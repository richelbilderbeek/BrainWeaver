#!/bin/bash

cd ..

if [ ! -d BoostGraphTutorial ]; then
 git clone https://github.com/richelbilderbeek/BoostGraphTutorial
fi

cd BoostGraphTutorial
git pull
cd ..

if [ ! -d RibiClasses ]; then
 git clone https://github.com/richelbilderbeek/RibiClasses
fi

cd RibiClasses
git pull
cd ..

if [ ! -d RibiLibraries ]; then
 git clone https://github.com/richelbilderbeek/RibiLibraries
fi

cd RibiLibraries
git pull
cd ..

if [ ! -d StyleSheetSetter ]; then
 git clone https://github.com/richelbilderbeek/StyleSheetSetter
fi

cd StyleSheetSetter
git pull
cd ..

if [ ! -d TestArrowItems ]; then
 git clone https://github.com/richelbilderbeek/TestArrowItems
fi

cd TestArrowItems
git pull
cd ..

if [ ! -d TestRoundedEditRectItem ]; then
 git clone https://github.com/richelbilderbeek/TestRoundedEditRectItem
fi

cd TestRoundedEditRectItem
git pull
cd ..

if [ ! -d TestRoundedRectItem ]; then
 git clone https://github.com/richelbilderbeek/TestRoundedRectItem
fi

cd TestRoundedRectItem
git pull
cd ..
