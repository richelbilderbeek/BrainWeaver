#include "qtbrainweaverfiledialog.h"

#include <cassert>

#include <QFileDialog>

#include "brainweaverfile.h"

QString ribi::braw::QtFileDialog::m_last_file;

std::unique_ptr<QFileDialog>
ribi::braw::QtFileDialog::GetOpenFileDialog() const
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

  const std::string namefile = "BrainWeaver concept map (*."
    + GetFilenameExtension() + ")";
  d->setDefaultSuffix(GetFilenameExtension().c_str());
  d->setNameFilter(namefile.c_str());

  return d;
}

std::unique_ptr<QFileDialog>
ribi::braw::QtFileDialog::GetSaveFileDialog(const FileType type) const
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
  if (type == FileType::cmp)
  {
    namefile = "BrainWeaver concept map (*."
    + GetFilenameExtension() + ")";
    d->setDefaultSuffix(GetFilenameExtension().c_str());
  }
  else
  {
    assert(type == FileType::pdf);
    namefile = "Portable document format (*.pdf)";
    d->setDefaultSuffix("pdf");
  }
  d->setNameFilter(namefile.c_str());
  return d;
}
