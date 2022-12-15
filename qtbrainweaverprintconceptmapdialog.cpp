#include "qtbrainweaverprintconceptmapdialog.h"

#include <cassert>
#include <ctime>
#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

#include <QKeyEvent>

#include <QDebug>
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


ribi::braw::QtPrintConceptMapDialog::QtPrintConceptMapDialog(
  const File& file,
  QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtPrintConceptMapDialog),
    m_file(file),
    m_widget(new cmap::QtConceptMap)
{
  ui->setupUi(this);

  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help

  setMinimumWidth(780);
  setMaximumWidth(780);


  m_widget->SetConceptMap(file.GetConceptMap());

  {
    assert(m_widget);
    assert(ui->frame_concept_map->layout());
    ui->frame_concept_map->layout()->addWidget(m_widget);

    ui->frame_concept_map->setMinimumWidth(750);
    ui->frame_concept_map->setMaximumWidth(750);
    ui->frame_concept_map->setMinimumHeight(
      1.44 * ui->frame_concept_map->width()
    );
  }


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
  //Concept map
  {
    assert(m_widget);
    if (boost::num_vertices(m_widget->ToConceptMap()) == 0)
    {
      #ifndef NDEBUG
      qDebug() << "Warning: Zero nodes in QtConceptMap, should not have that as a user";
      #endif // NDEBUG
    }
    m_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  }
  //Concept map as text
  {
    assert(ui->frame_concept_map_as_text->layout());
    const auto conceptmap = m_file.GetConceptMap();
    const auto nodes = GetNodesSortedByLevel(conceptmap);
    for (const auto& node: nodes)
    {
      if (IsCenterNode(node)) continue;
      ribi::cmap::QtConceptMapRatedConceptDialog * const widget
        = new ribi::cmap::QtConceptMapRatedConceptDialog(
          conceptmap,
          node,
          ribi::cmap::Role::student
        );
      assert(widget);
      ui->frame_concept_map_as_text->layout()->addWidget(widget);
    }
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
  if (event->key() == Qt::Key_Escape)
  {
    close();
    return;
  }
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

void ribi::braw::QtPrintConceptMapDialog::showEvent(QShowEvent *)
{
  assert(m_widget);
  if (boost::num_vertices(m_widget->ToConceptMap()) == 0) return;

  m_widget->rotate(90);
  const QRectF all_items_rect = m_widget->scene()->itemsBoundingRect();
  m_widget->fitInView(all_items_rect, Qt::KeepAspectRatio);
}
