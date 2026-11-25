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
fi

# Extra settings, appended after the .pro file is read:
# - link to Boost.Timer, which is no longer header-only in recent Boost versions
# - allow the use of the deprecated Boost.Timer header
# - allow warnings, as these were not warnings yet when this code was written
# - measure the code coverage
qmake_extra_args=(
  -after
  "CONFIG += debug"
  "DEFINES += BOOST_TIMER_ENABLE_DEPRECATED"
  "LIBS += -lboost_timer -lboost_chrono"
  "QMAKE_CXXFLAGS += -Wno-error --coverage"
  "QMAKE_LFLAGS += --coverage"
)

mkdir -p coverage

for pro_file in *.pro
do
  # Wt (for websites) and libnds (for the Nintendo DS) are not available
  if grep -qE 'Wt\.pri|GeneralWeb\.pri|WebApplication\.pri|libnds' "${pro_file}"; then
    echo "Skipping ${pro_file}, as it needs Wt or libnds"
    continue
  fi

  echo "Building ${pro_file}"
  rm -f Makefile Makefile.Debug Makefile.Release .qmake.stash
  qmake "${pro_file}" "${qmake_extra_args[@]}"
  make -j"$(nproc)"

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

echo "Collecting code coverage"
for gcda_file in $(find . -name "*.gcda")
do
  (cd coverage && gcov -p -o "../$(dirname "${gcda_file}")" "../${gcda_file}" > /dev/null 2>&1) || true
done

echo "Success: all projects built"
