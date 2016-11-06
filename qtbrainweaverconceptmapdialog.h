#ifndef QTBRAINWEAVERCONCEPTMAPDIALOG_H
#define QTBRAINWEAVERCONCEPTMAPDIALOG_H

#include "qtconceptmap.h"
#include "brainweaverfile.h"
#include "qtbrainweaverdialog.h"
#include "conceptmap.h"

namespace Ui { class QtConceptMapDialog; }

namespace ribi {
namespace braw {

class QtConceptMapDialog : public QtDialog
{
  Q_OBJECT //!OCLINT
    
  public:
  explicit QtConceptMapDialog(const File& file, QWidget* parent = 0);
  QtConceptMapDialog(const QtConceptMapDialog&) = delete;
  QtConceptMapDialog& operator=(const QtConceptMapDialog&) = delete;
  ~QtConceptMapDialog() noexcept;

  ///Obtain the widget
  const ribi::cmap::QtConceptMap * GetWidget() const;
  ribi::cmap::QtConceptMap * GetWidget();

  ///Does the user need to go back to the student menu?
  bool GoBackToMenu() const noexcept;

  ///Update concept map into file
  void UpdateFileWithConceptMapFromWidget();

  ///Save to disk
  void Save(const std::string& filename) const;

  private slots:

  void keyPressEvent(QKeyEvent *);
  void showEvent(QShowEvent *);

  ///Must use CamelCase, otherwise this slot is assumed to connect automatically
  void OnAutosave();
  void on_button_save_clicked();
  void on_button_print_clicked();

private:
  Ui::QtConceptMapDialog *ui;

  ///Must we go back to the student menu?
  bool m_back_to_menu;

  ///The file
  File m_file;

  ///The concept map widget
  ribi::cmap::QtConceptMap * const m_widget;
};

///Create a concept map from a cluster
ribi::cmap::ConceptMap CreateFromCluster(
  const std::string& question,
  const Cluster& cluster
);

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCONCEPTMAPDIALOG_H
