#!/bin/bash
qmake BrainweaverDeveloper.pro
make debug
qmake BrainweaverAssessor.pro
make debug
qmake BrainweaverStudent.pro
make debug
