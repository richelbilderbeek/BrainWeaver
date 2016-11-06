#ifndef BRAINWEAVERFILEFACTORY_H
#define BRAINWEAVERFILEFACTORY_H

#include <vector>

namespace ribi {
namespace braw {

struct File;

///Factory of File
struct FileFactory
{
  FileFactory();

  int GetNumberOfTests() const noexcept { return 6; }

  ///Empty file
  File Get0() const noexcept;

  ///File with focal question
  File Get1() const noexcept;

  ///File with complex concept map
  File Get2() const noexcept;

  ///File with complex concept map and complex cluster
  File Get3() const noexcept;

  ///File with rated complex concept map and complex cluster
  File Get4() const noexcept;

  ///File with rated complex concept map and complex cluster, all multiple lines
  File Get5() const noexcept;

  ///Get all the tests
  std::vector<File> GetTests() const noexcept;
};

} //~namespace braw
} //~namespace ribi

#endif // BRAINWEAVERFILEFACTORY_H
