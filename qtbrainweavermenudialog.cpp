//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2016 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtbrainweavermenudialog.h"

#include <boost/lexical_cast.hpp>

#include <QFile>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLayout>
#include <QVBoxLayout>

#include "add_custom_vertex.h"
#include "brainweaverfilefactory.h"
#include "brainweaverfile.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapconcept.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapexamples.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapnode.h"
#include "container.h"
#include "counter.h"
#include "fileio.h"
#include "plane.h"
#include "qtbrainweaveraboutdialog.h"
#include "qtbrainweaverassessormenudialog.h"
#include "qtbrainweaverclusterdialog.h"
#include "qtbrainweaverclusterwidget.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweavercreateassessmentcompletedialog.h"
#include "qtbrainweaverfiledialog.h"
#include "qtbrainweaveroverviewdialog.h"
#include "qtbrainweaverprintconceptmapdialog.h"
#include "qtbrainweaverprintratingdialog.h"
#include "qtbrainweaverrateconceptmapdialog.h"
#include "qtbrainweaverratingdialog.h"
#include "qtbrainweaverstudentmenudialog.h"
#include "qtbrainweavertestcreatesubconceptmapdialog.h"
#include "qtbrainweaverviewfilesdialog.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmaprateconceptdialognewname.h"
#include "qtconceptmaprateconcepttallydialognewname.h"
#include "qtconceptmaprateexamplesdialognewname.h"
//#include "qtconceptmapviewtestsdialog.h"
#include "qtstylesheetsettermaindialog.h"
#include "qttestconceptmapmenudialog.h"
#include "qttesteditconceptmapdialog.h"
#include "qttestqtarrowitemsmenudialog.h"
#include "qttestqtroundededitrectitemmenudialog.h"
#include "qttestqtroundedrectitemmenudialog.h"
#include "ribi_regex.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtbrainweavermenudialog.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbMenuDialog::QtPvdbMenuDialog(QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbMenuDialog),
    m_file{},
    m_show_child_dialogs_modal(true)
{
  ui->setupUi(this);
}

ribi::pvdb::QtPvdbMenuDialog::~QtPvdbMenuDialog() noexcept
{
  delete ui;
}

