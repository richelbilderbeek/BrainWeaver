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
  //The first node removed
  const auto g = ribi::cmap::RemoveFirstNode(file.GetConceptMap());

  std::vector<ribi::cmap::Node> nodes = ribi::cmap::GetNodes(g);
  const int n_nodes{static_cast<int>(nodes.size())};

  if (nodes.size() < 2)
  {
    throw std::invalid_argument("Cannot CalculateComplexityEstimated");
  }

  ///This works, because focal node has already been deleted
  const int nrntf{static_cast<int>(boost::num_edges(g))}; //n_relations_not_to_focus
  return static_cast<int>(
    std::round(100.0
      * std::pow(
        static_cast<double>(nrntf * 2)
        / static_cast<double>(n_nodes * (n_nodes - 1) ),
        0.25
      )
    )
  );
}


int ribi::braw::CalculateComplexityExperimental(const File& file)
{
  //The first node removed
  const auto g = ribi::cmap::RemoveFirstNode(file.GetConceptMap());

  std::vector<ribi::cmap::Node> nodes = ribi::cmap::GetNodes(g);
  const int n_nodes{static_cast<int>(nodes.size())};

  if (nodes.empty())
  {
    throw std::invalid_argument("Cannot CalculateComplexityExperimental");
  }

  const int sum_rated_complexity //Constant 'k_i'
    = std::accumulate(nodes.begin(),nodes.end(),0,
    [](int& init, const ribi::cmap::Node& node)
    {
      return init + node.GetConcept().GetRatingComplexity();
    }
  );
  return static_cast<int>(
    std::round(
      50.0 * static_cast<double>(sum_rated_complexity)
       / static_cast<double>(n_nodes)
    )
  );
}


int ribi::braw::CalculateConcretenessEstimated(const File& file)
{
  //The first node removed
  const auto g = ribi::cmap::RemoveFirstNode(file.GetConceptMap());

  std::vector<ribi::cmap::Node> nodes = ribi::cmap::GetNodes(g);
  const int n_nodes{static_cast<int>(nodes.size())};

  if (nodes.empty())
  {
    throw std::invalid_argument("Cannot CalculateConcretenessEstimated");
  }

  const std::vector<ribi::cmap::Edge> edges = GetEdges(file.GetConceptMap());
  const int n_nodes_examples = std::accumulate(nodes.begin(),nodes.end(),0,
    [](int& init, const ribi::cmap::Node& node)
    {
      return init + static_cast<int>(node.GetConcept().GetExamples().Get().size());
    }
  );
  const int n_edges_examples = std::accumulate(edges.begin(),edges.end(),0,
    [](int& init, const ribi::cmap::Edge& edge)
    {
      return init + static_cast<int>(edge.GetNode().GetConcept().GetExamples().Get().size());
    }
  );

  //This works, because the focus is already removed
  const int nrntf{static_cast<int>(boost::num_edges(g))}; //n_relations_not_to_focus

  const int n_examples //Constant 'v'
    = n_nodes_examples + n_edges_examples;
  if (n_examples + n_nodes + nrntf == 0)
  {
    throw std::invalid_argument("Cannot calculate the experimental complexity");
  }
  return static_cast<int>(
    std::round(
      100.0 * static_cast<double>(n_examples)
      / static_cast<double>(n_examples + n_nodes + nrntf)
    )
  );
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
