#include "qtbrainweaverprintratingdialog.h"

#include <cassert>
#include <ctime>

#include <boost/lexical_cast.hpp>

#include <QFileDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QScrollBar>
#include <QPrinter>
#include <QTableWidget>

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

ribi::braw::QtPrintRatingDialog::QtPrintRatingDialog(
  const File& file,
  QWidget *parent)
  : QtDialog(parent),
    ui(new Ui::QtPrintRatingDialog),
    m_file(file),
    m_label_concept_map_as_text{new QLabel("Conceptmap als tekst", this)},
    m_label_diagnostics{new QLabel("Gevonden waarden", this)},
    m_label_rated_concepts{new QLabel("Overzicht concepten", this)},
    m_label_tallied_examples{
      new QLabel(
        "Verdeling van de voorbeelden/toelichting over de zes objecten van kennis",
        this
      )
    },
    m_table_diagnostics{
      QtDisplay().CreateDiagnosticsWidget(file, this)
    },
    m_table_rated_concepts{QtDisplay().CreateRatedConceptsWidget(file, this)},
    m_table_tallied_examples{
      QtDisplay().CreateTalliedExamplesWidget(file, this)
    },
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
  std::vector<QWidget *> v = {
    ui->frame_header,
    ui->frame_concept_map,
    m_label_rated_concepts,
    m_table_rated_concepts,
    m_label_tallied_examples,
    m_table_tallied_examples,
    m_label_diagnostics,
    m_table_diagnostics,
    m_label_concept_map_as_text
  };
  {
    std::copy(
      begin(m_concept_map_as_texts),
      end(m_concept_map_as_texts),
      std::back_inserter(v)
    );
    //Add widgets in widget_concept_map_as_text
    /*
    const int n = ui->widget_concept_map_as_text->layout()->count();
    for (int i=0; i!=n; ++i)
    {
      v.push_back(ui->widget_concept_map_as_text->layout()->itemAt(i)->widget());
    }
    */
  }
  return v;
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
  const std::unique_ptr<QFileDialog> print_dialog(
    QtFileDialog().GetSaveFileDialog(
      QtFileDialog::FileType::pdf)
  );
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

void ribi::braw::QtPrintRatingDialog::Print(const std::string& filename)
{
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
  const auto& file = m_file; //Just an alias
  //Concept map
  {
    m_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_widget->setMaximumHeight(m_widget->scene()->itemsBoundingRect().height() + 2);
    m_widget->setMinimumHeight(m_widget->scene()->itemsBoundingRect().height() + 2);
    //Fit concept map to widget
    m_widget->fitInView(m_widget->scene()->itemsBoundingRect());
  }
  //Add rated concepts
  {
    assert(ui->scrollAreaWidgetContents->layout());
    ui->scrollAreaWidgetContents->layout()->addWidget(
      m_label_rated_concepts
    );
    ui->scrollAreaWidgetContents->layout()->addWidget(
      m_table_rated_concepts

    );
  }

  //Add tallied examples
  {
    assert(ui->scrollAreaWidgetContents->layout());
    ui->scrollAreaWidgetContents->layout()->addWidget(
      m_label_tallied_examples
    );
    ui->scrollAreaWidgetContents->layout()->addWidget(
      m_table_tallied_examples
    );
  }

  //Add diagnostics
  {
    assert(ui->scrollAreaWidgetContents->layout());
    ui->scrollAreaWidgetContents->layout()->addWidget(
      m_label_diagnostics
    );
    ui->scrollAreaWidgetContents->layout()->addWidget(
      m_table_diagnostics
    );
  }
  //Concept map as text
  {
    ui->scrollAreaWidgetContents->layout()->addWidget(
      m_label_concept_map_as_text
    );

    const int n_nodes = CountNodes(m_file);
    for (int node_index = 1; node_index != n_nodes; ++node_index) //1: skip center node
    {
      const auto node = GetNodes(m_file.GetConceptMap()).at(node_index);
      auto * const widget
        = new cmap::QtConceptMapRatedConceptDialog(
          m_file.GetConceptMap(),
          node,
          ribi::cmap::Role::assessor
        );
      assert(widget);
      m_concept_map_as_texts.push_back(widget);
      ui->scrollAreaWidgetContents->layout()->addWidget(widget);
    }
  }

}
