#ifndef QTBRAINWEAVERABOUTDIALOG_H
#define QTBRAINWEAVERABOUTDIALOG_H

#include "qtaboutdialog.h"

namespace ribi {
namespace braw {

struct QtAboutDialog : public ::ribi::QtAboutDialog
{
  QtAboutDialog(QWidget * const parent = nullptr);
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERABOUTDIALOG_H
