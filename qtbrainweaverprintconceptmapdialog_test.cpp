#include "qtbrainweaverprintconceptmapdialog_test.h"

#include <cassert>
#include <iostream>
#include "qtbrainweaverprintconceptmapdialog.h"
#include "brainweaverfilefactory.h"
#include "qtconceptmap.h"
#include "qtconceptmaphelper.h"

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


