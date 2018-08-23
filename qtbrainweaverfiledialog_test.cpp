#include "qtbrainweaverfiledialog_test.h"
#include "qtbrainweaverfiledialog.h"
#include <QFileDialog>

void ribi::braw::QtFileDialogTest::DefaultConstruction() const noexcept
{
  const QtFileDialog d;
  d.GetOpenFileDialog();
  d.GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d.GetSaveFileDialog(QtFileDialog::FileType::pdf);
}

void ribi::braw::QtFileDialogTest::OpenDialogSaysKijkIn() const noexcept
{
  const auto d = QtFileDialog().GetOpenFileDialog();
  QVERIFY(d->labelText(QFileDialog::LookIn) == "Kijk in");
}

void ribi::braw::QtFileDialogTest::OpenDialogSaysOpen() const noexcept
{
  const auto d = QtFileDialog().GetOpenFileDialog();
  QVERIFY(d->labelText(QFileDialog::Accept) == "Open");
}

void ribi::braw::QtFileDialogTest::OpenDialogSaysBestanden() const noexcept
{
  const auto d = QtFileDialog().GetOpenFileDialog();
  QVERIFY(d->labelText(QFileDialog::FileName) == "Bestand");
}

void ribi::braw::QtFileDialogTest::OpenDialogShouldSaySoortBestanden() const noexcept
{
  const auto d = QtFileDialog().GetOpenFileDialog();
  QVERIFY(d->labelText(QFileDialog::FileType) == "Soort bestanden");
}

void ribi::braw::QtFileDialogTest::SaveDialogShouldSayKijkIn() const noexcept
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  QVERIFY(d->labelText(QFileDialog::LookIn) == "Kijk in");
}

void ribi::braw::QtFileDialogTest::SaveDialogShouldSaySlaOp() const noexcept
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  QVERIFY(d->labelText(QFileDialog::Accept) == "Sla op");
}

void ribi::braw::QtFileDialogTest::SaveDialogShouldSayBestanden() const noexcept
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  QVERIFY(d->labelText(QFileDialog::FileName) == "Bestand");
}

void ribi::braw::QtFileDialogTest::SaveDialogShouldSaySoortBestanden() const noexcept
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  QVERIFY(d->labelText(QFileDialog::FileType) == "Soort bestanden");
}
