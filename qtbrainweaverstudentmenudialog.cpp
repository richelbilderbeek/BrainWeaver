#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtbrainweaverstudentmenudialog.h"

#include <cassert>
#include <memory>

#include <QKeyEvent>
#include <QFileDialog>

#include "brainweaverfile.h"
#include "qtbrainweaveraboutdialog.h"
#include "qtbrainweaverfiledialog.h"
#include "qtbrainweaverstudentstartcompletedialog.h"

#include "ui_qtbrainweaverstudentmenudialog.h"
#pragma GCC diagnostic pop

ribi::braw::QtStudentMenuDialog::QtStudentMenuDialog(
  const File file, QWidget* parent
) : QtDialog(parent),
    ui(new Ui::QtStudentMenuDialog),
    m_file(file)
{
  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help

  if (!m_file.GetStudentName().empty())
  {
    SetName(m_file.GetStudentName());
  }
  on_edit_name_textChanged(ui->edit_name->text());
}

ribi::braw::QtStudentMenuDialog::~QtStudentMenuDialog() noexcept
{
  delete ui;
}

std::string ribi::braw::QtStudentMenuDialog::GetName() const noexcept
{
  return ui->edit_name->text().toStdString();
}

void ribi::braw::QtStudentMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { emit remove_me(this); return; }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S)
  {
    on_button_save_clicked(); return;
  }
  QDialog::keyPressEvent(e);
}

void ribi::braw::QtStudentMenuDialog::on_button_about_clicked()
{
  std::unique_ptr<ribi::braw::QtAboutDialog> d{new ribi::braw::QtAboutDialog};
  assert(d);
  //const auto d(QtAboutDialog().Get());
  this->hide();
  d->exec();
  this->show();
}

void ribi::braw::QtStudentMenuDialog::on_button_quit_clicked()
{
  emit remove_me(this);
}

void ribi::braw::QtStudentMenuDialog::on_button_start_clicked()
{
  m_file.SetStudentName(ui->edit_name->text().toStdString());
  QtStudentStartCompleteDialog * const d{
    new QtStudentStartCompleteDialog(m_file)
  };
  emit add_me(d);
}

void ribi::braw::QtStudentMenuDialog::on_edit_name_textChanged(const QString &arg1)
{
  //Enable start button when student has entered at least two characters
  assert(ui->edit_name->text() == arg1);
  if (arg1.size() > 1)
  {
    ui->button_start->setEnabled(true);
  }
  else
  {
    ui->button_start->setEnabled(false);
  }
}

void ribi::braw::QtStudentMenuDialog::on_button_save_clicked()
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla de concept map op");
  const int status = d->exec();
  if (status == QDialog::Rejected)
  {
    return;
  }
  assert(d->selectedFiles().size() == 1);
  const std::string filename = d->selectedFiles()[0].toStdString();
  assert(!filename.empty());
  Save(filename);
}

void ribi::braw::QtStudentMenuDialog::Save(const std::string& filename)
{
  m_file.SetStudentName(ui->edit_name->text().toStdString());
  m_file.Save(filename);
}

void ribi::braw::QtStudentMenuDialog::SetName(const std::string& name)
{
  ui->edit_name->setText(name.c_str());
}
