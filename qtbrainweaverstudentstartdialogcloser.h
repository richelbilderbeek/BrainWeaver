#ifndef QTBRAINWEAVERSTUDENTSTARTDIALOGDIALOGCLOSER_H
#define QTBRAINWEAVERSTUDENTSTARTDIALOGDIALOGCLOSER_H

#include <QDialog>

namespace ribi {
namespace braw {

class QtStudentStartDialogCloser : public QObject
{
  Q_OBJECT

  public:
  QtStudentStartDialogCloser();
  virtual ~QtStudentStartDialogCloser();
  public slots:

  ///Close
  void Close() const;

  ///Press cancel
  void PressStartCluster() const;

  ///Press OK
  void PressStartConceptMap() const;

};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERSTUDENTSTARTDIALOGDIALOGCLOSER_H
