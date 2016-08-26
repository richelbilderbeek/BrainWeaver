#!/bin/bash

cpp_files=`ls *.cpp | egrep -v "^qrc_.*\.cpp$" | egrep -v "^moc_.*\.cpp$"`
h_files=`ls *.h | egrep -v "^ui_.*\.h$"`

./oclint-0.10.3/bin/oclint -o oclint.log -max-priority-1 0 -max-priority-2 0 -max-priority-3 0 \
  -disable-rule ShortVariableName \
  -disable-rule FileNotFound \
  $cpp_files \
  $h_files \
  -- \
  -c -std=c++11 \
  -I../RibiClasses/CppAbout \
  -I../RibiClasses/CppHelp \
  -I../RibiClasses/CppTestTimer \
  -I../RibiClasses/CppFileIo \
  -I../RibiClasses/CppMenuDialog \
  -I../RibiClasses/CppQtAboutDialog \
  -I../RibiClasses/CppQtHideAndShowDialog \
  -I../RibiClasses/CppTrace \
  -I/usr/include/c++/5 \
  -I/usr/include/qt5 \
  -I/usr/include/qt5/QtCore \
  -I/usr/include/qt5/QtGui \
  -I/usr/include/qt5/QtWidgets \
  > /dev/null

#cat oclint.log

# Will be 1 if success
# Will be 0 if fail
success=`egrep "FilesWithViolations=0 P1=0 P2=0 P3=0" oclint.log | wc -l`

if [ $success -eq 1 ]; 
then
  echo "OCLint: OK"
else
  echo "OCLint: Fail"
  exit 1
fi