#include "qtbrainweaverclusterdialogcloser_test.h"

#include <cassert>

#include <QApplication>
#include <QDebug>
#include <QPushButton>

#include "qtbrainweaverclusterdialog.h"
#include "qtbrainweaverclusterdialogcloser.h"
#include "ui_qtbrainweaverclusterdialog.h"
#include "qtconceptmapcommandcreatenewnode.h"

using namespace ribi::cmap;

ribi::braw::QtClusterDialogCloser::QtClusterDialogCloser()
{

}

ribi::braw::QtClusterDialogCloser::~QtClusterDialogCloser()
{

}

void ribi::braw::QtClusterDialogCloser::Modify() const
{
  ribi::braw::QtClusterDialog* const pop_up
    = qobject_cast<ribi::braw::QtClusterDialog*>(
      qApp->activeWindow()
    );
  assert(pop_up);
  const File before = pop_up->ToFile();
  pop_up->ui->edit->setText("New");
  pop_up->ui->button_add->click();
  const File after = pop_up->ToFile();
  assert(before != after);
}

void ribi::braw::QtClusterDialogCloser::PressCancel() const
{
  ribi::braw::QtClusterDialog* const pop_up
    = qobject_cast<ribi::braw::QtClusterDialog*>(
      qApp->activeWindow()
    );
  assert(pop_up);
  pop_up->ui->button_cancel->click();
  assert(pop_up->isHidden());
}

void ribi::braw::QtClusterDialogCloser::PressOk() const
{
  ribi::braw::QtClusterDialog* const pop_up
    = qobject_cast<ribi::braw::QtClusterDialog*>(
      qApp->activeWindow()
    );
  assert(pop_up);
  pop_up->ui->button_ok->click();
  assert(pop_up->isHidden());
}
