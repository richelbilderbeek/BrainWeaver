#include "qtbrainweaverprintconceptmapdialog_test.h"

#include <cassert>
#include <iostream>
#include "qtbrainweaverprintconceptmapdialog.h"
#include "brainweaverfilefactory.h"
#include "qtconceptmap.h"

void ribi::braw::qtbrainweaverprintconceptmapdialog_test::default_construct()
{
  std::cout << __func__ << ": TODO" << '\n';
  return;
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


