#include "qtbrainweaverrateconceptmapdialog_test.h"

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QKeyEvent>

#include "qtbrainweaverrateconceptmapdialog.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "brainweaverfilefactory.h"
#include "qtbrainweaverfiledialog.h"
#include "brainweaverfile.h"
#include "qtconceptmap.h"
#include "qtbrainweaverratingdialog.h"
#include "fileio.h"
#include "qtconceptmaprateconceptdialog.h"
#include "ui_qtbrainweaverrateconceptmapdialog.h"

void ribi::braw::QtRateConceptMapDialogTest
::ButtonNextClicked() const noexcept
{
  const File file = FileFactory().Get5();
  assert(IsCenterNode(ribi::cmap::GetFirstNode(file.GetConceptMap())));
  QtRateConceptMapDialog d(file);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_next_clicked();
}

void ribi::braw::QtRateConceptMapDialogTest
  ::CloseOnEscape() const noexcept
{
  const File file = FileFactory().Get5();
  QtRateConceptMapDialog d(file);
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
}

void ribi::braw::QtRateConceptMapDialogTest
  ::ChangeEvents() const noexcept
{
  const File file = FileFactory().Get5();
  QtRateConceptMapDialog d(file);
  d.show();
  d.setEnabled(false);
  d.show();
  d.setEnabled(true);
  d.show();
}

void ribi::braw::QtRateConceptMapDialogTest
  ::FileMustMatchGetFile() const noexcept
{
  for (const auto& file: FileFactory().GetTests())
  {
    if (!boost::num_vertices(file.GetConceptMap()))
    {
      //Cannot rate a null concept map
      continue;
    }
    QtRateConceptMapDialog d(file);
    d.show();
    QVERIFY(d.GetFile() == file);
  }
}

void ribi::braw::QtRateConceptMapDialogTest::QuickSaveFirstTimeOpensDialog() const noexcept
{
  const File file = FileFactory().Get5();
  QtRateConceptMapDialog d(file);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
}


void ribi::braw::QtRateConceptMapDialogTest::QuickSaveSecondTimeSavesFast() const noexcept
{
  const File file = FileFactory().Get5();
  QtRateConceptMapDialog d(file);
  const QString filename{"tmp.cmp"};
  QtFileDialog::m_last_file = filename;
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
  QVERIFY(QFile::exists(filename));
  QFile::remove(filename);
}

void ribi::braw::QtRateConceptMapDialogTest::Save() const noexcept
{
  const std::string filename{
    "qtbrainweaverrateconceptmapdialog_test_save.cmp"
  };
  if (ribi::is_regular_file(filename)) { ribi::delete_file(filename); }
  assert(!ribi::is_regular_file(filename));

  const File file = FileFactory().Get5();
  QtRateConceptMapDialog d(file);
  d.show();
  d.Save(filename);
  QVERIFY(ribi::is_regular_file(filename));
}

void ribi::braw::QtRateConceptMapDialogTest::WidgetIsInitialized() const noexcept
{
  for (const auto& file: FileFactory().GetTests())
  {
    if (!boost::num_vertices(file.GetConceptMap()))
    {
      //Cannot rate a null concept map
      continue;
    }
    QtRateConceptMapDialog d(file);
    d.show();
    QVERIFY(d.GetWidget());
  }
}

