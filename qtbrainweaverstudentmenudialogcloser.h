#ifndef QTBRAINWEAVERSTUDENTMENUDIALOGDIALOGCLOSER_H
#define QTBRAINWEAVERSTUDENTMENUDIALOGDIALOGCLOSER_H

#include <QDialog>

namespace ribi {
namespace braw {

class QtStudentMenuDialogCloser : public QObject
{
  Q_OBJECT

  public:
  QtStudentMenuDialogCloser();
  virtual ~QtStudentMenuDialogCloser();
  public slots:

  ///Close
  void Close() const;

  ///Enter a name
  void EnterName() const;

  ///Press Start
  void PressStart() const;

};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERSTUDENTMENUDIALOGDIALOGCLOSER_H
