#Don't enable Effective C++ warnings when using Qwt
include(../RibiLibraries/DesktopApplicationNoWeffcpp.pri)
include(../RibiLibraries/Apfloat.pri)
include(../RibiLibraries/BoostAll.pri)

include(../RibiLibraries/GeneralConsole.pri)
include(../RibiLibraries/GeneralDesktop.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

#Specific, console
include(../RibiClasses/CppConceptMap/CppConceptMap.pri)
include(../RibiClasses/CppContainer/CppContainer.pri)
include(../RibiClasses/CppCounter/CppCounter.pri)
include(../RibiClasses/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../RibiClasses/CppGeometry/CppGeometry.pri)
include(../RibiClasses/CppGrabber/CppGrabber.pri)
include(../RibiClasses/CppPlane/CppPlane.pri)
include(../RibiClasses/CppRibiRandom/CppRibiRandom.pri)
include(../RibiClasses/CppRibiRegex/CppRibiRegex.pri)
include(../RibiClasses/CppXml/CppXml.pri)

#Specific, desktop
include(../RibiClasses/CppQtArrowItem/CppQtArrowItem.pri)
include(../RibiClasses/CppQtDisplayPosItem/CppQtDisplayPosItem.pri)
include(../RibiClasses/CppQtConceptMap/CppQtConceptMap.pri)
include(../RibiClasses/CppQtImage/CppQtImage.pri)
include(../RibiClasses/CppQtKeyboardFriendlyGraphicsView/CppQtKeyboardFriendlyGraphicsView.pri)
include(../RibiClasses/CppQtLabeledQuadBezierArrowItem/CppQtLabeledQuadBezierArrowItem.pri)
include(../RibiClasses/CppQtPathArrowItem/CppQtPathArrowItem.pri)
include(../RibiClasses/CppQtQuadBezierArrowItem/CppQtQuadBezierArrowItem.pri)
include(../RibiClasses/CppQtRoundedEditRectItem/CppQtRoundedEditRectItem.pri)
include(../RibiClasses/CppQtRoundedRectItem/CppQtRoundedRectItem.pri)
include(../RibiClasses/CppQtScopedDisable/CppQtScopedDisable.pri)
include(../RibiClasses/CppRibiSystem/CppRibiSystem.pri)
include(../StyleSheetSetter/StyleSheetSetterDesktop.pri)
include(../BoostGraphTutorial/BoostGraphTutorial/boost_graph_tutorial.pri)
include(BrainweaverDesktop.pri)

SOURCES += qtmain_assessor.cpp

# QResources give this error
QMAKE_CXXFLAGS += -Wno-unused-variable

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov
