#ifndef QTBRAINWEAVERFILEDIALOGDIALOGCLOSER_H
#define QTBRAINWEAVERFILEDIALOGDIALOGCLOSER_H

#include <QDialog>

class QFileDialog;

namespace ribi {
namespace braw {


///Object to close a popped-up QtFileDialog
class QtFileDialogCloser : public QObject
{
  Q_OBJECT

  public:
  QtFileDialogCloser(const QString& filename);
  virtual ~QtFileDialogCloser();
  public slots:
  void PressCancel() const;
  void PressOk() const;

  private:
  ///Returns non-nullptr
  ///Will freeze if dialog is absent
  QFileDialog * GetDialog() const noexcept;

  ///File to save to
  const QString m_filename;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERFILEDIALOGDIALOGCLOSER_H
