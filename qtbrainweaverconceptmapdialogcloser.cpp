#include "qtbrainweaverconceptmapdialogcloser_test.h"

#include <cassert>

#include <QApplication>
#include <QDebug>
#include <QPushButton>

#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweaverconceptmapdialogcloser.h"
#include "ui_qtbrainweaverconceptmapdialog.h"
#include "qtconceptmapcommandcreatenewnode.h"

using namespace ribi::cmap;

ribi::braw::QtConceptMapDialogCloser::QtConceptMapDialogCloser()
{

}

ribi::braw::QtConceptMapDialogCloser::~QtConceptMapDialogCloser()
{

}

void ribi::braw::QtConceptMapDialogCloser::Modify()
{
  ribi::braw::QtConceptMapDialog* pop_up = nullptr;
  while (!pop_up)
  {
    pop_up
      = qobject_cast<ribi::braw::QtConceptMapDialog*>(
        qApp->activeWindow()
      );
    qApp->processEvents();
  }
  assert(pop_up);
  QtConceptMap * const q = pop_up->GetQtConceptMap();
  const auto before = q->ToConceptMap();
  q->DoCommand(
    new CommandCreateNewNode(*q)
  );
  const auto after = q->ToConceptMap();
  assert(before != after);
}

void ribi::braw::QtConceptMapDialogCloser::PressCancel()
{
  ribi::braw::QtConceptMapDialog* pop_up = nullptr;
  while (!pop_up)
  {
    pop_up
      = qobject_cast<ribi::braw::QtConceptMapDialog*>(
        qApp->activeWindow()
      );
    qApp->processEvents();
  }
  assert(pop_up);
  pop_up->ui->button_cancel->click();
  assert(pop_up->isHidden());
}

void ribi::braw::QtConceptMapDialogCloser::PressOk()
{
  ribi::braw::QtConceptMapDialog* pop_up = nullptr;
  while (!pop_up)
  {
    pop_up
      = qobject_cast<ribi::braw::QtConceptMapDialog*>(
        qApp->activeWindow()
      );
    qApp->processEvents();
  }
  assert(pop_up);
  pop_up->ui->button_ok->click();
  assert(pop_up->isHidden());
}
