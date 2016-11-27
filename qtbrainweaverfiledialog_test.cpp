#include "qtbrainweaverfiledialog_test.h"
#include "qtbrainweaverfiledialog.h"
#include <QFileDialog>

void ribi::braw::qtbrainweaverfiledialog_test::default_construction()
{
  const QtFileDialog d;
  d.GetOpenFileDialog();
  d.GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d.GetSaveFileDialog(QtFileDialog::FileType::pdf);
}

void ribi::braw::qtbrainweaverfiledialog_test::save_dialog_should_say_sla_op()
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  QVERIFY(d->labelText(QFileDialog::Accept) == "Sla op");
}
