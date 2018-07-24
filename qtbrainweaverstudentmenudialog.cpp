#include "qtbrainweaverstudentmenudialog.h"

#include <cassert>

#include <QFileDialog>
#include <QKeyEvent>

#include "qtbrainweaveraboutdialog.h"
#include "qtbrainweaverfiledialog.h"
#include "qtbrainweaverstudentstartcompletedialog.h"

#include "ui_qtbrainweaverstudentmenudialog.h"

ribi::braw::QtStudentMenuDialog::QtStudentMenuDialog(
  const File file, QWidget* parent
) : QDialog(parent),
    ui(new Ui::QtStudentMenuDialog),
    m_file(file)
{
  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help

  if (!m_file.GetStudentName().empty())
  {
    SetName(m_file.GetStudentName().c_str());
  }
  on_edit_name_textChanged(ui->edit_name->text());

  connect(
    ui->button_quit,
    SIGNAL(clicked(bool)),
    this,
    SLOT(close())
  );
}

ribi::braw::QtStudentMenuDialog::~QtStudentMenuDialog() noexcept
{
  delete ui;
}

QString ribi::braw::QtStudentMenuDialog::GetName() const noexcept
{
  return ui->edit_name->text();
}

void ribi::braw::QtStudentMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape)
  {
    close();
    return;
  }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S)
  {
    if (QtFileDialog::m_last_file.isEmpty())
    {
      on_button_save_clicked();
      return;
    }
    else
    {
      Save(QtFileDialog::m_last_file);
      return;
    }
  }
  QDialog::keyPressEvent(e);
}

void ribi::braw::QtStudentMenuDialog::on_button_about_clicked()
{
  std::unique_ptr<ribi::braw::QtAboutDialog> d{new ribi::braw::QtAboutDialog};
  assert(d);
  this->hide();
  d->exec();
  this->show();
}

void ribi::braw::QtStudentMenuDialog::on_button_start_clicked()
{
  m_file.SetStudentName(ui->edit_name->text().toStdString());
  auto * const d{
    new QtStudentStartCompleteDialog(m_file, this)
  };
  d->exec();
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
  const QString filename = d->selectedFiles()[0];
  QtFileDialog::m_last_file = filename;
  assert(!filename.isEmpty());
  Save(filename);
}

void ribi::braw::QtStudentMenuDialog::Save(const QString& filename)
{
  m_file.SetStudentName(ui->edit_name->text().toStdString());
  m_file.Save(filename.toStdString());
}

void ribi::braw::QtStudentMenuDialog::SetName(const QString& name)
{
  ui->edit_name->setText(name);
}
