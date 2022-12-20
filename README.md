# BrainWeaver

BrainWeaver, tool for teacher education, as described in [1].

You can download BrainWeaver :

 * (new) [here](http://richelbilderbeek.nl/ProjectBrainWeaverExe20190301.zip)
 * (stable) [here](http://richelbilderbeek.nl/ProjectBrainWeaverExe20180916.zip)

## Build status of builds that BrainWeaver relies on

Note that [BrainWeaverRuffian](https://github.com/richelbilderbeek/BrainWeaverRuffian) *should fail*! See [BrainWeaverRuffian](https://github.com/richelbilderbeek/BrainWeaverRuffian) why.

## Building

Building `BrainWeaver` should be easy on Debian or *ubuntu or other GNU/Linux distro's that use Debian as a package manager. If you have another
operating system or package manager, feel invited to add building instructions for those platforms.

To build `BrainWeaver` you will need to:

 * Install some packages
 * Download some other GitHubs
 * Build some other GitHubs
 * Build `BrainWeaver`

### Install packages

In the `BrainWeaver` folder, run the `install_packages.sh` script with root rights:

```
sudo ./install_packages.sh
```


### Download other GitHubs

In the `BrainWeaver` folder, run the `download_other_githubs.sh` script (without root access):

```
./download_other_githubs
```

### Build other GitHubs

In the `BrainWeaver` folder, run the `build_other_githubs.sh` script (without root access):

```
./build_other_githubs
```

### Build `BrainWeaver`

Within the `BrainWeaver` folder, 

 * Developer: Open the Qt Creator project file `BrainWeaverDeveloper.pro` in Qt Creator and build
 * Student module: Open the Qt Creator project file `BrainWeaverStudent.pro` in Qt Creator and build
 * Assessor module: Open the Qt Creator project file `BrainWeaverAssessor.pro` in Qt Creator and build

If you do not use Qt Creator, you can build the project using `qmake` and `make` like this:

```
qmake BrainWeaverDeveloper.pro -qt=qt5
make 
```

## User documentation

See [the BrainWeaver documentation](doc/README.md).

## Testing

Testing is done by:

 * BrainWeaverConsoleTest.pro (run by Travis CI)
 * BrainWeaverDeveloperTest.pro (run by Travis CI)
 * the file `test_scripts/scenario1.sh` for a minimal run ([zipped video](demos/scenario1.zip)) (started by hand, BrainWeaver must be running)
 * the file `test_scripts/scenario2.sh` for a more complex run (started by hand, BrainWeaver must be running)

## Help

### Building fails!

I personally hate building problems, so I will be most happy to help you out. Please let me know, by, for example, adding an Issue.

### Other problems

Please let me know, by, for example, adding an Issue.

## SLOCcount



```
Total Physical Source Lines of Code (SLOC)                = 445,425
Development Effort Estimate, Person-Years (Person-Months) = 120.85 (1,450.19)
 (Basic COCOMO model, Person-Months = 2.4 * (KSLOC**1.05))
Schedule Estimate, Years (Months)                         = 3.31 (39.74)
 (Basic COCOMO model, Months = 2.5 * (person-months**0.38))
Estimated Average Number of Developers (Effort/Schedule)  = 36.49
Total Estimated Cost to Develop                           = $ 2,732,881
 (average salary = $22,614/year, overhead = 1.00).
SLOCCount, Copyright (C) 2001-2004 David A. Wheeler
SLOCCount is Open Source Software/Free Software, licensed under the GNU GPL.
SLOCCount comes with ABSOLUTELY NO WARRANTY, and you are welcome to
redistribute it under certain conditions as specified by the GNU GPL license;
see the documentation for details.
Please credit this data as "generated using David A. Wheeler's 'SLOCCount'."
```

## Licenses

 * [Montserrat font license](LICENSE_Montserrat.txt), font by Julieta Ulanovsky 

## References

 * [1] van den Bogaart, A. C., Bilderbeek, R. J. C., Schaap, H., Hummel, H. G., & Kirschner, P. A. (2016). A computer-supported method to reveal and assess Personal Professional Theories in vocational education. Technology, Pedagogy and Education, 1-17.
