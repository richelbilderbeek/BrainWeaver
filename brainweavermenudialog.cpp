#include "brainweavermenudialog.h"

#include <cassert>
#include <iostream>

#include "conceptmap.h"
#include "container.h"
#include "fileio.h"
#include "geometry.h"
#include "ribi_regex.h"
#include "xml.h"

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
    "BrainWeaver",
    "tool to create and assess concept maps",
    "August 6th of 2018",
    "2012-2018",
    "http://www.richelbilderbeek.nl/ProjectBrainWeaver.htm",
    GetVersion(),
    GetVersionHistory());

  a.AddLibrary("apfloat version: 2.4.1");
  a.AddLibrary("Container version: " + ribi::Container().GetVersion());
  a.AddLibrary("FileIo version: " + ribi::fileio::FileIo().GetVersion());
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
    "See https://github.com/richelbilderbeek/BrainWeaver/blob/master/NEWS.md"
  };
}
