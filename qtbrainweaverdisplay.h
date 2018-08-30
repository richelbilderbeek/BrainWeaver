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

  QTableWidget * CreateRatedConceptsWidget(
    const File& file, QWidget * const parent = nullptr
  ) const;

  QTableWidget * CreateTalliedCompetenciesWidget(
    const File& file, QWidget * const parent = nullptr
  ) const;

  private:

  void DisplayDiagnosticsHeader(QTableWidget * const table) const;
  void DisplayDiagnosticsItems(const File& file, QTableWidget * const table) const;

  void DisplayTalliedCompetencies(const File& file, QTableWidget * const table) const;

  void DisplayTalliedCompetenciesHeader(QTableWidget * const table) const;
  void DisplayTalliedCompetenciesItems(const File& file, QTableWidget * const table) const;

  std::array<std::string, 7> CreateTalliedCompetenciesTexts(const File& file) const;

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
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERDISPLAY_H
