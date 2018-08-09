#include <iostream>
#include <string>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QIcon>
#include "qtbrainweavermenudialog.h"

std::string CreateStyleSheet() //!OCLINT indeed a long stylesheet
{
  return
    "* {\n"
    "  font-family: \":/BrainWeaver/fonts/Montserrat-Regular.ttf\";\n"
    "}\n"
    "QDialog {\n"
//    "  background-image: url(:/BrainWeaver/pics/LoomBackground.png);\n" //Sorry Joost!
    "  background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0, stop: 0 #bbf, stop: 1 #bff);\n"
    "}\n"
    "QLabel {\n"
    "  font-size: 18px;\n"
    "  font-weight: bold;\n"
    "  padding: 1px;\n"
    "  font-family: \":/BrainWeaver/fonts/Montserrat-Regular.ttf\";\n"
    "}\n"
    "QLabel#label_cluster_relations {\n"
    "  font-size: 10px;\n"
    "}\n"
    "QLabel#label_complexity {\n"
    "  font-size: 20px;\n"
    "}\n"
    "QLabel#label_concept_examples {\n"
    "  font-size: 10px;\n"
    "}\n"
    "QLabel#label_concreteness {\n"
    "  font-size: 20px;\n"
    "}\n"
    "QLabel#label_name {\n"
    "  font-size: 12px;\n"
    "}\n"
    "QLabel#label_specificity {\n"
    "  font-size: 20px;\n"
    "}\n"
    "\n"
    "QPushButton {\n"
    "  font-size: 16px;\n"
    "  font-family: \":/BrainWeaver/fonts/Montserrat-Regular.ttf\";\n"
    "  border-width: 1px;\n"
    "  border-style: solid;\n"
    "  padding: 3px;\n"
    "}\n"
    "\n"
    "QPushButton:enabled {\n"
    "  color: black;\n"
    "  background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ccc, stop: 1 #fff);\n" //!OCLINT
    "  border-color: #111;\n"
    "}\n"
    "QPushButton:disabled {\n"
    "  color: #888;\n"
    "  background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ccc, stop: 1 #fff);\n" //!OCLINT
    "  border-color: #fff;\n"
    "}\n"
    "\n"
    "QPlainTextEdit {\n"
    "  font-size: 14px;\n"
    "  font-family: \":/BrainWeaver/fonts/Montserrat-Regular.ttf\";\n"
    "}\n"
    "\n"
    "ribi::cmap::QtNode {\n"
    "  font-size: 14px;\n"
    "}\n"
    "\n"
    "QTableWidget {\n"
    "  font-size: 14px;\n"
    "  font-family: \":/BrainWeaver/fonts/Montserrat-Regular.ttf\";\n"
    "  alternate-background-color: #BBB;\n"
    "  gridline-color: black;\n"
    "}\n"
    "\n"
    "QHeaderView {\n"
    "  font-size: 14px;\n"
    "  font-family: \":/BrainWeaver/fonts/Montserrat-Regular.ttf\";\n"
    "  border-width: 1px;\n"
    "  border-style: solid;\n"
    "}\n"
    "\n"
  ;
}




//From https://rohieb.wordpress.com/2010/07/08/qt-throw-exceptions-from-signals-and-slots/
//which is adapted from http://stackoverflow.com/a/1578433/3364162
class MyApplication : public QApplication
{
public:
  MyApplication(int& argc, char ** argv)
    : QApplication(argc, argv)
  {

  }

  // reimplemented from QApplication so we can throw exceptions in slots
  bool notify(QObject * receiver, QEvent * event) {
    try
    {
      return QApplication::notify(receiver, event);
    }
    catch(std::exception& e)
    {
      qCritical() << "Exception thrown:" << e.what();
    }
    catch(...)
    {
      qCritical() << "Unknown exception thrown";
    }
    return false;
  }
};


int main(int argc, char *argv[])
{
  try
  {
    MyApplication a(argc, argv);
    #ifndef NDEBUG
    std::clog << "DEBUG mode\n";
    #else
    std::clog << "RELEASE mode\n";
    #endif
    a.setStyleSheet(CreateStyleSheet().c_str());
    a.setWindowIcon(QIcon(":/images/R.png"));
    ribi::braw::QtMenuDialog d;
    d.show();
    //Put d in screen center at 80% of fullscreen size
    {
      d.setGeometry(QRect(64,51,1152,922));
    }
    return a.exec();
  }
  catch (std::exception& e)
  {
    std::cout << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cout << "Unknown exception thrown" << '\n';
    return 1;
  }
}
