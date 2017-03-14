# Brainweaver

Branch|[![Travis CI logo](TravisCI.png)](https://travis-ci.org)
---|---
master|[![Build Status](https://travis-ci.org/richelbilderbeek/Brainweaver.svg?branch=master)](https://travis-ci.org/richelbilderbeek/Brainweaver)
develop|[![Build Status](https://travis-ci.org/richelbilderbeek/Brainweaver.svg?branch=develop)](https://travis-ci.org/richelbilderbeek/Brainweaver)
coverity_scan|[![Build Status](https://travis-ci.org/richelbilderbeek/Brainweaver.svg?branch=coverity_scan)](https://travis-ci.org/richelbilderbeek/Brainweaver)

<a href="https://scan.coverity.com/projects/richelbilderbeek-brainweaver">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/11051/badge.svg"/>
</a>

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
qmake BrainweaverDeveloper.pro -qt=qt5
make 
```

## User documentation

See [the Brainweaver documentation](doc/README.md).

## Testing

Testing is done by:

 * BrainweaverConsoleTest.pro (run by Travis CI)
 * BrainweaverDeveloperTest.pro (run by Travis CI)
 * the file `test_scripts/scenario1.sh` for a minimal run ([zipped video](demos/scenario1.zip)) (started by hand, Brainweaver must be running)
 * the file `test_scripts/scenario2.sh` for a more complex run (started by hand, Brainweaver must be running)

## Help

### Building fails!

I personally hate building problems, so I will be most happy to help you out. Please let me know, by, for example, adding an Issue.

### Other problems

Please let me know, by, for example, adding an Issue.

## References

 * [1] van den Bogaart, A. C., Bilderbeek, R. J. C., Schaap, H., Hummel, H. G., & Kirschner, P. A. (2016). A computer-supported method to reveal and assess Personal Professional Theories in vocational education. Technology, Pedagogy and Education, 1-17.

