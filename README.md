# Brainweaver

Brainweaver, tool for teacher education, as described in [1].

Brainweaver is in active development.

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

## Help

### Building fails!

I personally hate building problems, so I will be most happy to help you out. Please let me know, by, for example, adding an Issue.

### Other problems

Please let me know, by, for example, adding an Issue.

## References

 * [1] Van den Bogaart, A. C. M., Bilderbeek, R.J.C., Schaap, H., Hummel, H. G. K., & Kirschner, P. A. (submitted). A Computer supported  method to reveal and assess personal professional theories in vocational education. Technology, Pedagogy & Education.
