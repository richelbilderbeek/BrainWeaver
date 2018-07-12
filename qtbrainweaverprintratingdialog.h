#ifndef QTBRAINWEAVERPRINTRATINGDIALOG_H
#define QTBRAINWEAVERPRINTRATINGDIALOG_H

#include "qtbrainweaverdialog.h"
#include "qtbrainweaverfwd.h"
#include "brainweaverfile.h"

namespace Ui {
  class QtPrintRatingDialog;
}

struct QTableWidget;

namespace ribi {
namespace braw {

///View the current rating, optimized for printers
///This dialog will not be visible for humans at all in release
///QtRatingDialog is optimized for humans
class QtPrintRatingDialog : public QtDialog
{
  Q_OBJECT //!OCLINT
  
public:
  ///file be const, as the Display Concept map cannot deal with const ribi::cmap::ConceptMap (yet?)
  explicit QtPrintRatingDialog(
    const File& file,
    QWidget *parent = 0);
  QtPrintRatingDialog(const QtPrintRatingDialog&) = delete;
  QtPrintRatingDialog& operator=(const QtPrintRatingDialog&) = delete;
  ~QtPrintRatingDialog() noexcept;

  QTableWidget * GetTableConcepts();
  void Print();
  void Print(const std::string& filename);

protected:
  void keyPressEvent(QKeyEvent * event);
  void showEvent(QShowEvent *);

private slots:
  void on_button_print_clicked();
  const std::vector<QWidget *> CollectWidgets() const;
private:
  Ui::QtPrintRatingDialog *ui;

  const File m_file;

  cmap::QtConceptMap * const m_widget;
};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERPRINTRATINGDIALOG_H
