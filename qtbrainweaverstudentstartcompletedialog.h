#ifndef QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_H
#define QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_H

#include <QDialog>
#include "brainweaverfile.h"
#include "brainweaverfwd.h"

namespace Ui { class QtStudentStartCompleteDialog; }

namespace ribi {
namespace braw {

class qtbrainweaverstudentstartcompletedialog_test;

class QtStudentStartCompleteDialog : public QDialog
{
  Q_OBJECT //!OCLINT
    
  public:
  explicit QtStudentStartCompleteDialog(
    const File file,
    QWidget* parent = nullptr
  );
  QtStudentStartCompleteDialog(const QtStudentStartCompleteDialog&) = delete;
  QtStudentStartCompleteDialog& operator=(const QtStudentStartCompleteDialog&) = delete;
  ~QtStudentStartCompleteDialog() noexcept;

  ///Does the user need to go back to the student menu?
  bool GoBackToMenu() const noexcept;

  ///Save to file
  void Save(const std::string& filename);

  void StartAssociate();
  void StartConstruct();

  private slots:
  void keyPressEvent(QKeyEvent* e);
  void on_button_start_associate_clicked();
  void on_button_start_construct_clicked();

  private:
  Ui::QtStudentStartCompleteDialog *ui;

  ///Does the dialog want to go back to the student menu?
  bool m_back_to_menu;

  File m_file;

  ///Save to file
  void Save();

  friend class qtbrainweaverstudentstartcompletedialog_test;
};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_H
