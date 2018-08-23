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
  if (e->key() == Qt::Key_Escape)
  {
    close();
    return;
  }
  //QuickSave
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S)
  {
    if (QtFileDialog::m_last_file.isEmpty())
    {
      Save();
      return;
    }
    assert(!QtFileDialog::m_last_file.isEmpty());
    Save(QtFileDialog::m_last_file);
    return;
  }
}

void ribi::braw::QtAssessorMenuDialog::on_button_create_assessment_clicked()
{
  auto * const d{
    new QtCreateAssessmentDialog(this)
  };
  d->exec();

  //TODO: m_file = d->ToFile();
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

  //TODO: m_file = d->ToFile();
}

void ribi::braw::QtAssessorMenuDialog::Save() const
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla de voortgang op");
  const int status = d->exec();
  if (status == QDialog::Rejected) return;
  assert(d->selectedFiles().size() == 1);
  const QString filename = d->selectedFiles()[0];
  QtFileDialog::m_last_file = filename;
  Save(filename);
}


void ribi::braw::QtAssessorMenuDialog::Save(const QString& filename) const
{
  m_file.Save(filename.toStdString());
}
