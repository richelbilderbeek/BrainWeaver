#ifndef QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_H
#define QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_H

#include "brainweaverfile.h"
#include "brainweaverfwd.h"
#include "qtbrainweaverdialog.h"

namespace Ui { class QtStudentStartCompleteDialog; }

namespace ribi {
namespace braw {

class QtStudentStartCompleteDialog : public QtDialog
{
  Q_OBJECT //!OCLINT
    
  public:
  explicit QtStudentStartCompleteDialog(const File file, QWidget* parent = 0);
  QtStudentStartCompleteDialog(const QtStudentStartCompleteDialog&) = delete;
  QtStudentStartCompleteDialog& operator=(const QtStudentStartCompleteDialog&) = delete;
  ~QtStudentStartCompleteDialog() noexcept;

  ///Does the user need to go back to the student menu?
  bool GoBackToMenu() const noexcept;

  ///Save to file
  ///Will throw if there is an incorrect file extension
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
};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_H
