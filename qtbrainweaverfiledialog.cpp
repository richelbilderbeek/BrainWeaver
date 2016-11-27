#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtbrainweaverfiledialog.h"

#include <cassert>
#include <stdexcept>

#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>

#include "brainweaverfile.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace braw {

std::unique_ptr<QFileDialog>
QtFileDialog::GetOpenFileDialog() const
{
  std::unique_ptr<QFileDialog> d(new QFileDialog);

  d->setViewMode(QFileDialog::Detail);
  d->setFileMode(QFileDialog::ExistingFile);
  d->setAcceptDrops(QFileDialog::AcceptOpen);
  d->setOptions(QFileDialog::ReadOnly);

  const std::string namefile = "Brainweaver concept map (*."
    + GetFilenameExtension() + ")";

  d->setNameFilter(namefile.c_str());

  return d;
}

std::unique_ptr<QFileDialog>
QtFileDialog::GetSaveFileDialog(const FileType type) const
{
  std::unique_ptr<QFileDialog> d(new QFileDialog);
  d->setViewMode(QFileDialog::Detail);
  d->setFileMode(QFileDialog::AnyFile);
  d->setAcceptDrops(QFileDialog::AcceptSave);

  d->setLabelText(QFileDialog::Accept, "Sla op");

  //Workaround for https://bugreports.qt-project.org/browse/QTBUG-29248
  d->setOptions( QFileDialog::DontUseNativeDialog );

  std::string namefile;
  switch (type) //!OCLINT Too few branches in switch statement is false: there are only two enum class values
  {
    case FileType::cmp:
      namefile = "Brainweaver concept map (*."
      + GetFilenameExtension() + ")";
    break;
    case FileType::pdf:
      namefile = "Portable document format (*.pdf)";
    break;
  }

  d->setNameFilter(namefile.c_str());

  return d;
}

} //~namespace braw
} //~namespace ribi
