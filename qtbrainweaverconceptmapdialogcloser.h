#ifndef QTBRAINWEAVERCONCEPTMAPDIALOGDIALOGCLOSER_H
#define QTBRAINWEAVERCONCEPTMAPDIALOGDIALOGCLOSER_H

#include <QDialog>

namespace ribi {
namespace braw {

///Object to close a popped-up QtConceptMapDialog
class QtConceptMapDialogCloser : public QObject
{
  Q_OBJECT

  public:
  QtConceptMapDialogCloser();
  virtual ~QtConceptMapDialogCloser();
  public slots:
  void Close();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCONCEPTMAPDIALOGDIALOGCLOSER_H
