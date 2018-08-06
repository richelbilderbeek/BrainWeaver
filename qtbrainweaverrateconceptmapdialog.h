#ifndef QTBRAINWEAVERRATECONCEPTMAPDIALOG_H
#define QTBRAINWEAVERRATECONCEPTMAPDIALOG_H

#include <QDialog>
#include "qtbrainweaverfwd.h"
#include "brainweaverfile.h"

namespace Ui { class QtRateConceptMapDialog; }

namespace ribi {
namespace braw {

struct qtbrainweaverrateconceptmapdialog_test;

class QtRateConceptMapDialog final : public QDialog
{
  Q_OBJECT //!OCLINT
  
public:
  explicit QtRateConceptMapDialog(
    const File& file,
    QWidget* parent = nullptr
  );
  QtRateConceptMapDialog(const QtRateConceptMapDialog&) = delete;
  QtRateConceptMapDialog& operator=(const QtRateConceptMapDialog&) = delete;
  ~QtRateConceptMapDialog() noexcept;

  const File& GetFile() const noexcept;
  ::ribi::cmap::QtConceptMap * GetWidget();

  ///Respond to key press
  void keyPressEvent(QKeyEvent *) override;

  void Save();
  void Save(const std::string& filename);

private slots:
  void changeEvent(QEvent *) override;
  void on_button_next_clicked();
  void on_button_save_clicked();
  void showEvent(QShowEvent *) override;

private:
  Ui::QtRateConceptMapDialog *ui;
  File m_file;
  ::ribi::cmap::QtConceptMap * const m_qtconcept_map;

  friend class qtbrainweaverrateconceptmapdialog_test;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERRATECONCEPTMAPDIALOG_H
