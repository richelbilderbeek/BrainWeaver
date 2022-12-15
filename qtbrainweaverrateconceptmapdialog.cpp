#include "qtbrainweaverrateconceptmapdialog.h"

#include <cassert>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QKeyEvent>

#include "qtbrainweaverfiledialog.h"
#include "qtbrainweaverratingdialog.h"
#include "qtconceptmap.h"
#include "ui_qtbrainweaverrateconceptmapdialog.h"

ribi::braw::QtRateConceptMapDialog::QtRateConceptMapDialog(
  const File& file,
  QWidget* parent)
  : QDialog(parent),
  ui(new Ui::QtRateConceptMapDialog),
  m_file(file),
  m_qtconcept_map(new ::ribi::cmap::QtConceptMap(file.GetRating()))
{
  //Checked by File
  assert(CountCenterNodes(file.GetConceptMap()) == 1);

  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help

  m_qtconcept_map->SetConceptMap(file.GetConceptMap());
  m_qtconcept_map->SetMode(ribi::cmap::Mode::rate);

  {
    assert(!ui->widget->layout());
    QLayout * const layout = new QGridLayout;
    ui->widget->setLayout(layout);
    layout->addWidget(m_qtconcept_map);
  }

  {
    const std::string s = "Naam student: " + m_file.GetStudentName();
    ui->label_name->setText(s.c_str());
  }

  //Center the dialog
  {

    // const QRect screen = QApplication::desktop()->screenGeometry();
    const QRect screen{QApplication::desktop()->geometry()};
    this->setGeometry(screen.adjusted(64,64,-64,-64));
    this->move( screen.center() - this->rect().center() );
  }
}

ribi::braw::QtRateConceptMapDialog::~QtRateConceptMapDialog() noexcept
{
  this->m_qtconcept_map->StopTimer();
  delete ui;
}

void ribi::braw::QtRateConceptMapDialog::changeEvent(QEvent * event)
{
  if (event->type() == QEvent::EnabledChange)
  {
    if (isEnabled())
    {
      this->m_qtconcept_map->StartTimer();
    }
    else
    {
      this->m_qtconcept_map->StopTimer();
    }
  }
}

const ribi::braw::File& ribi::braw::QtRateConceptMapDialog::GetFile() const noexcept
{
  return m_file;
}

ribi::cmap::QtConceptMap * ribi::braw::QtRateConceptMapDialog::GetWidget()
{
  assert(m_qtconcept_map);
  return m_qtconcept_map;
}

void ribi::braw::QtRateConceptMapDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key() == Qt::Key_Escape)
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
    Save(QtFileDialog::m_last_file.toStdString());
    return;
  }
  m_qtconcept_map->keyPressEvent(e);
  if (!e->isAccepted())
  {
    QDialog::keyPressEvent(e);
  }
}

void ribi::braw::QtRateConceptMapDialog::on_button_next_clicked()
{
  assert(IsCenterNode(ribi::cmap::GetFirstNode(m_file.GetConceptMap())));
  m_file.SetConceptMap(m_qtconcept_map->ToConceptMap());
  assert(
    ribi::cmap::HasSimilarData(
      m_qtconcept_map->ToConceptMap(),
      m_file.GetConceptMap(),
      0.001
    )
  );
  assert(IsCenterNode(ribi::cmap::GetFirstNode(m_file.GetConceptMap())));
  m_qtconcept_map->StopTimer();
  m_qtconcept_map->setEnabled(false);
  auto * const d{
    new QtRatingDialog(m_file, this)
  };
  d->exec();
  m_qtconcept_map->setEnabled(true);
  m_qtconcept_map->StartTimer();
}

void ribi::braw::QtRateConceptMapDialog::Save()
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla het assessment invoer-bestand op");
  this->setEnabled(false);
  const int status = d->exec();
  this->setEnabled(true);
  if (status == QDialog::Rejected || d->selectedFiles().empty())
  {
    this->show();
    return;
  }
  assert(d->selectedFiles().size() == 1);
  const std::string filename = d->selectedFiles()[0].toStdString();
  assert(!filename.empty());
  QtFileDialog::m_last_file = filename.c_str();
  Save(filename);
  this->show();
}


void ribi::braw::QtRateConceptMapDialog::Save(const std::string& filename)
{
  m_file.SetConceptMap(m_qtconcept_map->ToConceptMap());
  assert(
    HasSimilarData(
      m_qtconcept_map->ToConceptMap(),
      m_file.GetConceptMap(),
      0.001
    )
  );
  //const ribi::cmap::ConceptMap concept_map = GetWidget()->GetConceptMap();
  //assert(boost::num_vertices(concept_map) > 0);
  //m_file.SetConceptMap(concept_map);
  //assert(IsEqual(*m_file.GetConceptMap(),*GetWidget()->GetConceptMap()));
  m_file.Save(filename);
}

void ribi::braw::QtRateConceptMapDialog::on_button_save_clicked()
{
  Save();
}

void ribi::braw::QtRateConceptMapDialog::showEvent(QShowEvent *)
{
  const QRectF all_items_rect = m_qtconcept_map->scene()->itemsBoundingRect();
  m_qtconcept_map->fitInView(all_items_rect, Qt::KeepAspectRatio);
  this->m_qtconcept_map->setFocus();
}
