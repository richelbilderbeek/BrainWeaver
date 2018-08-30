#ifndef QTBRAINWEAVERSTUDENTSTARTDIALOG_H
#define QTBRAINWEAVERSTUDENTSTARTDIALOG_H

#include <QDialog>
#include "brainweaverfile.h"
#include "brainweaverfwd.h"

namespace Ui { class QtStudentStartDialog; }

namespace ribi {
namespace braw {

class QtStudentStartDialogCloser;
class QtStudentStartDialogTest;

class QtStudentStartDialog final : public QDialog
{
  Q_OBJECT //!OCLINT

  public:
  explicit QtStudentStartDialog(
    const File file,
    QWidget* parent = nullptr
  );
  QtStudentStartDialog(const QtStudentStartDialog&) = delete;
  QtStudentStartDialog& operator=(const QtStudentStartDialog&) = delete;
  ~QtStudentStartDialog() noexcept;

  const File& GetFile() const noexcept { return m_file; }

  ///Does the user need to go back to the student menu?
  bool GoBackToMenu() const noexcept;

  ///Save to file
  void Save(const QString& filename);

  void StartAssociate();
  void StartConstruct();

  private slots:
  void keyPressEvent(QKeyEvent* e);
  void on_button_start_associate_clicked();
  void on_button_start_construct_clicked();

  private:
  Ui::QtStudentStartDialog *ui;

  ///Does the dialog want to go back to the student menu?
  bool m_back_to_menu;

  File m_file;

  ///Save to file
  void Save();

  friend class QtStudentStartDialogTest;
  friend class QtStudentStartDialogCloser;
};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERSTUDENTSTARTDIALOG_H
