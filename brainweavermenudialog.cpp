#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "brainweavermenudialog.h"

#include <cassert>
#include <iostream>

#include <boost/make_shared.hpp>

#include "container.h"
#include "conceptmap.h"
#include "fileio.h"
#include "fuzzy_equal_to.h"
#include "geometry.h"
//#include "plane.h"
#include "ribi_regex.h"

#include "xml.h"
#pragma GCC diagnostic pop

int ribi::braw::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 0;
  }
  std::cout << "This application has no console version\n";
  return 0;
}

ribi::About ribi::braw::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Brainweaver",
    "tool to create and assess concept maps",
    "June 12th of 2016",
    "2012-2016",
    "http://www.richelbilderbeek.nl/ProjectBrainweaver.htm",
    GetVersion(),
    GetVersionHistory());

  a.AddLibrary("apfloat version: 2.4.1");
  //a.AddLibrary("ConceptMap version: " + ribi::cmap::ConceptMap::GetVersion());
  a.AddLibrary("Container version: " + ribi::Container().GetVersion());
  a.AddLibrary("FileIo version: " + ribi::fileio::FileIo().GetVersion());
  a.AddLibrary("fuzzy_equal_to version: " + fuzzy_equal_to::GetVersion());
  a.AddLibrary("Geometry version: " + Geometry().GetVersion());
  a.AddLibrary("ribi::Regex version: " + ribi::Regex::GetVersion());
  return a;
}

ribi::Help ribi::braw::MenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

std::string ribi::braw::MenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::braw::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "See https://github.com/richelbilderbeek/Brainweaver/blob/master/NEWS.md"
  };
}
