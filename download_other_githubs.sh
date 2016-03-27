#!/bin/bash

cd ..

if [ ! -d BoostGraphTutorial ]; then
 git clone https://github.com/richelbilderbeek/BoostGraphTutorial
fi

if [ ! -d RibiClasses ]; then
 git clone https://github.com/richelbilderbeek/RibiClasses
fi

if [ ! -d RibiLibraries ]; then
 git clone https://github.com/richelbilderbeek/RibiLibraries
fi

if [ ! -d StyleSheetSetter ]; then
 git clone https://github.com/richelbilderbeek/StyleSheetSetter
fi

if [ ! -d TestArrowItems ]; then
  git clone https://github.com/richelbilderbeek/TestArrowItems
fi

if [ ! -d TestConceptMap ]; then
  git clone https://github.com/richelbilderbeek/TestConceptMap
fi

if [ ! -d TestRoundedEditRectItem ]; then
 git clone https://github.com/richelbilderbeek/TestRoundedEditRectItem
fi

if [ ! -d TestRoundedRectItem ]; then
 git clone https://github.com/richelbilderbeek/TestRoundedRectItem
fi
