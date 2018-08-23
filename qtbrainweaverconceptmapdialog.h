#ifndef QTBRAINWEAVERCONCEPTMAPDIALOG_H
#define QTBRAINWEAVERCONCEPTMAPDIALOG_H

#include <QDialog>
#include "qtconceptmap.h"
#include "brainweaverfile.h"
#include "conceptmap.h"

namespace Ui { class QtConceptMapDialog; }

namespace ribi {
namespace braw {

class QtConceptMapDialog final : public QDialog
{
  Q_OBJECT //!OCLINT
    
  public:
  explicit QtConceptMapDialog(const File& file, QWidget* parent = nullptr);
  QtConceptMapDialog(const QtConceptMapDialog&) = delete;
  QtConceptMapDialog& operator=(const QtConceptMapDialog&) = delete;
  ~QtConceptMapDialog() noexcept;

  ///Obtain the QtConceptMap
  const ribi::cmap::QtConceptMap * GetQtConceptMap() const;
  ribi::cmap::QtConceptMap * GetQtConceptMap();

  ///Does the user need to go back to the student menu?
  bool GoBackToMenu() const noexcept;

  bool HasClickedOk() const noexcept { return m_clicked_ok; }

  ///Update concept map into file
  void UpdateFileWithConceptMapFromWidget();

  ///Save to disk
  void Save(const QString& filename) const;

  private slots:

  void keyPressEvent(QKeyEvent *);
  void showEvent(QShowEvent *);

  ///Must use CamelCase, otherwise this slot is assumed to connect automatically
  void OnAutosave();
  void on_button_save_clicked();
  void on_button_print_clicked();

  void on_button_ok_clicked();

  void on_button_cancel_clicked();

private:
  Ui::QtConceptMapDialog *ui;

  ///Must we go back to the student menu?
  bool m_back_to_menu{false};

  ///Has the user closed the dialog using OK?
  ///Is false if the dialog is closed by Cancel or Escape
  bool m_clicked_ok{false};

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
