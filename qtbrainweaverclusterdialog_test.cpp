#include "qtbrainweaverclusterdialog_test.h"

#include <fstream>
#include <iostream>
#include <boost/algorithm/string/trim_all.hpp>
#include <boost/shared_ptr.hpp>

#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>

#include "qtbrainweaverclusterdialog.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "conceptmapcenternodefactory.h"

#include "conceptmapcompetency.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "brainweaverclusterfactory.h"
#include "brainweavercluster.h"
#include "brainweaverfilefactory.h"
#include "brainweaverfile.h"
#include "fileio.h"
#include "qtbrainweaverclusterwidget.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweaverfiledialog.h"
#include "ui_qtbrainweaverclusterdialog.h"

using namespace ribi::cmap;

void ribi::braw::QtClusterDialogTest
  ::ButtonAddClickedNothingToAdd() const noexcept
{
  File file = FileFactory().Get0();
  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);
  QtClusterDialog d(file);
  d.show();
  d.on_button_add_clicked();
}

void ribi::braw::QtClusterDialogTest
  ::ButtonAddClickedSomethingToAdd() const noexcept
{
  File file = FileFactory().Get0();
  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);
  QtClusterDialog d(file);
  d.show();
  d.ui->edit->setText("Something");
  d.on_button_add_clicked();
}

void ribi::braw::QtClusterDialogTest
  ::ButtonNextClickedNoConceptMap() const noexcept
{
  File file = FileFactory().Get0();
  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);
  QtClusterDialog d(file);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_next_clicked();
}

void ribi::braw::QtClusterDialogTest
  ::ButtonNextClickedWithConceptMap() const noexcept
{
  File file = FileFactory().Get5();
  assert(boost::num_vertices(file.GetConceptMap()));
  QtClusterDialog d(file);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_next_clicked();
}


void ribi::braw::QtClusterDialogTest
  ::ClusterDialogEnabledIfNoConceptMap() const noexcept
{
  File file = FileFactory().Get0();

  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);

  QVERIFY(!file.GetCluster().Empty());
  QVERIFY(boost::num_vertices(file.GetConceptMap()) == 0);

  const QtClusterDialog d(file);
  const auto w = d.GetWidget();
  QVERIFY(w && w->isEnabled());
}

void ribi::braw::QtClusterDialogTest::
  ClusterDialogDisabledIfNodesInConceptMap() const noexcept
{
  const std::string question = "question with spaces";
  File file;
  file.SetQuestion(question);

  const Cluster cluster = ClusterFactory().GetTest( { 0,1,2 } );

  file.SetCluster(cluster);

  const int index_1 = 1;
  QVERIFY(index_1 < ConceptFactory().GetNumberOfTests());
  const int index_2 = 2;
  QVERIFY(index_2 < ConceptFactory().GetNumberOfTests());

  file.SetConceptMap(CreateConceptMap(question));
  QtClusterDialog d(file);
  d.show();
  QVERIFY(d.GetWidget());
  QVERIFY(!d.GetWidget()->isEnabled());
}

void ribi::braw::QtClusterDialogTest::DefaultConstruct() const noexcept
{
  File file = FileFactory().Get0();
  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);
  QtClusterDialog d(file);
  d.show();
}

void ribi::braw::QtClusterDialogTest
  ::EnableButtonDependingOnFile() const noexcept
{
  const auto v = File::GetTests();
  std::for_each(v.begin(),v.end(),
    [](const File& file)
    {
      const bool had_cluster = !file.GetCluster().Empty();
      const bool had_concept_map = boost::num_vertices(file.GetConceptMap());
      QtClusterDialog d{file};

      if (!had_cluster && !had_concept_map)
      {
        QVERIFY(d.GetUi()->button_add->isEnabled());
      }
      if ( had_cluster && !had_concept_map)
      {
        QVERIFY(d.GetUi()->button_add->isEnabled());
      }
      if (!had_cluster &&  had_concept_map)
      {
        QVERIFY(!d.GetUi()->button_add->isEnabled());
      }
      if ( had_cluster &&  had_concept_map)
      {
        QVERIFY(!d.GetUi()->button_add->isEnabled());
      }
    }
  );
}

void ribi::braw::QtClusterDialogTest::GetWidget() const noexcept
{
  File file = FileFactory().Get0();
  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);
  QtClusterDialog d(file);
  d.show();
  QVERIFY(d.GetWidget());
}

void ribi::braw::QtClusterDialogTest::PressEscape() const noexcept
{
  File file = FileFactory().Get0();
  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);
  QtClusterDialog d(file);
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
}

void ribi::braw::QtClusterDialogTest::PressSomething() const noexcept
{
  //Pressing something that has to be passed to child
  File file = FileFactory().Get0();
  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);
  QtClusterDialog d(file);
  d.show();
  QTest::keyClick(&d, Qt::Key_0);
}

void ribi::braw::QtClusterDialogTest::QuickSaveFirstTimeOpensDialog() const noexcept
{
  QtClusterDialog d(FileFactory().GetUnrated());
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  QtFileDialog::m_last_file = "";
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
}

void ribi::braw::QtClusterDialogTest::QuickSaveSecondTimeSavesFast() const noexcept
{
  QtClusterDialog d(FileFactory().Get5());
  const QString filename{"tmp.cmp"};
  QtFileDialog::m_last_file = filename;
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
  QVERIFY(QFile::exists(filename));
  QFile::remove(filename);
}

void ribi::braw::QtClusterDialogTest::Save() const noexcept
{
  File file = FileFactory().Get5();
  QtClusterDialog d(file);
  d.show();
  const QString filename{"qtbrainweaverclusterdialog_test_save.cmp"};
  if (ribi::is_regular_file(filename.toStdString())) { ribi::delete_file(filename.toStdString()); }
  assert(!ribi::is_regular_file(filename.toStdString()));
  d.Save(filename);
  QVERIFY(ribi::is_regular_file(filename.toStdString()));
}

