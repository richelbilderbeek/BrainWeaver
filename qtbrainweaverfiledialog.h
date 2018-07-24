#ifndef QTBRAINWEAVERFILEDIALOG_H
#define QTBRAINWEAVERFILEDIALOG_H

#include <memory>
#include <QString>

struct QFileDialog;

namespace ribi {
namespace braw {

struct QtFileDialog
{
  QtFileDialog() {}

  enum class FileType { cmp, pdf };
  ///Create a QFileDialog to open Brainweaver files with
  std::unique_ptr<QFileDialog> GetOpenFileDialog() const;

  ///Create a QFileDialog to save Brainweaver files with
  std::unique_ptr<QFileDialog> GetSaveFileDialog(const FileType type) const;

  static QString m_last_file;
};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERFILEDIALOG_H
