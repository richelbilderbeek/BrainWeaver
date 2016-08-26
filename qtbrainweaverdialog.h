#ifndef QTBRAINWEAVERDIALOG_H
#define QTBRAINWEAVERDIALOG_H

#include <QDialog>

namespace ribi {
namespace braw {

///Base class for all dialogs displayed within the Master Dialog
class QtDialog : public QDialog
{
  Q_OBJECT //!OCLINT
public:
  explicit QtDialog(QWidget *parent = 0);

protected:

  void closeEvent(QCloseEvent *);

signals:

  ///The Dialog creates another QDialog
  ///Ownership of dialog will be of MasterDialog
  void add_me(QDialog * const dialog) const;

  ///This Dialog signals to be removed, by emitting 'this'
  void remove_me(QDialog * const dialog) const;

public slots:

};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERDIALOG_H
