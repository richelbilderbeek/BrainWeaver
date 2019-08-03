#include "qtbrainweavermenudialog_test.h"

#include <QDebug>
#include "qtbrainweavermenudialog.h"

void ribi::braw::QtMenuDialogTest::PressAllKeys() const noexcept
{

  //Press digit
  for (int k = static_cast<int>(Qt::Key_0); k <= static_cast<int>(Qt::Key_9); ++k)
  {
    //if (k == Qt::Key_1) continue;
    auto d{std::make_unique<ribi::braw::QtMenuDialog>()};
    d->show();
    QTimer::singleShot(2000, qApp, SLOT(closeAllWindows()));
    QTest::keyClick(d.get(), static_cast<Qt::Key>(k), Qt::AltModifier, 100);
  }
  //Press characters
  for (int k = static_cast<int>(Qt::Key_A); k <= static_cast<int>(Qt::Key_I); ++k)
  {
    auto d{std::make_unique<ribi::braw::QtMenuDialog>()};
    d->show();
    QTimer::singleShot(2000, qApp, SLOT(closeAllWindows()));
    QTest::keyClick(d.get(), static_cast<Qt::Key>(k), Qt::AltModifier, 100);
  }

}

void ribi::braw::QtMenuDialogTest::PressAllKeysFromMemberFunctions() const noexcept
{
  QtMenuDialog d;
  const std::vector<> v = {
    &QtMenuDialog::on_button_about_clicked,
    &QtMenuDialog::on_button_assessor_clicked,
    &QtMenuDialog::on_button_create_assessment_clicked,
    &QtMenuDialog::on_button_edit_concept_clicked,
    &QtMenuDialog::on_button_edit_conceptmap_clicked,
    &QtMenuDialog::on_button_modify_stylesheet_clicked,
    &QtMenuDialog::on_button_overview_clicked,
    &QtMenuDialog::on_button_print_concept_map_clicked,
    &QtMenuDialog::on_button_print_rating_clicked,
    &QtMenuDialog::on_button_rate_concept_auto_clicked,
    &QtMenuDialog::on_button_rate_concept_clicked,
    &QtMenuDialog::on_button_rate_concept_map_clicked,
    &QtMenuDialog::on_button_rate_examples_clicked,
    &QtMenuDialog::on_button_rating_clicked,
    &QtMenuDialog::on_button_student_clicked,
    &QtMenuDialog::on_button_test_cluster_clicked
  };
  for (const auto f: v)
  {
    QTimer::singleShot(1000, qApp, SLOT(closeAllWindows()));
    (d.*f)();
  }
}
