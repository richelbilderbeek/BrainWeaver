#ifndef QTBRAINWEAVEROVERVIEWDIALOG_H
#define QTBRAINWEAVEROVERVIEWDIALOG_H

#include "qtbrainweaverdialog.h"
#include "brainweaverfwd.h"

namespace ribi {
namespace braw {

struct QtOverviewDialog : public QDialog
{
  explicit QtOverviewDialog(QWidget* parent = 0);

protected:
  void keyPressEvent(QKeyEvent *);
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVEROVERVIEWDIALOG_H
