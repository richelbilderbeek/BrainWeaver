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
