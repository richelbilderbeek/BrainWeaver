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
