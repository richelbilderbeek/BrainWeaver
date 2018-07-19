#ifndef QTBRAINWEAVERRATINGDIALOG_H
#define QTBRAINWEAVERRATINGDIALOG_H

#include <QDialog>
#include <iosfwd>
#include "brainweaverfile.h"
#include "brainweaverfwd.h"

namespace Ui { class QtRatingDialog; }

struct QTableWidget;

namespace ribi {
namespace braw {

class qtbrainweaverratingdialog_test;

///View the current rating, optimized for humans
///QtPrintRatingDialog is optimized for printers
class QtRatingDialog : public QDialog
{
  Q_OBJECT //!OCLINT

  public:
  explicit QtRatingDialog(
    const File file,
    QWidget* parent = nullptr
  );
  QtRatingDialog(const QtRatingDialog&) = delete;
  QtRatingDialog& operator=(const QtRatingDialog&) = delete;
  ~QtRatingDialog() noexcept;

  bool GetBackToMenu() const noexcept;
  void Save(const std::string& filename) const;

  private slots:
  void on_button_save_clicked();
  void keyPressEvent(QKeyEvent* e);
  void on_button_print_clicked();
  void on_edit_name_textEdited(const QString &arg1);
  void showEvent(QShowEvent *);

private:
  Ui::QtRatingDialog *ui;
  bool m_back_to_menu;
  File m_file;

  friend class qtbrainweaverratingdialog_test;
};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERRATINGDIALOG_H
