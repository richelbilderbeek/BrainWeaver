#ifndef QTBRAINWEAVERDISPLAY_TEST_H
#define QTBRAINWEAVERDISPLAY_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtDisplayTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void CreateRatedConceptsWidgetOnEmptyGraphThrows() const noexcept;
};

} //~namespace braw
} //~namespace ribi



#endif // QTBRAINWEAVERDISPLAY_TEST_H
