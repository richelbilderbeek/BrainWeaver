#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtbrainweavercreateassessmentcompletedialog.h"

#include <sstream>
#include <stdexcept>

#include <QKeyEvent>
#include <QFileDialog>

#include "conceptmap.h"
#include "brainweaverfile.h"
#include "conceptmapfactory.h"
#include "qtbrainweaverfiledialog.h"

#include "ui_qtbrainweavercreateassessmentcompletedialog.h"

#include "trace.h"
#pragma GCC diagnostic pop

ribi::braw::QtCreateAssessmentCompleteDialog::QtCreateAssessmentCompleteDialog(QWidget* parent)
  : QtDialog(parent),
    ui(new Ui::QtCreateAssessmentCompleteDialog),
    m_back_to_menu(false)
{
  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help
}

ribi::braw::QtCreateAssessmentCompleteDialog::~QtCreateAssessmentCompleteDialog() noexcept
{
  delete ui;
}

std::string ribi::braw::QtCreateAssessmentCompleteDialog::GetQuestion() const noexcept
{
  return ui->edit->text().toStdString();
}

void ribi::braw::QtCreateAssessmentCompleteDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape)
  {
    emit remove_me(this);
    return;
  }
}

void ribi::braw::QtCreateAssessmentCompleteDialog::on_button_save_clicked()
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla het assessment invoer-bestand op");
  const int status = d->exec();
  if (status == QDialog::Rejected)
  {
    this->show();
    return;
  }
  assert(d->selectedFiles().size() == 1);
  const std::string filename = d->selectedFiles()[0].toStdString();
  assert(!filename.empty());
  Save(filename);
  m_back_to_menu = true;
  emit remove_me(this);
}

void ribi::braw::QtCreateAssessmentCompleteDialog::Save(const std::string& filename) const
{
  const std::string question = ui->edit->text().toStdString();
  File file;
  file.SetQuestion(question);
  assert(file.GetQuestion() == question);
  file.Save(filename);
}

void ribi::braw::QtCreateAssessmentCompleteDialog::SetQuestion(const std::string& question)
{
  ui->edit->setText(question.c_str());
}

void ribi::braw::QtCreateAssessmentCompleteDialog::on_edit_textChanged(const QString &arg1)
{
  assert(ui->edit->text() == arg1);
  ui->button_save->setEnabled(!arg1.isEmpty());

}
