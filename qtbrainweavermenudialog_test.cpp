#include "qtbrainweavermenudialog_test.h"

#include <boost/lexical_cast.hpp>

#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLayout>
#include <QVBoxLayout>

#include "qtbrainweavermenudialog.h"
#include "add_custom_vertex.h"
#include "brainweaverfilefactory.h"
#include "brainweaverfile.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapconcept.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapexamples.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapnode.h"
#include "container.h"
#include "counter.h"
#include "fileio.h"
#include "plane.h"
#include "qtbrainweaveraboutdialog.h"
#include "qtbrainweaverassessormenudialog.h"
#include "qtbrainweaverclusterdialog.h"
#include "qtbrainweaverclusterwidget.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweavercreateassessmentcompletedialog.h"
#include "qtbrainweaverfiledialog.h"
#include "qtbrainweaveroverviewdialog.h"
#include "qtbrainweaverprintconceptmapdialog.h"
#include "qtbrainweaverprintratingdialog.h"
#include "qtbrainweaverrateconceptmapdialog.h"
#include "qtbrainweaverratingdialog.h"
#include "qtbrainweaverstudentmenudialog.h"
#include "qtbrainweaverviewfilesdialog.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmaprateconceptdialognewname.h"
#include "qtconceptmaprateconcepttallydialognewname.h"
#include "qtconceptmaprateexamplesdialognewname.h"
//#include "qtconceptmapviewtestsdialog.h"
#include "qtstylesheetsettermaindialog.h"
#include "qttestconceptmapmenudialog.h"
#include "qttesteditconceptmapdialog.h"
#include "qttestqtarrowitemsmenudialog.h"
#include "qttestqtroundededitrectitemmenudialog.h"
#include "qttestqtroundedrectitemmenudialog.h"
#include "ribi_regex.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtbrainweavermenudialog.h"

void ribi::pvdb::qtbrainweavermenudialog_test::press_all_buttons()
{
  QtMenuDialog d;
  d.show();
  Ui::QtMenuDialog * const ui = d.GetUi();
  const std::vector<QPushButton*> buttons
    =
    {
      //Duplication of tests, the ones I am most interested in now

      //Normal alphabetical order of tests
      ui->button_about,
      ui->button_assessor,
      ui->button_create_test_files,
      ui->button_modify_stylesheet,
      ui->button_overview,
      ui->button_print_concept_map,
      ui->button_print_rating,
      ui->button_rate_concept,
      ui->button_rate_concept_auto,
      ui->button_rate_concept_map,
      ui->button_rate_examples,
      ui->button_rating,
      ui->button_student,
      ui->button_test_arrowitems,
      ui->button_test_cluster,
      ui->button_test_conceptmap,
      ui->button_test_create_sub_concept_map,
      ui->button_test_conceptmaps,
      ui->button_test_qtroundededitrectitem,
      ui->button_view_files
    };
  const std::size_t n_buttons = buttons.size();
  for (std::size_t i = 0; i!=n_buttons; ++i)
  {
    QVERIFY(i < buttons.size());
    QPushButton * const button = buttons[i];
    QVERIFY(button);
    if (button->isEnabled()) button->click();
  }
}
