#!/bin/bash
qmake BrainweaverDeveloper.pro
make
qmake BrainweaverAssessor.pro
make
qmake BrainweaverStudent.pro
make
