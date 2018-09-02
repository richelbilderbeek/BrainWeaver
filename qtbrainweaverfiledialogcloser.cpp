#include "qtbrainweaverfiledialogcloser_test.h"

#include <cassert>

#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>

#include "qtbrainweaverfiledialog.h"
#include "qtbrainweaverfiledialogcloser.h"
#include "qtconceptmapcommandcreatenewnode.h"

using namespace ribi::cmap;

ribi::braw::QtFileDialogCloser::QtFileDialogCloser(const QString& filename)
  : m_filename{filename}
{

}

ribi::braw::QtFileDialogCloser::~QtFileDialogCloser()
{

}

QFileDialog * ribi::braw::QtFileDialogCloser::GetDialog() const noexcept
{
  QFileDialog * pop_up = nullptr;
  while (!pop_up)
  {
    pop_up = qobject_cast<QFileDialog*>(
      qApp->activeWindow()
    );
    qApp->processEvents();
  }
  return pop_up;
}

void ribi::braw::QtFileDialogCloser::PressCancel() const
{
  QFileDialog * const pop_up = GetDialog();
  assert(pop_up);
  pop_up->selectFile(m_filename);
  pop_up->reject();
  pop_up->setResult(QDialog::Rejected);
  assert(pop_up->isHidden());
}

void ribi::braw::QtFileDialogCloser::PressOk() const
{
  QFileDialog * const pop_up = GetDialog();
  assert(pop_up);
  pop_up->selectFile(m_filename);
  pop_up->close();
  pop_up->setResult(QDialog::Accepted);
  assert(pop_up->isHidden());
}
