#include "qtbrainweaverstudentmenudialogcloser_test.h"

#include <cassert>

#include <QApplication>
#include <QDebug>
#include <QPushButton>

#include "qtbrainweaverstudentmenudialog.h"
#include "qtbrainweaverstudentmenudialogcloser.h"
#include "ui_qtbrainweaverstudentmenudialog.h"
#include "qtconceptmapcommandcreatenewnode.h"

using namespace ribi::cmap;

ribi::braw::QtStudentMenuDialogCloser::QtStudentMenuDialogCloser()
{

}

ribi::braw::QtStudentMenuDialogCloser::~QtStudentMenuDialogCloser()
{

}

void ribi::braw::QtStudentMenuDialogCloser::Close() const
{
  ribi::braw::QtStudentMenuDialog* pop_up{nullptr};
  while (!pop_up)
  {
    pop_up
      = qobject_cast<ribi::braw::QtStudentMenuDialog*>(
        qApp->activeWindow()
      );
    qApp->processEvents();
  }
  pop_up->close();
}

void ribi::braw::QtStudentMenuDialogCloser::EnterName() const
{
  ribi::braw::QtStudentMenuDialog* pop_up{nullptr};
  while (!pop_up)
  {
    pop_up
      = qobject_cast<ribi::braw::QtStudentMenuDialog*>(
        qApp->activeWindow()
      );
    qApp->processEvents();
  }
  pop_up->SetName("Fortune Harrington");
}

void ribi::braw::QtStudentMenuDialogCloser::PressStart() const
{
  ribi::braw::QtStudentMenuDialog* pop_up{nullptr};
  while (!pop_up)
  {
    pop_up
      = qobject_cast<ribi::braw::QtStudentMenuDialog*>(
        qApp->activeWindow()
      );
    qApp->processEvents();
  }
  assert(pop_up);
  pop_up->ui->button_start->click();
  while (!pop_up->isHidden())
  {
    qApp->processEvents();
  }
  assert(pop_up->isHidden());
}
