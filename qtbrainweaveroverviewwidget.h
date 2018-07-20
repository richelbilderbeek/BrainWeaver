#ifndef QTBRAINWEAVEROVERVIEWWIDGET_H
#define QTBRAINWEAVEROVERVIEWWIDGET_H


#include <QGraphicsView>
#include "brainweaverfwd.h"


namespace ribi {
namespace braw {

struct QtDialog;

class QtOverviewWidget : public QGraphicsView
{
  Q_OBJECT //!OCLINT

public:

  explicit QtOverviewWidget(QWidget* parent = nullptr);
    
public slots:

  void mouseDoubleClickEvent(QMouseEvent *event);

private:

  ///NASTY BUG ALERT: It crashes Wine if m_dialogs is created as
  ///const std::vector<boost::shared_ptr<QDialog> > m_dialogs;
  ///No idea why...
  const std::vector<QDialog* > m_dialogs;

};

///Create all dialogs
std::vector<QDialog* > GetAllDialogs();

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVEROVERVIEWWIDGET_H
