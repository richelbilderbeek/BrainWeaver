#include "qtbrainweaverstudentstartdialogcloser_test.h"

#include <cassert>

#include <QApplication>
#include <QDebug>
#include <QPushButton>

#include "qtbrainweaverstudentstartdialog.h"
#include "qtbrainweaverstudentstartdialogcloser.h"
#include "ui_qtbrainweaverstudentstartdialog.h"
#include "qtconceptmapcommandcreatenewnode.h"

using namespace ribi::cmap;

ribi::braw::QtStudentStartDialogCloser::QtStudentStartDialogCloser()
{

}

ribi::braw::QtStudentStartDialogCloser::~QtStudentStartDialogCloser()
{

}

void ribi::braw::QtStudentStartDialogCloser::Close() const
{
  ribi::braw::QtStudentStartDialog* pop_up{nullptr};
  while (!pop_up)
  {
    pop_up
      = qobject_cast<ribi::braw::QtStudentStartDialog*>(
        qApp->activeWindow()
      );
    qApp->processEvents();
  }
  pop_up->close();
}

void ribi::braw::QtStudentStartDialogCloser::PressStartCluster() const
{
  ribi::braw::QtStudentStartDialog* pop_up{nullptr};
  while (!pop_up)
  {
    pop_up
      = qobject_cast<ribi::braw::QtStudentStartDialog*>(
        qApp->activeWindow()
      );
    qApp->processEvents();
  }
  assert(pop_up);
  pop_up->ui->button_start_associate->click();
  while (!pop_up->isHidden())
  {
    qApp->processEvents();
  }
  assert(pop_up->isHidden());
}

void ribi::braw::QtStudentStartDialogCloser::PressStartConceptMap() const
{
  ribi::braw::QtStudentStartDialog* pop_up{nullptr};
  while (!pop_up)
  {
    pop_up
      = qobject_cast<ribi::braw::QtStudentStartDialog*>(
        qApp->activeWindow()
      );
    qApp->processEvents();
  }
  assert(pop_up);
  pop_up->ui->button_start_construct->click();
  while (!pop_up->isHidden())
  {
    qApp->processEvents();
  }
  assert(pop_up->isHidden());
}
