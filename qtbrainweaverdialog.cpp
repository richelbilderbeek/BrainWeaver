#include "qtbrainweaverdialog.h"

#include <QCloseEvent>
#include <QDebug>

ribi::braw::QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent)
{
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help
  setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint); //Remove close?
  setWindowFlags(windowFlags() & ~Qt::WindowCancelButtonHint); //Remove close?

}

void ribi::braw::QtDialog::closeEvent(QCloseEvent *)
{
  //From http://stackoverflow.com/a/29250691/3364162
  //event->setAccepted(!event->spontaneous());
  emit remove_me(this);
}
