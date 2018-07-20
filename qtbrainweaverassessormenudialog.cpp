#include "qtbrainweaverassessormenudialog.h"

#include <QFileDialog>
#include <QKeyEvent>

#include "qtbrainweaveraboutdialog.h"
#include "qtconceptmaprateconceptdialog.h"
#include "qtbrainweavercreateassessmentdialog.h"

#include "qtbrainweaverrateconceptmapdialog.h"
#include "qtbrainweaverfiledialog.h"

#include "ui_qtbrainweaverassessormenudialog.h"


ribi::braw::QtAssessorMenuDialog::QtAssessorMenuDialog(QWidget* parent)
  : QDialog(parent),
    ui(new Ui::QtAssessorMenuDialog)
{
  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help

  connect(
    ui->button_quit,
    SIGNAL(clicked(bool)),
    this,
    SLOT(close())
  );
}

ribi::braw::QtAssessorMenuDialog::~QtAssessorMenuDialog() noexcept
{
  delete ui;
}

void ribi::braw::QtAssessorMenuDialog::Assess(const std::string& filename)
{
  File file = LoadFile(filename);
  auto * const d = new QtRateConceptMapDialog(file, this);
  d->exec();
  file = d->GetFile();
}

void ribi::braw::QtAssessorMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key() == Qt::Key_Escape || (e->key() == Qt::Key_F4 && (e->modifiers() & Qt::AltModifier)))
  {
    close();
    return;
  }
}

void ribi::braw::QtAssessorMenuDialog::on_button_create_assessment_clicked()
{
  auto * const d{
    new QtCreateAssessmentDialog(this)
  };
  d->exec();
}


void ribi::braw::QtAssessorMenuDialog::on_button_about_clicked()
{
  auto * const d{
    new ribi::braw::QtAboutDialog(this)
  };
  d->exec();
}

void ribi::braw::QtAssessorMenuDialog::on_button_assess_result_clicked()
{
  //Load assessent file
  const auto d = QtFileDialog().GetOpenFileDialog();
  d->setWindowTitle("Kies een assessment bestand");
  const int status = d->exec();
  if (status == QDialog::Rejected) return;
  const auto v = d->selectedFiles();
  if (!v.isEmpty())
  {
    assert(v.size() == 1);
    const std::string filename = v[0].toStdString();
    Assess(filename);
  }
}
