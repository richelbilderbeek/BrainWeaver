#ifndef QTBRAINWEAVERMENUDIALOG_H
#define QTBRAINWEAVERMENUDIALOG_H

#include <QDialog>
#include "brainweaverfile.h"
#include "brainweaverfwd.h"

namespace Ui { class QtMenuDialog; }

namespace ribi {
namespace braw {

class QtMenuDialogTest;

class QtMenuDialog final : public QDialog //!OCLINT Indeed a lot of methods: one per button
{
  Q_OBJECT //!OCLINT

  public:
  explicit QtMenuDialog(QWidget* parent = nullptr);
  QtMenuDialog(const QtMenuDialog&) = delete;
  QtMenuDialog& operator=(const QtMenuDialog&) = delete;
  virtual ~QtMenuDialog() noexcept;

  const Ui::QtMenuDialog * GetUi() const noexcept { return ui; }
        Ui::QtMenuDialog * GetUi()       noexcept { return ui; }

public slots:
  void on_button_about_clicked() noexcept;
  void on_button_assessor_clicked() noexcept;
  void on_button_modify_stylesheet_clicked() noexcept;
  void on_button_overview_clicked() noexcept;
  void on_button_print_concept_map_clicked() noexcept;
  void on_button_print_rating_clicked() noexcept;
  void on_button_rate_concept_auto_clicked() noexcept;
  void on_button_rate_concept_clicked() noexcept;
  void on_button_rate_concept_map_clicked() noexcept;
  void on_button_rate_examples_clicked() noexcept;
  void on_button_rating_clicked() noexcept;
  void on_button_student_clicked() noexcept;
  void on_button_edit_conceptmap_clicked();
  void on_button_test_cluster_clicked() noexcept;

private slots:
  void keyPressEvent(QKeyEvent* e) noexcept;

  void on_button_edit_concept_clicked();

  void on_button_create_assessment_clicked();

private:
  Ui::QtMenuDialog *ui;

  friend class QtMenuDialogTest;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERMENUDIALOG_H
