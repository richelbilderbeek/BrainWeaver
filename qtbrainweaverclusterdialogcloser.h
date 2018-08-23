#ifndef QTBRAINWEAVERCLUSTERDIALOGDIALOGCLOSER_H
#define QTBRAINWEAVERCLUSTERDIALOGDIALOGCLOSER_H

#include <QDialog>

namespace ribi {
namespace braw {

///Object to close a popped-up QtClusterDialog
class QtClusterDialogCloser : public QObject
{
  Q_OBJECT

  public:
  QtClusterDialogCloser();
  virtual ~QtClusterDialogCloser();
  public slots:

  ///Modify the concept map randomly
  void Modify();

  ///Press cancel
  void PressCancel();

  ///Press OK
  void PressOk();

};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCLUSTERDIALOGDIALOGCLOSER_H
