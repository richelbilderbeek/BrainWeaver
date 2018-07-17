

#include "qtbrainweaveroverviewdialog.h"

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QIcon>
#include <QTimer>
#include <QWidget>

#include "brainweaverfilefactory.h"
#include "brainweaverfile.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapfactory.h"
#include "qtbrainweaverassessormenudialog.h"
#include "qtbrainweaverclusterdialog.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweavercreateassessmentdialog.h"

#include "qtbrainweavermenudialog.h"
#include "qtbrainweaveroverviewwidget.h"
#include "qtbrainweaverprintconceptmapdialog.h"
#include "qtbrainweaverprintratingdialog.h"
#include "qtbrainweaverrateconceptmapdialog.h"
#include "qtbrainweaverratingdialog.h"
#include "qtbrainweaverstudentmenudialog.h"
#include "qtbrainweaverstudentstartcompletedialog.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmaprateconceptdialog.h"
#include "qtconceptmaprateconcepttallydialog.h"
#include "qtconceptmaprateexamplesdialog.h"



ribi::braw::QtOverviewWidget::QtOverviewWidget(QWidget* parent)
  : QGraphicsView(new QGraphicsScene,parent),
    m_dialogs(GetAllDialogs())
{
  assert(scene());
  assert(std::count_if(m_dialogs.begin(),m_dialogs.end(),[](QDialog* p) { return !p; } ) == 0);

  double y_sum = 0.0;
  double max_width = 0.0;

  const int sz = m_dialogs.size();
  for (int i = 0; i!=sz; ++i)
  {
    //Convert dialog to widget explicitly for Wine
    assert(m_dialogs[i]);
    QWidget * const widget = m_dialogs[i];
    assert(widget);

    QGraphicsProxyWidget * const proxy = scene()->addWidget(widget,Qt::Dialog);
    assert(proxy);

    proxy->setPos(32,y_sum);

    y_sum += proxy->rect().height();
    y_sum += 64; //Added by window height
    max_width = std::max(max_width,proxy->rect().width());

    const std::string window_title
      = m_dialogs[i]->windowTitle().toStdString()
      + " ("
      + m_dialogs[i]->objectName().toStdString()
      + ")";
    proxy->setWindowTitle(window_title.c_str());
  }
  this->setGeometry(0,0,max_width,y_sum);
}


std::vector<QDialog* > ribi::braw::GetAllDialogs()
{
  std::vector<QDialog* > v;
  v.push_back(new QtAssessorMenuDialog);
  v.push_back(new QtClusterDialog(FileFactory().Get3()));
  v.push_back(
    new ribi::cmap::QtConceptMapConceptEditDialog(
      ribi::cmap::ConceptFactory().GetTest(2)
    )
  );
  v.push_back(new QtConceptMapDialog(FileFactory().Get2()));
  v.push_back(new QtCreateAssessmentDialog);
  v.push_back(new QtMenuDialog);
  v.push_back(new QtPrintConceptMapDialog(FileFactory().Get5()));
  v.push_back(
    new cmap::QtRateConceptDialog(ribi::cmap::ConceptMapFactory().Get6())
  );
  v.push_back(
    new cmap::QtRateConceptTallyDialog(
      ribi::cmap::ConceptMapFactory().Get6(),
      ribi::cmap::CreateDefaultRating()
    )
  );
  v.push_back(new QtRateConceptMapDialog(FileFactory().GetTests().at(2)));
  v.push_back(
    new ribi::cmap::QtRateExamplesDialog(
      ribi::cmap::ConceptFactory().GetTests().at(2)
    )
  );
  v.push_back(new QtRatingDialog(FileFactory().GetTests().at(4)));
  v.push_back(new QtStudentMenuDialog(FileFactory().GetTests().at(2)));
  v.push_back(new QtStudentStartCompleteDialog(FileFactory().GetTests().at(2)));
  assert(std::count_if(v.begin(),v.end(),[](QDialog* p) { return !p; } ) == 0);
  return v;
}

void ribi::braw::QtOverviewWidget::mouseDoubleClickEvent(QMouseEvent *)
{
  // Create the image with the exact size of the shrunk scene
  QImage image(scene()->sceneRect().size().toSize(), QImage::Format_ARGB32);
  // Start all pixels transparent
  image.fill(Qt::transparent);
  QPainter painter(&image);
  scene()->render(&painter);
  image.save("file_name.png");
}
