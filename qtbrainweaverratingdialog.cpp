#include "qtbrainweaverratingdialog.h"

#include <cassert>

#include <QDebug>
#include <QKeyEvent>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QPainter>
#include <QLayout>
#include <QPrinter>
#include <QTableWidget>

#include "conceptmap.h"
#include "qtconceptmap.h"
#include "qtbrainweaverprintratingdialog.h"
#include "qtconceptmap.h"
#include "qtbrainweaverdisplay.h"
#include "qtbrainweaverfiledialog.h"
#include "brainweaverfile.h"

#include "ui_qtbrainweaverratingdialog.h"


ribi::braw::QtRatingDialog::QtRatingDialog(
  const File file,
  QWidget* parent)
  : QDialog(parent),
    ui(new Ui::QtRatingDialog),
    m_file(file)
{
  if (boost::num_vertices(file.GetConceptMap()) == 0)
  {
    std::stringstream msg;
    msg << __func__ << ": must have at least one node";
    throw std::invalid_argument(msg.str());
  }

  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help

  //Student name
  {
    const std::string s = "Naam student: " + file.GetStudentName();
    ui->label_student_name->setText(s.c_str());
  }
  //Assessor name
  {
    ui->label_assessor_name->setText("Naam assessor: ");
    if (file.GetAssessorName().empty())
    {
      ui->edit_name->setFocus(); //Needs to be done in showEvent
      ui->button_print->setEnabled(false);
    }
    else
    {
      ui->edit_name->setText(file.GetAssessorName().c_str());
      //ui->edit_name->setReadOnly(true); //TVDB request
      ui->button_print->setEnabled(true);
    }
  }
  //Add rated concepts
  {
    assert(ui->scrollAreaWidgetContents->layout());
    ui->scrollAreaWidgetContents->layout()->addWidget(
      new QLabel(
        "Overzicht concepten",
        this
      )
    );
    ui->scrollAreaWidgetContents->layout()->addWidget(
      QtDisplay().CreateRatedConceptsWidget(file, this)
    );
  }
  //Add tallied examples
  {
    assert(ui->scrollAreaWidgetContents->layout());
    ui->scrollAreaWidgetContents->layout()->addWidget(
      new QLabel(
        "Verdeling van de voorbeelden/toelichting over de zes objecten van kennis",
        this
      )
    );
    ui->scrollAreaWidgetContents->layout()->addWidget(
      QtDisplay().CreateTalliedCompetenciesWidget(file, this)
    );
  }

  //Add diagnostics
  {
    assert(ui->scrollAreaWidgetContents->layout());
    ui->scrollAreaWidgetContents->layout()->addWidget(
      new QLabel(
        "Gevonden waarden",
        this
      )
    );
    ui->scrollAreaWidgetContents->layout()->addWidget(
      QtDisplay().CreateDiagnosticsWidget(file, this)
    );
  }
  //Center the dialog
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(screen.adjusted(64,64,-64,-64));
    this->move(screen.center() - this->rect().center());
  }
}

ribi::braw::QtRatingDialog::~QtRatingDialog() noexcept
{
  delete ui;
}

void ribi::braw::QtRatingDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key() == Qt::Key_Escape)
  {
    close();
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
      Save(QtFileDialog::m_last_file.toStdString());
      return;
    }
  }
}

void ribi::braw::QtRatingDialog::on_button_save_clicked()
{
  //Temporarily disable to widget, otherwise saving cannot succeed
  this->setEnabled(false);

  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla het assessment invoer-bestand op");
  const int status = d->exec();
  this->setEnabled(true);
  if (status == QDialog::Rejected)
  {
    return;
  }
  assert(d->selectedFiles().size() == 1);
  const std::string filename = d->selectedFiles()[0].toStdString();
  assert(!filename.empty());
  QtFileDialog::m_last_file = filename.c_str();
  Save(filename);
}

void ribi::braw::QtRatingDialog::Save(const std::string& filename) const
{
  m_file.Save(filename);
}

void ribi::braw::QtRatingDialog::on_button_print_clicked()
{
  this->setEnabled(false);
  std::unique_ptr<QtPrintRatingDialog> d{
    new QtPrintRatingDialog(m_file)
  };
  d->show();
  d->Print();
  this->setEnabled(true);
}

void ribi::braw::QtRatingDialog::on_edit_name_textEdited(const QString &arg1)
{
  if (arg1.size() > 1)
  {
    m_file.SetAssessorName(arg1.toStdString());
    ui->button_print->setEnabled(true);
  }
  else
  {
    ui->button_print->setEnabled(false);
  }
}

void ribi::braw::QtRatingDialog::showEvent(QShowEvent *)
{
  ui->edit_name->setFocus();
}
