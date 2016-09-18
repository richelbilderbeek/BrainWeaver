# Brainweaver

[![Travis CI logo](TravisCI.png)](https://travis-ci.org)
![Whitespace](Whitespace.png)
[![Codecov logo](Codecov.png)](https://www.codecov.io)
[![gplv3](http://www.gnu.org/graphics/gplv3-88x31.png)](http://www.gnu.org/licenses/gpl.html)

[![Build Status](https://travis-ci.org/richelbilderbeek/Brainweaver.svg?branch=master)](https://travis-ci.org/richelbilderbeek/Brainweaver)
[![codecov.io](https://codecov.io/github/richelbilderbeek/Brainweaver/coverage.svg?branch=master)](https://codecov.io/github/richelbilderbeek/Brainweaver?branch=master)

Brainweaver, tool for teacher education, as described in [1].

Brainweaver is in active development.

## Build status of builds that Brainweaver relies on

 * [![Build Status](https://travis-ci.org/richelbilderbeek/BoostGraphTutorial.svg?branch=master)](https://travis-ci.org/richelbilderbeek/BoostGraphTutorial) [![codecov.io](https://codecov.io/github/richelbilderbeek/BoostGraphTutorial/coverage.svg?branch=master)](https://codecov.io/github/richelbilderbeek/BoostGraphTutorial?branch=master) [BoostGraphTutorial](https://github.com/richelbilderbeek/BoostGraphTutorial)
 * [![Build Status](https://travis-ci.org/richelbilderbeek/RibiClasses.svg?branch=master)](https://travis-ci.org/richelbilderbeek/RibiClasses) [![codecov.io](https://codecov.io/github/richelbilderbeek/RibiClasses/coverage.svg?branch=master)](https://codecov.io/github/richelbilderbeek/RibiClasses?branch=master) [RibiClasses](https://github.com/richelbilderbeek/RibiClasses)
 * [![Build Status](https://travis-ci.org/richelbilderbeek/StyleSheetSetter.svg?branch=master)](https://travis-ci.org/richelbilderbeek/StyleSheetSetter) [![codecov.io](https://codecov.io/github/richelbilderbeek/StyleSheetSetter/coverage.svg?branch=master)](https://codecov.io/github/richelbilderbeek/StyleSheetSetter?branch=master) [StyleSheetSetter](https://github.com/richelbilderbeek/StyleSheetSetter)
 * [![Build Status](https://travis-ci.org/richelbilderbeek/ConceptMap.svg?branch=master)](https://travis-ci.org/richelbilderbeek/ConceptMap) [![codecov.io](https://codecov.io/github/richelbilderbeek/ConceptMap/coverage.svg?branch=master)](https://codecov.io/github/richelbilderbeek/ConceptMap?branch=master) [ConceptMap](https://github.com/richelbilderbeek/ConceptMap)
 * [![Build Status](https://travis-ci.org/richelbilderbeek/QtConceptMap.svg?branch=master)](https://travis-ci.org/richelbilderbeek/QtConceptMap) [![codecov.io](https://codecov.io/github/richelbilderbeek/QtConceptMap/coverage.svg?branch=master)](https://codecov.io/github/richelbilderbeek/QtConceptMap?branch=master) [QtConceptMap](https://github.com/richelbilderbeek/QtConceptMap)
 * [![Build Status](https://travis-ci.org/richelbilderbeek/QtKeyboardFriendlyGraphicsView.svg?branch=master)](https://travis-ci.org/richelbilderbeek/QtKeyboardFriendlyGraphicsView) [![codecov.io](https://codecov.io/github/richelbilderbeek/QtKeyboardFriendlyGraphicsView/coverage.svg?branch=master)](https://codecov.io/github/richelbilderbeek/QtKeyboardFriendlyGraphicsView?branch=master) [QtKeyboardFriendlyGraphicsView](https://github.com/richelbilderbeek/QtKeyboardFriendlyGraphicsView)

## Building

Building `Brainweaver` should be easy on Debian or *ubuntu or other GNU/Linux distro's that use Debian as a package manager. If you have another
operating system or package manager, feel invited to add building instructions for those platforms.

To build `Brainweaver` you will need to:

 * Install some packages
 * Download some other GitHubs
 * Build some other GitHubs
 * Build `Brainweaver`

### Install packages

In the `Brainweaver` folder, run the `install_packages.sh` script with root rights:

```
sudo ./install_packages.sh
```


### Download other GitHubs

In the `Brainweaver` folder, run the `download_other_githubs.sh` script (without root access):

```
./download_other_githubs.sh
```

### Build other GitHubs

In the `Brainweaver` folder, run the `build_other_githubs.sh` script (without root access):

```
./build_other_githubs.sh
```

### Build `Brainweaver`

Within the `Brainweaver` folder, 

 * Developer: Open the Qt Creator project file `BrainweaverDeveloper.pro` in Qt Creator and build
 * Student module: Open the Qt Creator project file `BrainweaverStudent.pro` in Qt Creator and build
 * Assessor module: Open the Qt Creator project file `BrainweaverAssessor.pro` in Qt Creator and build

If you do not use Qt Creator, you can build the project using `qmake` and `make` like this:

```
qmake BrainweaverDeveloper.pro
make
```

## Manual

See [the Brainweaver manual](Manual.md).

## Help

### Building fails!

I personally hate building problems, so I will be most happy to help you out. Please let me know, by, for example, adding an Issue.

### Other problems

Please let me know, by, for example, adding an Issue.

## References

 * [1] Van den Bogaart, A. C. M., Bilderbeek, R.J.C., Schaap, H., Hummel, H. G. K., & Kirschner, P. A. (submitted). A Computer supported  method to reveal and assess personal professional theories in vocational education. Technology, Pedagogy & Education.
