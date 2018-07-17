#include "qtbrainweavercreateassessmentdialog.h"

#include <sstream>
#include <stdexcept>

#include <QKeyEvent>
#include <QFileDialog>

#include "conceptmap.h"
#include "brainweaverfile.h"
#include "conceptmapfactory.h"
#include "qtbrainweaverfiledialog.h"

#include "ui_qtbrainweavercreateassessmentdialog.h"

ribi::braw::QtCreateAssessmentDialog::QtCreateAssessmentDialog(QWidget* parent)
  : QtDialog(parent),
    ui(new Ui::QtCreateAssessmentDialog),
    m_back_to_menu(false)
{
  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help
}

ribi::braw::QtCreateAssessmentDialog::~QtCreateAssessmentDialog() noexcept
{
  delete ui;
}

std::string ribi::braw::QtCreateAssessmentDialog::GetQuestion() const noexcept
{
  return ui->edit->text().toStdString();
}

ribi::cmap::Rating ribi::braw::QtCreateAssessmentDialog::GetRating() const
{
  return ribi::cmap::Rating(
    GetRatingComplexity(),
    GetRatingConcreteness(),
    GetRatingSpecificity()
  );
}


ribi::cmap::RatingComplexity ribi::braw::QtCreateAssessmentDialog::GetRatingComplexity() const
{
  // { {number of edges, number of examples}, score }
  std::map<std::pair<int, int>, int> m;
  // X/column: n_examples
  // Y/row: n_edges
  const int n_cols = ui->table_complexity->columnCount();
  const int n_rows = ui->table_complexity->rowCount();
  for (int col = 0; col != n_cols; ++col)
  {
    for (int row = 0; row != n_rows; ++row)
    {
      const int n_examples{col};
      const int n_edges{row};
      const int score{
        ui->table_complexity->itemAt(col, row)->text().toInt()
      };
      m.insert( { { n_edges, n_examples }, score } );
    }
  }
  return ribi::cmap::RatingComplexity(m);
}

ribi::cmap::RatingConcreteness ribi::braw::QtCreateAssessmentDialog::GetRatingConcreteness() const
{
  std::map<int, int> m;
  // X/column: n_examples
  const int n_cols = ui->table_concreteness->columnCount();
  for (int col = 0; col != n_cols; ++col)
  {
    const int n_examples{col};
    const int score{
      ui->table_concreteness->itemAt(col, 0)->text().toInt()
    };
    m.insert( { n_examples , score } );
  }
  return ribi::cmap::RatingConcreteness(m);
}

ribi::cmap::RatingSpecificity ribi::braw::QtCreateAssessmentDialog::GetRatingSpecificity() const
{
  std::map<int, int> m;
  // X/column: n_examples
  const int n_cols = ui->table_specificity->columnCount();
  for (int col = 0; col != n_cols; ++col)
  {
    const int n_examples{col};
    const int score{
      ui->table_specificity->itemAt(col, 0)->text().toInt()
    };
    m.insert( { n_examples , score } );
  }
  return ribi::cmap::RatingSpecificity(m);
}

void ribi::braw::QtCreateAssessmentDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key() == Qt::Key_Escape)
  {
    emit remove_me(this);
    close();
    return;
  }
}

void ribi::braw::QtCreateAssessmentDialog::on_button_save_clicked()
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla het assessment invoer-bestand op");
  const int status = d->exec();
  if (status == QDialog::Rejected)
  {
    this->show();
    return;
  }
  assert(d->selectedFiles().size() == 1);
  const std::string filename = d->selectedFiles()[0].toStdString();
  assert(!filename.empty());
  Save(filename);
  m_back_to_menu = true;
  emit remove_me(this);
}

void ribi::braw::QtCreateAssessmentDialog::Save(const std::string& filename) const
{
  File file;
  file.SetQuestion(GetQuestion());
  file.SetRating(GetRating());
  assert(file.GetQuestion() == GetQuestion());
  assert(file.GetRating() == GetRating());
  file.Save(filename);
}

void ribi::braw::QtCreateAssessmentDialog::SetQuestion(const std::string& question)
{
  ui->edit->setText(question.c_str());
}

void ribi::braw::QtCreateAssessmentDialog::on_edit_textChanged(const QString &arg1)
{
  assert(ui->edit->text() == arg1);
  ui->button_save->setEnabled(!arg1.isEmpty());

}
