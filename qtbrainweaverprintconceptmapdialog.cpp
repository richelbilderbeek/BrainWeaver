#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtbrainweaverprintconceptmapdialog.h"

#include <cassert>
#include <ctime>

#include <boost/numeric/conversion/cast.hpp>

#include <QKeyEvent>

#include <QFileDialog>
#include <QPrinter>
#include <QTimer>

#include "brainweaverfile.h"
#include "conceptmapconcept.h"
#include "conceptmap.h"
#include "conceptmapfactory.h"
#include "qtconceptmapqtnode.h"
#include "get_my_custom_vertexes.h"
#include "qtconceptmapratedconceptdialog.h"
#include "qtbrainweaverfiledialog.h"
#include "ui_qtbrainweaverprintconceptmapdialog.h"
#include "qtconceptmap.h"
#pragma GCC diagnostic pop

ribi::braw::QtPrintConceptMapDialog::QtPrintConceptMapDialog(
  const File& file,
  QWidget *parent)
  : QtDialog(parent),
    ui(new Ui::QtPrintConceptMapDialog),
    m_file(file),
    m_widget(new cmap::QtConceptMap)
{
  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help

  m_widget->SetConceptMap(file.GetConceptMap());
  {
    assert(m_widget);
    assert(ui->frame_concept_map->layout());
    ui->frame_concept_map->layout()->addWidget(m_widget);
  }

  //Allow a QtConceptMapWidget to have no QtExamplesItem
  //This allows to omit showing these in the PDF versions used for printing (#205)
  HideExamplesItem(*m_widget);

  ui->label_student_name->setText(
    ("Concept map van "
      + m_file.GetStudentName()).c_str()
  );
  {
    std::time_t my_time;
    std::time( &my_time );
    const std::tm * const time_and_date = std::localtime(&my_time);
    const std::string s = std::asctime(time_and_date);
    ui->label_date->setText( ("Datum: " + s).c_str());
  }

  //Much work done in ShowEvent
  {
    QTimer::singleShot(1000,this,SLOT(fitConceptMap()));
  }
}

ribi::braw::QtPrintConceptMapDialog::~QtPrintConceptMapDialog() noexcept
{
  delete ui;
}

std::vector<QWidget *> ribi::braw::QtPrintConceptMapDialog::CollectWidgets() const
{
  std::vector<QWidget *> v;
  v.push_back(ui->frame_top);
  v.push_back(ui->frame_concept_map);
  {
    //Add widgets in widget_concept_map_as_text
    const int n = ui->frame_concept_map_as_text->layout()->count();
    for (int i=0; i!=n; ++i)
    {
      v.push_back(ui->frame_concept_map_as_text->layout()->itemAt(i)->widget());
    }
  }
  return v;
}


void ribi::braw::QtPrintConceptMapDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { emit remove_me(this); return; }
}

void ribi::braw::QtPrintConceptMapDialog::on_button_print_clicked()
{
  Print();
}

void ribi::braw::QtPrintConceptMapDialog::Print()
{
  //Start save dialog
  const std::unique_ptr<QFileDialog> print_dialog(
    QtFileDialog().GetSaveFileDialog(
      QtFileDialog::FileType::pdf));
  print_dialog->setWindowTitle("Exporteer document naar PDF");
  if (print_dialog->exec() != QDialog::Accepted
    || print_dialog->selectedFiles().empty() )
  {
    return;
  }
  assert(!print_dialog->selectedFiles().empty());
  assert(print_dialog->selectedFiles().size() == 1);
  const std::string filename = print_dialog->selectedFiles()[0].toStdString();
  Print(filename);
}


void ribi::braw::QtPrintConceptMapDialog::Print(const std::string& filename)
{
  QPrinter printer;
  printer.setOrientation(QPrinter::Portrait);
  printer.setPaperSize(QPrinter::A4);
  printer.setOutputFormat(QPrinter::PdfFormat); //Student exports to PDF
  printer.setFullPage(false);
  printer.setOutputFileName(filename.c_str());

  //Draw the image to painter to printer (?must be done before printing)
  QPainter painter;

  painter.begin(&printer);
  {
    //Collect widgets to print
    const std::vector<QWidget *> widgets = CollectWidgets();

    int y = 0;
    for (QWidget * const widget: widgets)
    {
      const int h = widget->height();
      if (y+h > painter.window().height())
      {
        printer.newPage();
        y = 0;
      }
      widget->render(&painter,QPoint(0,y));
      y += h;
    }
  }
  painter.end();
}

void ribi::braw::QtPrintConceptMapDialog::resizeEvent(QResizeEvent *)
{
  fitConceptMap();
}

void ribi::braw::QtPrintConceptMapDialog::fitConceptMap()
{
  assert(m_widget);
  if (boost::num_vertices(m_widget->ToConceptMap()) == 0) return;
  const QRectF all_items_rect = m_widget->scene()->itemsBoundingRect();
  m_widget->setMinimumHeight(all_items_rect.height() + 2);
  m_widget->fitInView(all_items_rect);

}

void ribi::braw::QtPrintConceptMapDialog::showEvent(QShowEvent *)
{
  if (boost::num_vertices(m_widget->ToConceptMap()) == 0) return;

  //Concept map
  {
    assert(m_widget);
    assert(boost::num_vertices(m_widget->ToConceptMap()) > 0);

    //m_widget->ReadFromConceptMap(copy_concept_map);
    m_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setMinimumHeight(m_widget->scene()->itemsBoundingRect().height() + 2);
    //Fit concept map to widget
    const QRectF all_items_rect {
      m_widget->scene()->itemsBoundingRect() //Does not work
      //m_widget->scene()->sceneRect() //Does not work
    };
    m_widget->fitInView(all_items_rect); //Does not work
    //m_widget->ensureVisible(all_items_rect,0,0); //Does not work
  }
  //Concept map as text
  {
    assert(ui->frame_concept_map_as_text->layout());
    const auto conceptmap = m_file.GetConceptMap();
    const auto nodes = GetNodes(conceptmap);
    for (const auto node: nodes)
    {
      if (IsCenterNode(node)) continue;
      ribi::cmap::QtConceptMapRatedConceptDialog * const widget
        = new ribi::cmap::QtConceptMapRatedConceptDialog(conceptmap, node);
      assert(widget);
      widget->HideRating();
      ui->frame_concept_map_as_text->layout()->addWidget(widget);
    }
  }
  fitConceptMap();
}
