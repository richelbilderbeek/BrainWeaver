//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2016 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
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

std::unique_ptr<QFileDialog> QtFileDialog::GetOpenFileDialog()
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

std::unique_ptr<QFileDialog> QtFileDialog::GetSaveFileDialog(const FileType type)
{
  std::unique_ptr<QFileDialog> d(new QFileDialog);

  d->setViewMode(QFileDialog::Detail);
  d->setFileMode(QFileDialog::AnyFile);
  d->setAcceptDrops(QFileDialog::AcceptSave);

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
