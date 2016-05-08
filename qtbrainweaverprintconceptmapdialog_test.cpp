#include "qtbrainweaverprintconceptmapdialog_test.h"

#include <cassert>
#include "qtbrainweaverprintconceptmapdialog.h"
#include "brainweaverfilefactory.h"
#include "qtconceptmap.h"

void ribi::pvdb::qtbrainweaverprintconceptmapdialog_test::default_construct()
{
  const auto files = FileFactory().GetTests();
  for (const auto file: files) {
    QtPrintConceptMapDialog d(file);
    d.show();
    QTest::qWait(1000);
    const QRectF all_items_rect {
      d.m_widget->scene()->itemsBoundingRect() //Does not work
      //m_widget->scene()->sceneRect() //Does not work
    };
    for (const ribi::cmap::QtNode * const qtnode:
      ribi::cmap::GetQtNodes(d.m_widget->GetScene())
    )
    {
      //All QtNodes' their rectangles should be within all_items_rect
      QVERIFY(qtnode != nullptr);
      QVERIFY(all_items_rect.contains(qtnode->boundingRect()));
    }
  }
}


