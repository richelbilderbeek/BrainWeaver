#!/bin/bash

cd ..

if [ ! -d BoostGraphTutorial ]; then
 git clone https://github.com/richelbilderbeek/BoostGraphTutorial
fi

if [ ! -d ConceptMap ]; then
 git clone https://github.com/richelbilderbeek/ConceptMap
fi

if [ ! -d QtConceptMap ]; then
 git clone https://github.com/richelbilderbeek/QtConceptMap
fi

if [ ! -d QtKeyboardFriendlyGraphicsView ]; then
 git clone https://github.com/richelbilderbeek/QtKeyboardFriendlyGraphicsView
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
