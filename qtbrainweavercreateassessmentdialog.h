#ifndef QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_H
#define QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_H

#include "qtbrainweaverdialog.h"
#include "brainweaverfwd.h"
#include "conceptmaprating.h"

namespace Ui { class QtCreateAssessmentDialog; }

namespace ribi {
namespace braw {

class QtCreateAssessmentDialog : public QtDialog
{
  Q_OBJECT //!OCLINT
    
  public:
  explicit QtCreateAssessmentDialog(QWidget* parent = 0);
  QtCreateAssessmentDialog(const QtCreateAssessmentDialog&) = delete;
  QtCreateAssessmentDialog& operator=(const QtCreateAssessmentDialog&) = delete;
  ~QtCreateAssessmentDialog() noexcept;

  ///Get the filled in concept map focal question
  std::string GetQuestion() const noexcept;

  ///Get the automatic rating scores
  ribi::cmap::Rating GetRating() const;

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
  Ui::QtCreateAssessmentDialog *ui;

  ///Must the parent go back to the menu?
  bool m_back_to_menu;

  ///Get the automatic rating scores
  ribi::cmap::RatingComplexity GetRatingComplexity() const;

  ///Get the automatic rating scores
  ribi::cmap::RatingConcreteness GetRatingConcreteness() const;

  ///Get the automatic rating scores
  ribi::cmap::RatingSpecificity GetRatingSpecificity() const;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_H
