#ifndef QTBRAINWEAVERPRINTRATINGDIALOG_H
#define QTBRAINWEAVERPRINTRATINGDIALOG_H

#include <QDialog>
#include "qtbrainweaverfwd.h"
#include "brainweaverfile.h"

namespace Ui {
  class QtPrintRatingDialog;
}

struct QLabel;
struct QTableWidget;

namespace ribi {
namespace braw {

///View the current rating, optimized for printers
///This dialog will not be visible for humans at all in release
///QtRatingDialog is optimized for humans
class QtPrintRatingDialog : public QDialog
{
  Q_OBJECT //!OCLINT
  
public:
  ///file be const, as the Display Concept map cannot deal with const ribi::cmap::ConceptMap (yet?)
  explicit QtPrintRatingDialog(
    const File& file,
    QWidget *parent = nullptr
  );
  QtPrintRatingDialog(const QtPrintRatingDialog&) = delete;
  QtPrintRatingDialog& operator=(const QtPrintRatingDialog&) = delete;
  ~QtPrintRatingDialog() noexcept;

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
  QLabel * const m_label_concept_map_as_text;
  QLabel * const m_label_diagnostics;
  QLabel * const m_label_tallied_examples;
  QTableWidget * const m_table_diagnostics;
  QTableWidget * const m_table_tallied_examples;
  cmap::QtConceptMap * const m_widget;
  std::vector<QWidget*> m_concept_map_as_texts;
};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERPRINTRATINGDIALOG_H
