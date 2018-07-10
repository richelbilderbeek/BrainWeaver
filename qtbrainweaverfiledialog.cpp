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
  d->setLabelText(QFileDialog::LookIn, "Kijk in");
  d->setLabelText(QFileDialog::Accept, "Open");
  d->setLabelText(QFileDialog::FileName, "Bestand");
  d->setLabelText(QFileDialog::FileType, "Soort bestanden");

  const std::string namefile = "Brainweaver concept map (*."
    + GetFilenameExtension() + ")";
  d->setDefaultSuffix(GetFilenameExtension());
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

  d->setLabelText(QFileDialog::LookIn, "Kijk in");
  d->setLabelText(QFileDialog::Accept, "Sla op");
  d->setLabelText(QFileDialog::FileName, "Bestand");
  d->setLabelText(QFileDialog::FileType, "Soort bestanden");


  //Workaround for https://bugreports.qt-project.org/browse/QTBUG-29248
  d->setOptions( QFileDialog::DontUseNativeDialog );

  std::string namefile;
  switch (type) //!OCLINT Too few branches in switch statement is false: there are only two enum class values
  {
    case FileType::cmp:
      namefile = "Brainweaver concept map (*."
      + GetFilenameExtension() + ")";
      d->setDefaultSuffix(GetFilenameExtension());
    break;
    case FileType::pdf:
      namefile = "Portable document format (*.pdf)";
      d->setDefaultSuffix("pdf");
    break;
  }
  d->setNameFilter(namefile.c_str());

  return d;
}

} //~namespace braw
} //~namespace ribi
