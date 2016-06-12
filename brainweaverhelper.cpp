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

#include "conceptmaphelper.h"
#include "testtimer.h"
#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

double ribi::braw::GetDistance(const double delta_x, const double delta_y)
{
  return std::sqrt( (delta_x * delta_x) + (delta_y * delta_y) );
}

double ribi::braw::GetDistance(const double x1, const double y1, const double x2, const double y2)
{
  return GetDistance(x1-x2,y1-y2);
}

std::vector<std::string> ribi::braw::SafeFileToVector(const std::string& filename)
{
  std::vector<std::string> v = ribi::fileio::FileIo().FileToVector(filename);
  if (!v.empty() && v.back().empty()) v.pop_back();
  return v;
}

std::vector<std::string> ribi::braw::SplitXml(const std::string& s)
{
  std::vector<std::string> v;
  std::string::const_iterator i = s.begin();
  std::string::const_iterator j = s.begin();
  const std::string::const_iterator end = s.end();
  while (j!=end)
  {
    ++j;
    if ((*j=='>' || *j == '<') && std::distance(i,j) > 1)
    {
      std::string t;
      std::copy(
        *i=='<' ? i   : i+1,
        *j=='>' ? j+1 : j,
        std::back_inserter(t));
      v.push_back(t);
      i = j;
    }
  }
  return v;
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

std::vector<std::string> ribi::braw::XmlToPretty(const std::string& s)
{
  std::vector<std::string> v = SplitXml(s);
  int n = -2;
  std::for_each(v.begin(),v.end(),
    [&n](std::string& s)
    {
      assert(!s.empty());
      if (s[0] == '<' && s[1] != '/')
      {
        n+=2;
      }
      s = std::string(n,' ') + s;
      if (s[n+0] == '<' && s[n+1] == '/')
      {
        n-=2;
      }
    }
  );
  return v;
}
