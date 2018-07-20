#include "qtbrainweavermenudialog.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLayout>
#include <QVBoxLayout>
#include <QTableWidget>
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
//#include "plane.h"
#include "qtbrainweaveraboutdialog.h"
#include "qtbrainweaverassessormenudialog.h"
#include "qtbrainweaverclusterdialog.h"
#include "qtbrainweaverclusterwidget.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweavercreateassessmentdialog.h"
#include "qtbrainweaverdisplay.h"
#include "qtbrainweaverfiledialog.h"
#include "qtbrainweaveroverviewdialog.h"
#include "qtbrainweaverprintconceptmapdialog.h"
#include "qtbrainweaverprintratingdialog.h"
#include "qtbrainweaverrateconceptmapdialog.h"
#include "qtbrainweaverratingdialog.h"
#include "qtbrainweaverstudentmenudialog.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmaprateconceptdialog.h"
#include "qtconceptmaprateconcepttallydialog.h"
#include "qtconceptmaprateexamplesdialog.h"
#include "qtstylesheetsettermaindialog.h"
#include "ribi_regex.h"
#include "ui_qtbrainweavermenudialog.h"


ribi::braw::QtMenuDialog::QtMenuDialog(QWidget* parent)
  : QDialog(parent),
    ui(new Ui::QtMenuDialog)
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
  if (e->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::braw::QtMenuDialog::on_button_about_clicked() noexcept
{
  ribi::braw::QtAboutDialog * const d = new ribi::braw::QtAboutDialog;
  d->exec();
}

void ribi::braw::QtMenuDialog::on_button_assessor_clicked() noexcept
{
  auto * const d{
    new QtAssessorMenuDialog(this)
  };
  d->exec();
}

void ribi::braw::QtMenuDialog::on_button_overview_clicked() noexcept
{
  auto * const d{
    new QtOverviewDialog(this)
  };
  d->exec();
}

void ribi::braw::QtMenuDialog::on_button_rate_concept_clicked() noexcept
{
  const auto concept_map
    = ribi::cmap::ConceptMapFactory().GetRateConceptTallyDialogExample();
  auto * const d{
    new ribi::cmap::QtRateConceptDialog(
      concept_map,
      ribi::cmap::CreateDefaultRating(),
      this
    )
  };
  d->exec();
}

void ribi::braw::QtMenuDialog::on_button_rate_concept_map_clicked() noexcept
{
  const File file = FileFactory().Get2();
  QtRateConceptMapDialog * const d{
    new QtRateConceptMapDialog(file, this)
  };
  d->exec();
}

void ribi::braw::QtMenuDialog::on_button_rate_examples_clicked() noexcept
{
  const auto concept = ribi::cmap::ConceptFactory().Get2();
  auto d{
    new ribi::cmap::QtRateExamplesDialog(concept, this)
  };
  d->exec();
}

void ribi::braw::QtMenuDialog::on_button_rating_clicked() noexcept
{
  const int test = 4;
  assert(test < FileFactory().GetNumberOfTests());
  File file = FileFactory().GetTests().at(test);
  file.SetAssessorName("William Ebright");
  auto * const d{
    new QtRatingDialog(file, this)
  };
  d->exec();
}

void ribi::braw::QtMenuDialog::on_button_student_clicked() noexcept
{
  const auto d = QtFileDialog().GetOpenFileDialog();
  d->setWindowTitle("Kies een assessment bestand");
  const int status = d->exec();
  if (status == QDialog::Rejected) return;
  const auto v = d->selectedFiles();
  if (!v.isEmpty())
  {
    assert(v.size() == 1);
    const std::string filename = v[0].toStdString();
    const File file = LoadFile(filename);
    auto * const menu{
      new QtStudentMenuDialog(file, this)
    };
    menu->exec();
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
    new QtClusterDialog(file, this)
  };
  d->exec();
}

void ribi::braw::QtMenuDialog::on_button_modify_stylesheet_clicked() noexcept
{
  auto * const d{
    new QtStyleSheetSetterMainDialog(
      qApp->styleSheet().toStdString(),
      this
    )
  };
  d->exec();
  //Will fail due to #85 at https://github.com/richelbilderbeek/Brainweaver/issues/85
  //The former architecture showed d modally, thus at this point d would have
  //a new file now. In this case, the file is read before modification
  qApp->setStyleSheet(d->GetStyleSheet().c_str());
}

void ribi::braw::QtMenuDialog::on_button_print_concept_map_clicked() noexcept
{
  auto * const d{
    new QtPrintConceptMapDialog(FileFactory().Get5(), this)
  };
  d->exec();
}

void ribi::braw::QtMenuDialog::on_button_print_rating_clicked() noexcept
{
  auto * const d{
    new QtPrintRatingDialog(FileFactory().Get5())
  };
  d->exec();
}

void ribi::braw::QtMenuDialog::on_button_rate_concept_auto_clicked() noexcept
{
  const auto concept_map
    = ribi::cmap::ConceptMapFactory().GetRateConceptTallyDialogExample();
  auto * const d{
    new cmap::QtRateConceptTallyDialog(
      concept_map,
      ribi::cmap::CreateDefaultRating(),
      this
    )
  };
  d->exec();
}

void ribi::braw::QtMenuDialog::on_button_edit_conceptmap_clicked()
{
  const File file = FileFactory().Get2();
  auto * const d{
    new QtConceptMapDialog(file, this)
  };
  d->exec();
}


void ribi::braw::QtMenuDialog::on_button_edit_concept_clicked()
{
  const auto concept = ribi::cmap::ConceptFactory().Get2();
  ribi::cmap::QtConceptMapConceptEditDialog d(concept);
  d.exec();
}

void ribi::braw::QtMenuDialog::on_button_create_assessment_clicked()
{
  auto * const d{
    new ribi::braw::QtCreateAssessmentDialog()
  };
  d->exec();
}
