



#include "brainweaverhelper.h"

#include <cassert>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include <QFile>
#include <QRegExp>

#include "brainweaverfile.h"
#include "conceptmap.h"
#include "conceptmaphelper.h"
#include "fileio.h"


int ribi::braw::CalculateComplexityExperimental(const File& file)
{
  return ribi::cmap::CalculateComplexityExperimental(file.GetConceptMap());
}

int ribi::braw::CalculateConcretenessExperimental(const File& file)
{
  return ribi::cmap::CalculateConcretenessExperimental(file.GetConceptMap());
}

int ribi::braw::CalculateRichnessExperimental(const File& file)
{
  if (HasUnitializedExamples(file))
  {
    throw std::invalid_argument(
      "Cannot calculate richness if not all examples are rated"
    );
  }
  return ribi::cmap::CalculateRichnessExperimental(file.GetConceptMap());
}

int ribi::braw::CalculateSpecificityExperimental(const File& file)
{
  return ribi::cmap::CalculateSpecificityExperimental(file.GetConceptMap());
}

bool ribi::braw::HasUnitializedExamples(const File& file) noexcept
{
  return ribi::cmap::HasUninitializedExamples(file.GetConceptMap());
}

std::string ribi::braw::Unwordwrap(
  const std::vector<std::string>& v) noexcept
{
  return ribi::cmap::Unwordwrap(v);
}

std::vector<std::string> ribi::braw::Wordwrap(
  const std::string& s_original, const std::size_t max_len) noexcept
{
  return ribi::cmap::Wordwrap(s_original, max_len);
}
