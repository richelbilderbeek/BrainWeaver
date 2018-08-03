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

  //All deleted by QtOverviewWidget
  const std::vector<QDialog* > m_dialogs;

};

///Create all dialogs
std::vector<QDialog* > GetAllDialogs(QWidget* parent);

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVEROVERVIEWWIDGET_H
