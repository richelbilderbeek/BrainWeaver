//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2016 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtbrainweaverprintratingdialog.h"

#include <cassert>
#include <ctime>

#include <boost/lexical_cast.hpp>

#include <QFileDialog>
#include <QKeyEvent>
#include <QScrollBar>
#include <QPrinter>

#include "brainweaverfile.h"
#include "conceptmapconcept.h"
#include "qtbrainweaverfiledialog.h"
#include "conceptmapnode.h"
#include "conceptmapedge.h"
#include "conceptmapfactory.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmap.h"
#include "qtconceptmapratedconceptdialog.h"
#include "qtbrainweaverdisplay.h"
#include "qtconceptmap.h"
#include "ui_qtbrainweaverprintratingdialog.h"
#pragma GCC diagnostic pop

ribi::braw::QtPrintRatingDialog::QtPrintRatingDialog(
  const File& file,
  QWidget *parent)
  : QtDialog(parent),
    ui(new Ui::QtPrintRatingDialog),
    m_file(file),
    m_widget(new cmap::QtConceptMap)
{
  if (boost::num_vertices(file.GetConceptMap()) == 0)
  {
    std::stringstream msg;
    msg << __func__ << ": must have at least one node";
    throw std::invalid_argument(msg.str());
  }

  ui->setupUi(this);    
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help

  m_widget->SetConceptMap(file.GetConceptMap());
  ui->label_focal_question->setText(
    ("FOCUSVRAAG: "
    + m_file.GetQuestion()).c_str()
  );
  ui->label_student_name->setText(
    ("VAN: "
      + m_file.GetStudentName()).c_str()
  );
  ui->label_assessor_name->setText(
    ("ASSESSOR: "
      + m_file.GetAssessorName()).c_str()
  );

  {
    assert(m_widget);
    assert(ui->frame_concept_map->layout());
    ui->frame_concept_map->layout()->addWidget(m_widget);
  }

  //Allow a QtConceptMapWidget to have no QtExamplesItem
  //This allows to omit showing these in the PDF versions used for printing (#205)
  m_widget->HideExamplesItem();

  {
    std::time_t my_time;
    std::time( &my_time );
    const std::tm * const time_and_date = std::localtime(&my_time);
    const std::string s = std::asctime(time_and_date);
    ui->label_date->setText( ("Datum: " + s).c_str()
    );
  }
}

ribi::braw::QtPrintRatingDialog::~QtPrintRatingDialog() noexcept
{
  delete ui;
}

const std::vector<QWidget *> ribi::braw::QtPrintRatingDialog::CollectWidgets() const
{
  std::vector<QWidget *> v { ui->frame_header, ui->frame_concept_map, ui->label_concept_map_as_text };
  {
    //Add widgets in widget_concept_map_as_text
    const int n = ui->widget_concept_map_as_text->layout()->count();
    for (int i=0; i!=n; ++i)
    {
      v.push_back(ui->widget_concept_map_as_text->layout()->itemAt(i)->widget());
    }
  }
  v.push_back(ui->frame_concepts);
  v.push_back(ui->frame_competencies);
  v.push_back(ui->frame_values);
  v.push_back(ui->frame_misc_values);
  return v;
}

QTableWidget * ribi::braw::QtPrintRatingDialog::GetTableConcepts()
{
  return ui->table_concepts;
}

QTableWidget * ribi::braw::QtPrintRatingDialog::GetTableExamples()
{
  return ui->table_examples;
}

QTableWidget * ribi::braw::QtPrintRatingDialog::GetTableMiscValues()
{
  return ui->table_misc_values;
}

QTableWidget * ribi::braw::QtPrintRatingDialog::GetTableValues()
{
  return ui->table_values;
}

void ribi::braw::QtPrintRatingDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { emit remove_me(this); return; }
}

void ribi::braw::QtPrintRatingDialog::on_button_print_clicked()
{
  Print();
}

void ribi::braw::QtPrintRatingDialog::Print()
{
  //Start save dialog
  const boost::shared_ptr<QFileDialog> print_dialog(
    QtFileDialog::GetSaveFileDialog(
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

  QPrinter printer;
  printer.setOrientation(QPrinter::Portrait);
  printer.setPaperSize(QPrinter::A4);
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
      y+=h;
    }
  }
  painter.end();

}

void ribi::braw::QtPrintRatingDialog::showEvent(QShowEvent *)
{
  //Concept map
  {
    //const ribi::cmap::ConceptMap copy_concept_map
    //  = m_file.GetConceptMap();
    //const ribi::cmap::ConceptMap copy_concept_map
    //  = ribi::cmap::ConceptMapFactory::DeepCopy(m_file.GetConceptMap()); //2013-05-31 REJECT DEEP COPIES
    //m_widget->ReadFromConceptMap(copy_concept_map);
    m_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setMaximumHeight(m_widget->scene()->itemsBoundingRect().height() + 2);
    m_widget->setMinimumHeight(m_widget->scene()->itemsBoundingRect().height() + 2);
    //Fit concept map to widget
    m_widget->fitInView(m_widget->scene()->itemsBoundingRect());
  }
  //Concept map as text
  {
    assert(ui->widget_concept_map_as_text->layout());
    //std::string text;
    const int n_nodes = static_cast<int>(GetNodes(m_file.GetConceptMap()).size());
    for (int node_index = 1; node_index != n_nodes; ++node_index) //1: skip center node
    {
      const auto node = GetNodes(m_file.GetConceptMap()).at(node_index);
      cmap::QtConceptMapRatedConceptDialog * const widget
        = new cmap::QtConceptMapRatedConceptDialog(m_file.GetConceptMap(),node);
      assert(widget);
      ui->widget_concept_map_as_text->layout()->addWidget(widget);
    }
  }

  //Copied from caller
  QtDisplay().DisplayRatedConcepts(m_file,this->GetTableConcepts());
  {
    const int sz = static_cast<int>(GetNodes(m_file.GetConceptMap()).size());
    this->GetTableConcepts()->setMinimumHeight( ((sz-1) * 30) + 26 ); //Standard row is 30 pixels high, header 25 pixels
  }

  QtDisplay().DisplayExamples(m_file,this->GetTableExamples());
  QtDisplay().DisplayValues(m_file,this->GetTableValues());
  QtDisplay().DisplayMiscValues(m_file,this->GetTableMiscValues());
}
