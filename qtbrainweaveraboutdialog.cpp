



#include "qtbrainweaveraboutdialog.h"

#include <cassert>

#include <QLabel>
#include <QLayout>
#include <QPixmap>

#include "about.h"
#include "brainweavermenudialog.h"
#include "qtarrowitem.h"
#include "qtkeyboardfriendlygraphicsview.h"
#include "qtquadbezierarrowitem.h"
#include "qtscopeddisable.h"


ribi::About GetAbout()
{
  ribi::About about = ribi::braw::MenuDialog().GetAbout();
  about.AddLibrary("QtArrowItem version: "
    + ribi::QtArrowItem::GetVersion()
  );
  about.AddLibrary("QtKeyboardFriendlyGraphicsView version: "
    + ribi::GetQtKeyboardFriendlyGraphicsViewVersion()
  );
  about.AddLibrary("QtQuadBezierArrowItem version: "
    + ribi::QtQuadBezierArrowItem::GetVersion()
  );
  about.AddLibrary("QtScopedDisable version: "
    + QtScopedDisable<int>::GetVersion()
  );
  about.AddLibrary("Artwork from LibreOffice");
  return about;
}

ribi::braw::QtAboutDialog::QtAboutDialog()
  : ::ribi::QtAboutDialog(GetAbout())
{
  //Add Loom image
  assert(layout());
  QLabel * const label = new QLabel(this);
  label->setPixmap(QPixmap(":/images/PicLoomAbout.png"));
  layout()->addWidget(label);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help
}
