#ifndef BRAINWEAVERMENUDIALOG_H
#define BRAINWEAVERMENUDIALOG_H

#include "menudialog.h"

namespace ribi {
namespace braw {

///The GUI independent version of Project Van Den Bogaart its menu dialog
struct MenuDialog : public ::ribi::MenuDialog
{
  About GetAbout() const noexcept;
  Help GetHelp() const noexcept;
  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  std::vector<std::string> GetVersionHistory1() const noexcept;
  std::vector<std::string> GetVersionHistory2() const noexcept;
};

} //~namespace braw
} //~namespace ribi

#endif // BRAINWEAVERMENUDIALOG_H

