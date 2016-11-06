#ifndef QTBRAINWEAVERCLUSTERDIALOG_H
#define QTBRAINWEAVERCLUSTERDIALOG_H

#include "qtbrainweaverdialog.h"
#include "brainweaverfile.h"
#include "qtbrainweaverfwd.h"

namespace Ui { class QtClusterDialog; }

namespace ribi {
namespace braw {

struct qtbrainweaverclusterdialog_test;

///The Dialog in which the user clusters concepts and examples
///If the file supplied has no cluster, this dialog creates a cluster
///because the widget needs something to work on
class QtClusterDialog : public QtDialog
{
  Q_OBJECT //!OCLINT

public:
  explicit QtClusterDialog(const File& file, QWidget* parent = 0);
  QtClusterDialog(const QtClusterDialog&) = delete;
  QtClusterDialog& operator=(const QtClusterDialog&) = delete;
  ~QtClusterDialog() noexcept;

  const Ui::QtClusterDialog * GetUi() const noexcept { return ui; }
        Ui::QtClusterDialog * GetUi()       noexcept { return ui; }

  ///Obtain the widget
  QtClusterWidget * GetWidget();
  const QtClusterWidget * GetWidget() const;

  ///Does the dialog want to go back to the student menu?
  bool GoBackToMenu() const { return m_back_to_menu; }

  //Save to disk
  void Save(const std::string& filename);


protected:
  ///Respond to the following keys:
  ///F2: edit current item
  ///Delete: remove current item
  void keyPressEvent(QKeyEvent *);

public slots:

  void on_button_add_clicked();
  void on_button_next_clicked();

  void on_button_save_clicked();

private:
  Ui::QtClusterDialog *ui;

  ///Does the dialog want to go back to the student menu?
  bool m_back_to_menu;

  ///The file
  File m_file;

  ///The cluster widget
  QtClusterWidget * const m_widget;


  //Start saving procedure, with request of filename
  void Save();

  friend class qtbrainweaverclusterdialog_test;
};

///Add a Cluster to the file if it is not yet present,
///Create a QtClusterWidget from the file its cluster
QtClusterWidget * BuildWidget(File file);

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCLUSTERDIALOG_H
