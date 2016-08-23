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

#include <QDebug>
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
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapexamples.h"
#include "conceptmapfactory.h"
#include "conceptmapcenternodefactory.h"
#include "conceptmapnodefactory.h"
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

ribi::braw::QtMenuDialog::QtMenuDialog(QWidget* parent)
  : QtDialog(parent),
    ui(new Ui::QtMenuDialog)
    //m_file{}
{
  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help
}

ribi::braw::QtMenuDialog::~QtMenuDialog() noexcept
{
  delete ui;
}

void ribi::braw::QtMenuDialog::keyPressEvent(QKeyEvent* e) noexcept
{
  assert(e);
  if (e->key() == Qt::Key_Escape) { emit remove_me(this); return; }
}

void ribi::braw::QtMenuDialog::on_button_assessor_clicked() noexcept
{
  QtAssessorMenuDialog * const d = new QtAssessorMenuDialog;
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_rate_concept_clicked() noexcept
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
    //Question and first node must match
    file.SetQuestion(ribi::cmap::GetCenterNode(concept_map).GetName());
    file.SetConceptMap(concept_map);
  }
  //Obtain a random sub-concept-map
  const std::vector<ribi::cmap::ConceptMap> concept_maps = CreateDirectNeighbourConceptMaps(file.GetConceptMap());
  //Display this random concept map
  const int index = std::rand() % concept_maps.size();
  //const ribi::cmap::ConceptMap concept_map = concept_maps[ index ];
  //Create and show the dialog
  QtRateConceptMapDialog * const d{
    new QtRateConceptMapDialog(file)
  };
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_rate_concept_map_clicked() noexcept
{
  File file;
  const ribi::cmap::ConceptMap concept_map
    = ribi::cmap::ConceptMapFactory().GetTest(6);
  file.SetQuestion(ribi::cmap::GetCenterNode(concept_map).GetName());
  file.SetConceptMap(concept_map);
  QtRateConceptMapDialog * const d{
    new QtRateConceptMapDialog(file)
  };
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_rate_examples_clicked() noexcept
{
  using namespace cmap;
  const int index = 2;
  assert(index < ConceptFactory().GetNumberOfTests());
  const ribi::cmap::Concept concept = ConceptFactory().GetTests().at(index);
  QtRateExamplesDialogNewName * const d{
    new QtRateExamplesDialogNewName(concept)
  };
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_rating_clicked() noexcept
{
  const int test = 4;
  assert(test < FileFactory().GetNumberOfTests());
  const File file = FileFactory().GetTests().at(test);

  QtRatingDialog * const d{
    new QtRatingDialog(file)
  };
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_student_clicked() noexcept
{
  const auto d = QtFileDialog::GetOpenFileDialog();
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
      const File file = LoadFile(filename);
      QtStudentMenuDialog * const d{
        new QtStudentMenuDialog(file)
      };
      emit add_me(d);
    }
    catch (...)
    {
      //Gotta catch 'm all
    }
  }

}

void ribi::braw::QtMenuDialog::on_button_test_cluster_clicked() noexcept
{
  File file;
  const std::string question = "A good question to test the clustering dialog is ...";
  file.SetQuestion(question);
  Cluster cluster;
  cluster.Add(ribi::cmap::Concept("A"));
  cluster.Add(ribi::cmap::Concept("B"));
  cluster.Add(ribi::cmap::Concept("C"));
  file.SetCluster(cluster);
  QtClusterDialog * const d{
    new QtClusterDialog(file)
  };
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_overview_clicked() noexcept
{
  this->setWindowTitle("Loading, please wait...");
  QtOverviewDialog * const d{
    new QtOverviewDialog
  };
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_about_clicked() noexcept
{
  ribi::braw::QtAboutDialog * const d = new ribi::braw::QtAboutDialog;
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_test_qtroundededitrectitem_clicked() noexcept
{
  QtTestQtRoundedEditRectItemMenuDialog * const d{
    new QtTestQtRoundedEditRectItemMenuDialog
  };
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_test_arrowitems_clicked() noexcept
{
  QtTestQtArrowItemsMenuDialog * const d{
    new QtTestQtArrowItemsMenuDialog
  };
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_modify_stylesheet_clicked() noexcept
{
  QtStyleSheetSetterMainDialog * const d{
    new QtStyleSheetSetterMainDialog(qApp->styleSheet().toStdString())
  };
  emit add_me(d);

  //Will fail due to #85 at https://github.com/richelbilderbeek/Brainweaver/issues/85
  //The former architecture showed d modally, thus at this point d would have
  //a new file now. In this case, the file is read before modification
  qApp->setStyleSheet(d->GetStyleSheet().c_str());
}

void ribi::braw::QtMenuDialog::on_button_print_concept_map_clicked() noexcept
{
  QtPrintConceptMapDialog * const d{
    new QtPrintConceptMapDialog(FileFactory().GetTests().front())
  };
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_print_rating_clicked() noexcept
{
  QtPrintConceptMapDialog * const d{
    new QtPrintConceptMapDialog(FileFactory().GetTests().front())
  };
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_rate_concept_auto_clicked() noexcept
{

  const ribi::cmap::ConceptMap concept_map
    = ribi::cmap::ConceptMapFactory().Get6();
  ribi::cmap::QtRateConceptTallyDialog * const d{
    new cmap::QtRateConceptTallyDialog(concept_map)
  };
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_test_conceptmaps_clicked()
{
  ribi::cmap::QtTestMenuDialog * const d{
    new ribi::cmap::QtTestMenuDialog
  };
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_test_conceptmap_clicked()
{
  const int test = 4;
  assert(test < static_cast<int>(FileFactory().GetNumberOfTests()));
  const File file = FileFactory().GetTests().at(test);

  try
  {
    QtConceptMapDialog * const d{
      new QtConceptMapDialog(file)
    };
    emit add_me(d);
  }
  catch (std::exception& )
  {
    //Keep recovery filename
    qDebug() << "Crash detected, recovery file saved";
  }
}

void ribi::braw::QtMenuDialog::on_button_test_qtroundedrectitem_clicked()
{
  QtTestQtRoundedRectItemMenuDialog * const d{
    new QtTestQtRoundedRectItemMenuDialog
  };
  emit add_me(d);
}

void ribi::braw::QtMenuDialog::on_button_empty_qtconceptmap_clicked()
{
  const int test{0};
  assert(test < static_cast<int>(FileFactory().GetNumberOfTests()));
  const File file = FileFactory().GetTests().at(test);

  QtConceptMapDialog * const d{new QtConceptMapDialog(file)};
  emit add_me(d);
}
