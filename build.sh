#!/bin/bash
cd ..
pwd
ls
git clone https://github.com/richelbilderbeek/BoostGraphTutorial
git clone https://github.com/richelbilderbeek/RibiClasses
git clone https://github.com/richelbilderbeek/RibiLibraries
git clone https://github.com/richelbilderbeek/StyleSheetSetter
git clone https://github.com/richelbilderbeek/TestArrowItems
git clone https://github.com/richelbilderbeek/TestRoundedEditRectItem
git clone https://github.com/richelbilderbeek/TestRoundedRectItem
cd RibiLibraries; ./Apfloat.sh; cd ..
cd Brainweaver
qmake BrainweaverDeveloper.pro
make
qmake BrainweaverAssessor.pro
make
qmake BrainweaverStudent.pro
make
