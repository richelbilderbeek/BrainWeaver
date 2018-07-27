#ifndef QTBRAINWEAVERSTUDENTMENUDIALOG_H
#define QTBRAINWEAVERSTUDENTMENUDIALOG_H

#include <QDialog>
#include "brainweaverfile.h"
#include "brainweaverfwd.h"

namespace Ui { class QtStudentMenuDialog; }

namespace ribi {
namespace braw {

class QtStudentMenuDialog final : public QDialog
{
  Q_OBJECT //!OCLINT
    
  public:
  explicit QtStudentMenuDialog(
    const File file,
    QWidget* parent = nullptr
  );
  QtStudentMenuDialog(const QtStudentMenuDialog&) = delete;
  QtStudentMenuDialog& operator=(const QtStudentMenuDialog&) = delete;
  ~QtStudentMenuDialog() noexcept;

  ///Get the student his/her name
  QString GetName() const noexcept;

  ///Save to file
  void Save(const QString& filename);

  ///Set the student his/her name
  void SetName(const QString& name);

  public slots:
  void keyPressEvent(QKeyEvent* e);
  void on_button_about_clicked();
  void on_button_save_clicked();
  void on_button_start_clicked();
  void on_edit_name_textChanged(const QString &arg1);

private:
  Ui::QtStudentMenuDialog *ui;
  File m_file;

};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERSTUDENTMENUDIALOG_H
