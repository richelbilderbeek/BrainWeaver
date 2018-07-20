#ifndef QTBRAINWEAVEROVERVIEWDIALOG_H
#define QTBRAINWEAVEROVERVIEWDIALOG_H

#include <QDialog>
#include "brainweaverfwd.h"

namespace ribi {
namespace braw {

struct QtOverviewDialog : public QDialog
{
  explicit QtOverviewDialog(QWidget* parent = nullptr);

protected:
  void keyPressEvent(QKeyEvent *);
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVEROVERVIEWDIALOG_H
