#include <iostream>
#include <string>
#include <QApplication>
#include <QIcon>
#include "qtbrainweavermenudialog.h"

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

int main(int argc, char *argv[])
{
  try
  {
    QApplication a(argc, argv);
    a.setStyleSheet(CreateStyleSheet().c_str());
    a.setWindowIcon(QIcon(":/images/R.png"));
    ribi::pvdb::QtMenuDialog d;
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
