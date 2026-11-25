#!/bin/bash
#
# Builds all Qt Creator projects (.pro files) in this folder,
# runs the console versions and collects the code coverage.
#
# Usage, from the root of this repository:
#
#   ./scripts/check_build.sh
#
# Used by .github/workflows/check_build.yaml
#
set -e

# Download the other GitHub repositories this project depends on,
# using the scripts of this repository
for script in download_other_githubs download_other_githubs.sh install_other_githubs install_other_githubs.sh
do
  if [ -f "${script}" ]; then
    echo "Running ${script}"
    bash "${script}" || true
  fi
done

# Download the other GitHub repositories the project files refer to,
# that have not been downloaded yet
for folder in $(grep -hoE '\.\./[A-Za-z0-9_]+' -- *.pro *.pri 2>/dev/null | sort -u | sed 's#\.\./##')
do
  if [ ! -d "../${folder}" ]; then
    echo "Downloading ${folder}"
    git clone --depth 1 "https://github.com/richelbilderbeek/${folder}" "../${folder}" || true
  fi
done

# Unzip the libraries that are stored as zip files in RibiLibraries
if [ -d ../RibiLibraries ]; then
  (cd ../RibiLibraries && sh fparser.sh > /dev/null 2>&1) || true
  (cd ../RibiLibraries && sh bigint.sh > /dev/null 2>&1) || true
  # The bundled Qwt misses an include needed by recent Qt5 versions
  for qwt_file in $(grep -lE "QPainterPath" ../RibiLibraries/qwt-6*/src/*.cpp 2>/dev/null)
  do
    grep -q "#include <QPainterPath>" "${qwt_file}" || sed -i '1i #include <QPainterPath>' "${qwt_file}"
  done
fi

# Extra settings, appended after the .pro file is read:
# - link to Boost.Timer, which is no longer header-only in recent Boost versions
# - allow the use of the deprecated Boost.Timer header
# - allow warnings, as these were not warnings yet when this code was written
# - use the current compiler, instead of an old one like g++-5
# - measure the code coverage
qmake_extra_args=(
  -after
  "CONFIG += debug"
  "QT += concurrent printsupport svg opengl"
  "QMAKE_CXX = g++"
  "QMAKE_LINK = g++"
  "DEFINES += BOOST_TIMER_ENABLE_DEPRECATED"
  "LIBS += -lboost_timer -lboost_chrono"
  "QMAKE_CXXFLAGS += -Wno-error --coverage"
  "QMAKE_LFLAGS += --coverage"
)

mkdir -p coverage

# The .pro files are in the root folder, or else in subfolders
pro_files=$(ls -- *.pro 2>/dev/null || find . -mindepth 2 -maxdepth 2 -name "*.pro" | sort)

root_folder=$(pwd)
n_built=0
for pro_path in ${pro_files}
do
  cd "${root_folder}/$(dirname "${pro_path}")"
  pro_file=$(basename "${pro_path}")
  # Wt (for websites), libnds (for the Nintendo DS) and Urho3D (for 3D) are not available
  if grep -qE 'Wt\.pri|CppWt|GeneralWeb\.pri|WebApplication\.pri|libnds|Urho3D|(^|[ /])wt[a-z_]*\.(cpp|h)' "${pro_file}" ||
    [[ "${pro_file}" == *Website* ]]; then
    echo "Skipping ${pro_file}, as it needs Wt, libnds or Urho3D"
    continue
  fi

  echo "Building ${pro_file}"
  rm -f Makefile Makefile.Debug Makefile.Release .qmake.stash
  qmake "${pro_file}" "${qmake_extra_args[@]}"
  make -j"$(nproc)"
  n_built=$((n_built + 1))

  # Run console applications, to collect code coverage.
  # These are not allowed to take long and may fail
  case "${pro_file}" in
    *Desktop*|*Gui*) ;;
    *)
      executable=$(basename "${pro_file}" .pro)
      if [ -x "${executable}" ]; then
        echo "Running ${executable}"
        timeout 60 "./${executable}" < /dev/null > /dev/null 2>&1 || echo "Running ${executable} failed, ignoring this"
      fi
      ;;
  esac
done

cd "${root_folder}"

if [ "${n_built}" -eq 0 ]; then
  echo "::warning::No project could be built, as all need Wt, libnds or Urho3D"
fi

echo "Collecting code coverage"
for gcda_file in $(find . -name "*.gcda")
do
  (cd coverage && gcov -p -o "../$(dirname "${gcda_file}")" "../${gcda_file}" > /dev/null 2>&1) || true
done

echo "Success: all projects built"
