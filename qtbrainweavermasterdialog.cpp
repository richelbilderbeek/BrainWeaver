#include "qtbrainweavermasterdialog.h"
#include <cassert>
#include <QCloseEvent>
#include <QDebug>
#include <QKeyEvent>
#include "qtbrainweaverdialog.h"
#include "ui_qtbrainweavermasterdialog.h"

ribi::braw::QtMasterDialog::QtMasterDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtMasterDialog)
{
  ui->setupUi(this);
  assert(ui->stackedWidget->count() == 0);

  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help
  setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint); //Remove close?
  setWindowFlags(windowFlags() & ~Qt::WindowCancelButtonHint); //Remove close?

  //this->setWindowState(Qt::WindowFullScreen);
  //Dialog * const dialog = new Dialog(this);
  //QObject::connect(dialog, SIGNAL(add_me(QDialog*const)), this, SLOT(add_new(QDialog*const)));
  //QObject::connect(dialog, SIGNAL(remove_me(QDialog*const)), this, SLOT(remove(QDialog*const)));
  //ui->stackedWidget->addWidget(dialog);
  //assert(ui->stackedWidget->count() == 1);
}

ribi::braw::QtMasterDialog::~QtMasterDialog()
{
  delete ui;
}

void ribi::braw::QtMasterDialog::add_new(QDialog * const dialog)
{
  //if (ui->stackedWidget->currentWidget())
  //{
  //  ui->stackedWidget->currentWidget()->setEnabled(false);
  //}

  const int new_index = ui->stackedWidget->addWidget(dialog);
  ui->stackedWidget->setCurrentIndex(new_index);

  //Update
  this->setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());
  //this->setGeometry(ui->stackedWidget->currentWidget()->geometry());

  QObject::connect(
    ui->stackedWidget->currentWidget(),
    SIGNAL(add_me(QDialog*const)),
    this,
    SLOT(add_new(QDialog*const))
  );
  QObject::connect(dialog, SIGNAL(remove_me(QDialog*const)), this, SLOT(remove(QDialog*const)));
}

void ribi::braw::QtMasterDialog::closeEvent(QCloseEvent * event)
{
  //From http://stackoverflow.com/a/29250691/3364162
  event->setAccepted(!event->spontaneous());
}

void ribi::braw::QtMasterDialog::keyPressEvent(QKeyEvent * e)
{
  e->setAccepted(false);
  //Determine what to close: a current widget if present, else this dialog itself
  //QWidget * d = ui->stackedWidget->currentWidget();
  //if (!d) close();
  //d->keyPressEvent(e);
}

void ribi::braw::QtMasterDialog::remove(QDialog * const dialog)
{
  ui->stackedWidget->removeWidget(dialog);
  delete dialog;

  const int new_index = ui->stackedWidget->count() - 1;
  ui->stackedWidget->setCurrentIndex(new_index);

  //Update
  if (new_index >= 0)
  {
    this->setWindowTitle(ui->stackedWidget->currentWidget()->windowTitle());
    //ui->stackedWidget->currentWidget()->setEnabled(true);
  }
  else
  {
    close();
  }
  //this->setGeometry(ui->stackedWidget->currentWidget()->geometry());

}
