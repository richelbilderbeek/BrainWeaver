#ifndef QTBRAINWEAVERDISPLAY_H
#define QTBRAINWEAVERDISPLAY_H

#include <memory>
#include "brainweaverfwd.h"

struct QWidget;
struct QTableWidget;

namespace ribi {

namespace braw {

///Functions for printing
struct QtDisplay
{
  QtDisplay();

  QTableWidget * CreateDiagnosticsWidget(
    const File& file, QWidget * const parent = nullptr
  ) const;

  QTableWidget * CreateTalliedExamplesWidget(
    const File& file, QWidget * const parent = nullptr
  ) const;

  void DisplayRatedConcepts(const File& file,QTableWidget * const table) const;
  void DisplayExamples(const File& file, QTableWidget * const table) const;
  void DisplayMiscValues(const File& file, QTableWidget * const table) const;

  private:

  void DisplayRatedConceptName(
    const ribi::cmap::Concept& concept,
    QTableWidget * const table, const int row
  ) const;
  void DisplayRatedConceptRatingComplexity(
    const ribi::cmap::Concept& concept,
    QTableWidget * const table, const int row, const int col
  ) const;
  void DisplayRatedConceptRatingConcreteness(
    const ribi::cmap::Concept& concept,
    QTableWidget * const table, const int row, const int col
  ) const;
  void DisplayRatedConceptRatingSpecificity(
    const ribi::cmap::Concept& concept,
    QTableWidget * const table, const int row, const int col
  ) const;

  ///Put number of nodes at cell (0,0) of table
  void SetNumberOfNodes(const File& file, QTableWidget * const table) const;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERDISPLAY_H
