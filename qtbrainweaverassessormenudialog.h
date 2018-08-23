#ifndef QTBRAINWEAVERASSESSORMENUDIALOG_H
#define QTBRAINWEAVERASSESSORMENUDIALOG_H

#include <QDialog>
#include "brainweaverfwd.h"
#include "brainweaverfile.h"

namespace Ui { class QtAssessorMenuDialog; }

namespace ribi {
namespace braw {

class QtAssessorMenuDialog final : public QDialog
{
    Q_OBJECT //!OCLINT
    
public:
  explicit QtAssessorMenuDialog(QWidget* parent = nullptr);
  QtAssessorMenuDialog(const QtAssessorMenuDialog&) = delete;
  QtAssessorMenuDialog& operator=(const QtAssessorMenuDialog&) = delete;
  ~QtAssessorMenuDialog() noexcept;


public slots:
  void Assess(const std::string& filename);
  void keyPressEvent(QKeyEvent *);
  void on_button_about_clicked();
  void on_button_assess_result_clicked();
  void on_button_create_assessment_clicked();

private:
  Ui::QtAssessorMenuDialog *ui;

  ///The currently active file
  File m_file;

  ///Saves to last saved file.
  ///If there is none, requests a file name with a dialog
  void Save() const;

  ///Simply saves to file
  void Save(const QString& filename) const;
};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERASSESSORMENUDIALOG_H
