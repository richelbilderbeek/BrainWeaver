#include "qtbrainweaverconceptmapdialogcloser_test.h"

#include <cassert>

#include <QApplication>
#include <QDebug>
#include <QPushButton>

#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweaverconceptmapdialogcloser.h"
#include "ui_qtbrainweaverconceptmapdialog.h"

ribi::braw::QtConceptMapDialogCloser::QtConceptMapDialogCloser()
{

}

ribi::braw::QtConceptMapDialogCloser::~QtConceptMapDialogCloser()
{

}

void ribi::braw::QtConceptMapDialogCloser::Close()
{
  ribi::braw::QtConceptMapDialog* const pop_up
    = qobject_cast<ribi::braw::QtConceptMapDialog*>(
      qApp->activeWindow()
    );
  assert(pop_up);
  pop_up->ui->button_ok->click();
  assert(pop_up->isHidden());
}
