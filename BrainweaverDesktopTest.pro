#DEFINES += BRAINWEAVER_MOVE_ITEMS_ON_COLLISION

CONFIG += debug_and_release

# Most specific first
include(BrainweaverDesktop.pri)
include(BrainweaverDesktopTest.pri)

#Don't enable Effective C++ warnings when using Qwt
include(../RibiLibraries/DesktopApplicationNoWeffcpp.pri)
include(../RibiLibraries/Apfloat.pri)
include(../RibiLibraries/BoostAll.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

include(../RibiLibraries/GeneralConsole.pri)
include(../RibiLibraries/GeneralDesktop.pri)

#Specific, console
include(../RibiClasses/CppContainer/CppContainer.pri)
include(../RibiClasses/CppCounter/CppCounter.pri)
include(../RibiClasses/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../RibiClasses/CppGeometry/CppGeometry.pri)
include(../RibiClasses/CppGrabber/CppGrabber.pri)
include(../RibiClasses/CppPlane/CppPlane.pri)
include(../RibiClasses/CppQtImage/CppQtImage.pri)
include(../RibiClasses/CppRibiRandom/CppRibiRandom.pri)
include(../RibiClasses/CppRibiRegex/CppRibiRegex.pri)
include(../RibiClasses/CppRibiSystem/CppRibiSystem.pri)
include(../RibiClasses/CppRibiTime/CppRibiTime.pri)
include(../RibiClasses/CppStopwatch/CppStopwatch.pri)

include(../RibiClasses/CppQtArrowItem/CppQtArrowItem.pri)
include(../RibiClasses/CppQtDisplayPosItem/CppQtDisplayPosItem.pri)
include(../RibiClasses/CppQtGraphics/CppQtGraphics.pri)
include(../RibiClasses/CppQtKeyboardFriendlyGraphicsView/CppQtKeyboardFriendlyGraphicsView.pri)
include(../RibiClasses/CppQtLabeledQuadBezierArrowItem/CppQtLabeledQuadBezierArrowItem.pri)
include(../RibiClasses/CppQtPathArrowItem/CppQtPathArrowItem.pri)
include(../RibiClasses/CppQtQuadBezierArrowItem/CppQtQuadBezierArrowItem.pri)
include(../RibiClasses/CppQtRoundedEditRectItem/CppQtRoundedEditRectItem.pri)
include(../RibiClasses/CppQtRoundedRectItem/CppQtRoundedRectItem.pri)
include(../RibiClasses/CppQtScopedDisable/CppQtScopedDisable.pri)
include(../RibiClasses/CppTrace/CppTrace.pri)
include(../RibiClasses/CppXml/CppXml.pri)

#Specific
include(../ConceptMap/ConceptMap.pri)
include(../QtConceptMap/QtConceptMap.pri)
include(../StyleSheetSetter/StyleSheetSetterDesktop.pri)
include(../BoostGraphTutorial/BoostGraphTutorial/boost_graph_tutorial.pri)

SOURCES += qtmain_test.cpp

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

# QResources give this error
QMAKE_CXXFLAGS += -Wno-unused-variable

# Qt:
# QtConcurrent::filterInternal(Sequence&, KeepFunctor, ReduceFunctor)’:
# /usr/include/qt4/QtCore/qtconcurrentfilter.h:108:47: error: typedef ‘Iterator’ locally defined but not used [-Werror=unused-local-typedefs]
# typedef typename Sequence::const_iterator Iterator;
QMAKE_CXXFLAGS += -Wno-unused-local-typedefs

# QTest
QT += testlib
