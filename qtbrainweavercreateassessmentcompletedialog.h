#ifndef QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_H
#define QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_H

#include "qtbrainweaverdialog.h"
#include "brainweaverfwd.h"

namespace Ui { class QtCreateAssessmentCompleteDialog; }

namespace ribi {
namespace braw {

class QtCreateAssessmentCompleteDialog : public QtDialog
{
  Q_OBJECT //!OCLINT
    
  public:
  explicit QtCreateAssessmentCompleteDialog(QWidget* parent = 0);
  QtCreateAssessmentCompleteDialog(const QtCreateAssessmentCompleteDialog&) = delete;
  QtCreateAssessmentCompleteDialog& operator=(const QtCreateAssessmentCompleteDialog&) = delete;
  ~QtCreateAssessmentCompleteDialog() noexcept;

  ///Get the filled in concept map focal question
  std::string GetQuestion() const noexcept;

  ///Must the parent go back to the menu?
  bool GoBackToMenu() const noexcept { return m_back_to_menu; }

  ///Save file to disk
  void Save(const std::string& filename) const;

  ///Fill in the concept map focal question
  void SetQuestion(const std::string& question);

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_save_clicked();

  void on_edit_textChanged(const QString &arg1);

private:
  Ui::QtCreateAssessmentCompleteDialog *ui;

  ///Must the parent go back to the menu?
  bool m_back_to_menu;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_H
