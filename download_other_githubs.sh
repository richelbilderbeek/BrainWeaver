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