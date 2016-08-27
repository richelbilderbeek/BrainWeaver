//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2016 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "brainweaverhelper.h"

#include <cassert>
#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>
#include <QFile>
#include <QRegExp>

#include "brainweaverfile.h"
#include "conceptmaphelper.h"
#include "testtimer.h"
#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::braw::CalculateConcretenessExperimental(const File& file)
{
  //The first node removed
  const auto g = RemoveFirstNode(file.GetConceptMap());
  std::vector<ribi::cmap::Node> nodes = ribi::cmap::GetNodes(g);

  assert(!nodes.empty());
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

  std::map<cmap::Competency,int> m = TallyCompetencies(file);

  //The first node removed, as this is the focal question
  const auto g = RemoveFirstNode(file.GetConceptMap());
  //const std::vector<ribi::cmap::Node> nodes = ribi::cmap::GetNodes(g);

  //Remove category 'misc'
  #ifndef NDEBUG
  const int debug_m_size_old = static_cast<int>(m.size());
  const bool debug_will_resize = m.count(cmap::Competency::misc);
  #endif
  m.erase(cmap::Competency::misc);
  #ifndef NDEBUG
  const int debug_m_size_new = static_cast<int>(m.size());
  assert( ( debug_will_resize && debug_m_size_old == debug_m_size_new + 1)
       || (!debug_will_resize && debug_m_size_old == debug_m_size_new    )
  );
  #endif


  const int a = static_cast<int>(m.size());
  const int n_examples = std::accumulate(m.begin(),m.end(),0,
    [](int& init,const std::pair<cmap::Competency,int>& p)
    {
      return init + p.second;
    }
  );
  const int my_min = static_cast<int>(std::ceil( static_cast<double>(n_examples) / 12.0));
  const int my_max = static_cast<int>(std::floor(static_cast<double>(n_examples) /  4.0));
  const int b = std::count_if(m.begin(),m.end(),
    [my_min,my_max](const std::pair<cmap::Competency,int>& p)
    {
      return p.second >= my_min && p.second <= my_max;
    }
  );

  return static_cast<int>(
    std::round(
      100.0 * ( static_cast<double>(a+b) / 12.0)
    )
  );
}

int ribi::braw::CalculateSpecificityExperimental(const File& file)
{
  //The first node removed, as this is the focal question
  const auto g = RemoveFirstNode(file.GetConceptMap());

  const std::vector<ribi::cmap::Node> nodes = ribi::cmap::GetNodes(g);
  assert(!nodes.empty());

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
