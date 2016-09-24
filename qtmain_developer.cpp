#include <iostream>
#include <string>
#include <QApplication>
#include <QDebug>
#include <QIcon>
#include "qtbrainweavermenudialog.h"
#include "qtbrainweavermasterdialog.h"

const std::string CreateStyleSheet()
{
  const std::string s =
    "QDialog { "
//    "  background-image: url(:/images/PicLoomBackground.png);" //Sorry Joost!
    "  background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0, stop: 0 #bbf, stop: 1 #bff);"
    "} "
    "QLabel { "
    "  font-size: 18px;"
    "  font-family: \"Courier\", \"Courier New\", Courier, monospace;"
    "  font-weight: bold;"
    "  padding: 1px;"
    "} "
    ""
    "QPushButton {"
    "  font-family: \"Courier New\", \"Courier\", Courier, monospace;"
    "  font-size: 16px;"
    "  border-width: 1px;"
    "  border-style: solid;"
    "  padding: 3px;"
    "} "
    ""
    "QPushButton:enabled {"
    "  color: black;"
    "  background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ccc, stop: 1 #fff);"
    "  border-color: #111;"
    "} "
    "QPushButton:disabled {"
    "  color: #888;"
    "  background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ccc, stop: 1 #fff);"
    "  border-color: #fff;"
    "} "
    ""
    "QPlainTextEdit {"
    "  font-size: 12px;  font-family: \"Courier\", \"Courier New\", Courier, monospace;"
    "}";

  return s;
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
    a.setStyleSheet(CreateStyleSheet().c_str());
    a.setWindowIcon(QIcon(":/images/R.png"));
    ribi::braw::QtMasterDialog d;
    d.add_new(new ribi::braw::QtMenuDialog);
    d.show();
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
