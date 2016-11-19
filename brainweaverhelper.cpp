#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
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
#include "testtimer.h"
#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::braw::CalculateComplexityEstimated(const File& file)
{
  return ribi::cmap::CalculateComplexityEstimated(file.GetConceptMap());
}


int ribi::braw::CalculateComplexityExperimental(const File& file)
{
  return ribi::cmap::CalculateComplexityExperimental(file.GetConceptMap());
}


int ribi::braw::CalculateConcretenessEstimated(const File& file)
{
  return ribi::cmap::CalculateConcretenessEstimated(file.GetConceptMap());
}


int ribi::braw::CalculateConcretenessExperimental(const File& file)
{
  //The first node removed
  const auto g = ribi::cmap::RemoveFirstNode(file.GetConceptMap());
  std::vector<ribi::cmap::Node> nodes = ribi::cmap::GetNodes(g);

  if (nodes.empty())
  {
    throw std::invalid_argument("Cannot CalculateConcretenessExperimental");
  }

  const int src // sum_rated_concreteness
    = std::accumulate(nodes.begin(),nodes.end(),0,
    [](int& init, const ribi::cmap::Node& node)
    {
      return init + node.GetConcept().GetRatingConcreteness();
    }
  );
  return static_cast<int>(
    std::round(
      50.0 * static_cast<double>(src)
      / static_cast<double>(nodes.size())
    )
  );
}

int ribi::braw::CalculateRichnessExperimental(const File& file)
{
  if (HasUnitializedExamples(file))
  {
    throw std::invalid_argument(
      "Cannot calculate richness if not all examples are rated"
    );
  }
  #ifndef KNOW_IF_NEEDS_TO_REMOVE_FIRST_NOTE
  //Must or must not the center node be removed?
  //H: no, because a center node has no examples
  const int a{
    ribi::cmap::CalculateRichnessExperimental(file.GetConceptMap())
  };
  assert(ribi::cmap::IsCenterNode(ribi::cmap::GetFirstNode(file.GetConceptMap())));
  assert(ribi::cmap::GetCenterNode(file.GetConceptMap()).GetConcept().GetExamples().Get().empty());

  const int b{
    ribi::cmap::CalculateRichnessExperimental(
      ribi::cmap::RemoveFirstNode(file.GetConceptMap())
    )
  };
  assert(a == b);
  #endif
  return ribi::cmap::CalculateRichnessExperimental(file.GetConceptMap());
}

int ribi::braw::CalculateSpecificityExperimental(const File& file)
{
  using namespace ribi::cmap;

  //The first node removed, as this is the focal question
  assert(IsCenterNode(GetFirstNode(file.GetConceptMap())));
  const auto g = ribi::cmap::RemoveFirstNode(file.GetConceptMap());

  const std::vector<ribi::cmap::Node> nodes = ribi::cmap::GetNodes(g);

  if (nodes.empty())
  {
    throw std::invalid_argument("Cannot CalculateSpecificityExperimental");
  }

  const int srs //sum_rated_specificity
    = std::accumulate(nodes.begin(),nodes.end(),0,
    [](int& init, const ribi::cmap::Node& node)
    {
      return init + node.GetConcept().GetRatingSpecificity();
    }
  );
  return static_cast<int>(
    std::round(
      static_cast<double>(50 * srs)
      / static_cast<double>(nodes.size())
    )
  );
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
