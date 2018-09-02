#ifndef QTBRAINWEAVERCLUSTERDIALOGDIALOGCLOSER_H
#define QTBRAINWEAVERCLUSTERDIALOGDIALOGCLOSER_H

#include <QDialog>

namespace ribi {
namespace braw {

class QtClusterDialog;

///Object to close a popped-up QtClusterDialog
class QtClusterDialogCloser : public QObject
{
  Q_OBJECT

  public:
  QtClusterDialogCloser();
  virtual ~QtClusterDialogCloser();
  public slots:

  void Modify() const;
  void PressCancel() const;
  void PressOk() const;

  private:
  ///Returns non-nullptr
  ///Will freeze if dialog is absent
  QtClusterDialog * GetDialog() const noexcept;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCLUSTERDIALOGDIALOGCLOSER_H
