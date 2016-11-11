#include "qtbrainweaverprintconceptmapdialog_test.h"

#include <cassert>
#include <iostream>
#include "qtbrainweaverprintconceptmapdialog.h"
#include "brainweaverfilefactory.h"
#include "qtconceptmap.h"
#include "qtconceptmaphelper.h"
#include "fileio.h"

void ribi::braw::qtbrainweaverprintconceptmapdialog_test::default_construct()
{
  const auto files = FileFactory().GetTests();
  for (const auto file: files) {
    QtPrintConceptMapDialog d(file);
    d.show();
    QTest::qWait(1000);
    for (const ribi::cmap::QtNode * const qtnode:
      ribi::cmap::GetQtNodes(d.m_widget->GetScene())
    )
    {
      QVERIFY(qtnode != nullptr);
      QVERIFY(qtnode->isVisible());
      #ifdef REALLY_CARE_20161008
      //All QtNodes' their rectangles should be within all_items_rect
      const QRectF all_items_rect {
        //d.m_widget->scene()->itemsBoundingRect() //Does not work
        //d.m_widget->scene()->sceneRect() //Does not work
        d.m_widget->sceneRect()
      };
      QVERIFY(all_items_rect.contains(qtnode->boundingRect()));
      #endif
    }
  }
}

void ribi::braw::qtbrainweaverprintconceptmapdialog_test::print_should_produce_file()
{
  const auto file = FileFactory().Get3();
  QtPrintConceptMapDialog d(file);
  d.show();
  const std::string filename{
    "qtbrainweaverprintconceptmapdialog_test.pdf"
  };
  if (ribi::is_regular_file(filename)) { ribi::delete_file(filename); }
  QVERIFY(!ribi::is_regular_file(filename));
  d.Print(filename);
  QVERIFY(ribi::is_regular_file(filename));

  //Cleanup
  if (ribi::is_regular_file(filename)) { ribi::delete_file(filename); }
  assert(!ribi::is_regular_file(filename));
}