void ribi::pvdb::QtPvdbMenuDialog::keyPressEvent(QKeyEvent* e) noexcept
{
  assert(e);
  if (e->key()  == Qt::Key_Escape) { close(); return; }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_assessor_clicked() noexcept
{
  QtPvdbAssessorMenuDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); } //For testing
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_rate_concept_clicked() noexcept
{
  //Obtain an empty file
  File file;
  //Use HeteromorphousTestConceptMap[17] to check for subconcept maps with many examples
  //Use HeteromorphousTestConceptMap[18] to check for subconcept maps with large texts
  //Use HeteromorphousTestConceptMap[19] to check for connection to focus with ...
  {
    const ribi::cmap::ConceptMap concept_map
      = ribi::cmap::ConceptMapFactory().GetTest(6);
    assert(boost::num_vertices(concept_map) > 0);
    file.SetConceptMap(concept_map);
  }
  //Obtain a random sub-concept-map
  const std::vector<ribi::cmap::ConceptMap> concept_maps = CreateDirectNeighbourConceptMaps(file.GetConceptMap());
  //Display this random concept map
  const int index = std::rand() % concept_maps.size();
  const ribi::cmap::ConceptMap concept_map = concept_maps[ index ];
  //Create and show the dialog
  boost::shared_ptr<pvdb::QtRateConceptMapDialog> d(
    new pvdb::QtRateConceptMapDialog(file));
  if (m_show_child_dialogs_modal) { this->ShowChild(d.get()); } else { d->close(); } //For testing
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_rate_concept_map_clicked() noexcept
{
  File file;
  const ribi::cmap::ConceptMap concept_map
    = ribi::cmap::ConceptMapFactory().GetTest(6);
  file.SetConceptMap(concept_map);
  QtRateConceptMapDialog d(file);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_rate_examples_clicked() noexcept
{
  using namespace cmap;
  const int index = 2;
  assert(index < ConceptFactory().GetNumberOfTests());
  const ribi::cmap::Concept concept = ConceptFactory().GetTests().at(index);
  boost::shared_ptr<QtRateExamplesDialogNewName> d(new QtRateExamplesDialogNewName(concept));
  if (m_show_child_dialogs_modal) { this->ShowChild(d.get()); } else { d->close(); } //For testing
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_rating_clicked() noexcept
{
  const int test = 4;
  assert(test < FileFactory().GetNumberOfTests());
  const File file = pvdb::FileFactory().GetTests().at(test);

  QtPvdbRatingDialog d(file);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_student_clicked() noexcept
{
  if (!m_show_child_dialogs_modal) return;

  const auto d = pvdb::QtFileDialog::GetOpenFileDialog();
  d->setWindowTitle("Kies een assessment bestand");
  const int status = d->exec();
  if (status == QDialog::Rejected) return;
  const auto v = d->selectedFiles();
  if (!v.isEmpty())
  {
    assert(v.size() == 1);
    const std::string filename = v[0].toStdString();
    try
    {
      const File file = pvdb::LoadFile(filename);
      QtPvdbStudentMenuDialog d(file);
      if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); } //For testing
    }
    catch (...)
    {
      //Gotta catch 'm all
    }
  }

}

void ribi::pvdb::QtPvdbMenuDialog::on_button_test_cluster_clicked() noexcept
{
  File file;
  assert(file.GetCluster().Empty());
  assert(!boost::num_vertices(file.GetConceptMap()));
  {
    const std::string question = "qtvdbmenudialog.cpp 79?";
    ribi::cmap::ConceptMap concept_map;
    add_custom_vertex(
      ribi::cmap::Node(ribi::cmap::Concept(question)),concept_map
    );
    assert(boost::num_vertices(concept_map) > 0);
    file.SetQuestion(question);
    file.SetConceptMap(concept_map);

    assert(file.GetCluster().Empty());
    assert(boost::num_vertices(file.GetConceptMap()) > 0);
    assert(file.GetQuestion() == question);
  }
  QtPvdbClusterDialog d(file);

  assert(file.GetCluster().Empty());
  assert(boost::num_vertices(file.GetConceptMap()) > 0);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_overview_clicked() noexcept
{
  const QString old_title = this->windowTitle();
  this->setWindowTitle("Loading, please wait...");
  QtPvdbOverviewDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_about_clicked() noexcept
{
  const auto d = QtPvdbAboutDialog().Get();
  if (m_show_child_dialogs_modal)
  {
    this->hide();
    d->exec();
    this->show();
  }
  else
  {
    d->close();
  }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_view_files_clicked() noexcept
{
  QtPvdbViewFilesDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_test_qtroundededitrectitem_clicked() noexcept
{
  QtTestQtRoundedEditRectItemMenuDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_test_arrowitems_clicked() noexcept
{
  QtTestQtArrowItemsMenuDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_create_test_files_clicked() noexcept
{
  //Obtain the artificial concept maps
  const std::vector<File > v = pvdb::FileFactory().GetTests();
  const int sz = boost::numeric_cast<int>(v.size());
  for(int i=0; i!=sz; ++i)
  {
    File file = v[i];
    const std::string s
      = boost::lexical_cast<std::string>(i + 5)
      + "."
      + pvdb::File::GetFilenameExtension();
    file.Save(s);
  }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_modify_stylesheet_clicked() noexcept
{
  QtStyleSheetSetterMainDialog d(qApp->styleSheet().toStdString());
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
  qApp->setStyleSheet(d.GetStyleSheet().c_str());
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_print_concept_map_clicked() noexcept
{
  on_button_create_test_files_clicked();
  const std::string filename = "1." + pvdb::File::GetFilenameExtension();
  assert(fileio::FileIo().IsRegularFile(filename));
  const File file = pvdb::LoadFile(filename);

  QtPvdbPrintConceptMapDialog d(file);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_print_rating_clicked() noexcept
{
  on_button_create_test_files_clicked();
  const std::string filename = "1." + pvdb::File::GetFilenameExtension();
  assert(fileio::FileIo().IsRegularFile(filename));
  const File file = pvdb::LoadFile(filename);

  QtPvdbPrintRatingDialog d(file);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_rate_concept_auto_clicked() noexcept
{

  const ribi::cmap::ConceptMap concept_map
    = ribi::cmap::ConceptMapFactory().Get6();
  boost::shared_ptr<cmap::QtRateConceptTallyDialog> d(
    new cmap::QtRateConceptTallyDialog(concept_map));
  if (m_show_child_dialogs_modal) { this->ShowChild(d.get()); } else { d->close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_test_create_sub_concept_map_clicked() noexcept
{
  QtPvdbTestCreateSubConceptMapDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_test_conceptmaps_clicked()
{
  cmap::QtTestMenuDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_test_conceptmap_clicked()
{
  const int test = 4;
  assert(test < static_cast<int>(pvdb::FileFactory().GetNumberOfTests()));
  const File file = pvdb::FileFactory().GetTests().at(test);

  QtPvdbConceptMapDialog d(file);
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}

void ribi::pvdb::QtPvdbMenuDialog::on_button_test_qtroundedrectitem_clicked()
{
  QtTestQtRoundedRectItemMenuDialog d;
  if (m_show_child_dialogs_modal) { this->ShowChild(&d); } else { d.close(); }
}
