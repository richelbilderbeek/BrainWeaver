#include "qtbrainweaverfiledialog_test.h"
#include "qtbrainweaverfiledialog.h"
#include <QFileDialog>

void ribi::braw::QtFileDialogTest::default_construction()
{
  const QtFileDialog d;
  d.GetOpenFileDialog();
  d.GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d.GetSaveFileDialog(QtFileDialog::FileType::pdf);
}

void ribi::braw::QtFileDialogTest::open_dialog_should_say_kijk_in()
{
  const auto d = QtFileDialog().GetOpenFileDialog();
  QVERIFY(d->labelText(QFileDialog::LookIn) == "Kijk in");
}

void ribi::braw::QtFileDialogTest::open_dialog_should_say_open()
{
  const auto d = QtFileDialog().GetOpenFileDialog();
  QVERIFY(d->labelText(QFileDialog::Accept) == "Open");
}

void ribi::braw::QtFileDialogTest::open_dialog_should_say_bestanden()
{
  const auto d = QtFileDialog().GetOpenFileDialog();
  QVERIFY(d->labelText(QFileDialog::FileName) == "Bestand");
}

void ribi::braw::QtFileDialogTest::open_dialog_should_say_soort_bestanden()
{
  const auto d = QtFileDialog().GetOpenFileDialog();
  QVERIFY(d->labelText(QFileDialog::FileType) == "Soort bestanden");
}

void ribi::braw::QtFileDialogTest::save_dialog_should_say_kijk_in()
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  QVERIFY(d->labelText(QFileDialog::LookIn) == "Kijk in");
}

void ribi::braw::QtFileDialogTest::save_dialog_should_say_sla_op()
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  QVERIFY(d->labelText(QFileDialog::Accept) == "Sla op");
}

void ribi::braw::QtFileDialogTest::save_dialog_should_say_bestanden()
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  QVERIFY(d->labelText(QFileDialog::FileName) == "Bestand");
}

void ribi::braw::QtFileDialogTest::save_dialog_should_say_soort_bestanden()
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  QVERIFY(d->labelText(QFileDialog::FileType) == "Soort bestanden");
}
