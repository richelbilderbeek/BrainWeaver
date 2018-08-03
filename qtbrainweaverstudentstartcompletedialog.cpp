#include "qtbrainweaverstudentstartcompletedialog.h"

#include <QFileDialog>
#include <QKeyEvent>

#include "qtbrainweaverclusterdialog.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweaverfiledialog.h"
#include "ui_qtbrainweaverstudentstartcompletedialog.h"

ribi::braw::QtStudentStartCompleteDialog::QtStudentStartCompleteDialog(
  const File file,
  QWidget* parent)
  : QDialog(parent),
    ui(new Ui::QtStudentStartCompleteDialog),
    m_back_to_menu(false),
    m_file(file)
{
  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help
}

ribi::braw::QtStudentStartCompleteDialog::~QtStudentStartCompleteDialog() noexcept
{
  delete ui;
}

bool ribi::braw::QtStudentStartCompleteDialog::GoBackToMenu() const noexcept
{
  return m_back_to_menu;
}

void ribi::braw::QtStudentStartCompleteDialog::keyPressEvent(QKeyEvent* e)
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
      Save();
      return;
    }
    assert(!QtFileDialog::m_last_file.isEmpty());
    Save(QtFileDialog::m_last_file);
    return;
  }
  QDialog::keyPressEvent(e);
}

void ribi::braw::QtStudentStartCompleteDialog::on_button_start_associate_clicked()
{
  StartAssociate();
}

void ribi::braw::QtStudentStartCompleteDialog::on_button_start_construct_clicked()
{
  StartConstruct();
}

void ribi::braw::QtStudentStartCompleteDialog::Save()
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

void ribi::braw::QtStudentStartCompleteDialog::Save(const QString& filename)
{
  m_file.Save(filename.toStdString());
}

void ribi::braw::QtStudentStartCompleteDialog::StartAssociate()
{
  auto * const d{
    new QtClusterDialog(m_file, this)
  };
  d->exec();
}

void ribi::braw::QtStudentStartCompleteDialog::StartConstruct()
{
  auto * const d{
    new QtConceptMapDialog(m_file, this)
  };
  d->exec();
}
