#ifndef BRAINWEAVERFILE_H
#define BRAINWEAVERFILE_H

#include <string>
#include <vector>

#include "conceptmap.h"
#include "brainweaverfwd.h"
#include "brainweavercluster.h"
#include "conceptmaprating.h"

namespace ribi {
namespace braw {

///The File used, also the main director of the program's flow
class File
{
  public:

  //Start an empty file
  File();

  ///Create a File from all its (non-static) member variables
  File(
    const std::string& about,
    const std::string& assessor_name,
    const Cluster& cluster,
    const ribi::cmap::ConceptMap& concept_map,
    const std::string& question,
    const ribi::cmap::Rating& rating,
    const std::string& student_name,
    const std::string& version
  );

  ///AutoSave
  void AutoSave() const;

  ///Obtain the string which indicates this file is a Brainweaver file
  const std::string& GetAbout() const { return m_about; }

  ///Get the assessor his/her name
  const std::string& GetAssessorName() const { return m_assessor_name; }

  ///Get the student his/her clustering of concepts and examples
  const Cluster& GetCluster() const { return m_cluster; }
        Cluster& GetCluster()       { return m_cluster; }

  ///Get the concept map
  const ribi::cmap::ConceptMap& GetConceptMap() const { return m_concept_map; }
        ribi::cmap::ConceptMap& GetConceptMap()       { return m_concept_map; }

  ///Get the assessors' questions
  std::string GetQuestion() const;

  const auto& GetRating() const noexcept { return m_rating; }

  ///Get the student his/her name
  const std::string& GetStudentName() const { return m_student_name; }

  ///Obtain multiple test files
  static std::vector<File> GetTests() noexcept;

  ///Obtain the version of this class
  const std::string& GetVersion() const { return m_version; }

  ///Save a File
  ///File will have one line of XML
  void Save(const std::string& filename) const;

  ///Set the assessor his/her name
  void SetAssessorName(const std::string& assessor_name);

  ///Write a new clustering of concepts and examples
  ///Can only be done exactly once
  void SetCluster(const Cluster& cluster) noexcept;

  ///Write a new ConceptMap from a Cluster
  ///Can only be done exactly once
  void SetConceptMap(const ribi::cmap::ConceptMap& concept_map);

  ///Set the question
  void SetQuestion(const std::string& question);

  ///The the suggested rating
  void SetRating(const ribi::cmap::Rating& rating);

  ///Set the student his/her name
  ///Will throw if name is empty
  void SetStudentName(const std::string& student_name);

  private:

  ///The string which indicates this file is a Brainweaver file
  std::string m_about;

  ///The assessor his/her name
  std::string m_assessor_name;

  ///The clustering of items
  ///Initially will be nullptr
  Cluster m_cluster;

  ///The concept map
  ribi::cmap::ConceptMap m_concept_map;

  ///The question the student must answer
  std::string m_question;

  ///The rating that will be suggested on concepts
  ribi::cmap::Rating m_rating;

  ///The student his/her name
  std::string m_student_name;

  ///The version of this class
  std::string m_version;
};

///Count the number of edges, including those connected to the center node
int CountEdges(const File& file) noexcept;

///Count the average number of connections per non-center node
double CountEdgesPerNormalNode(
  const File& file,
  const int n_digits_behind_comma = 2
);

///Count the total number of examples
int CountExamples(const File& file) noexcept;

///Count the number of hierarchical levels
int CountHierarchicalLevels(const File& file) noexcept;

///Count the number of nodes
int CountNodes(const File& file) noexcept;

///Count the number of primary concepts
int CountPrimaryConcepts(const File& file) noexcept;

///Count the number of primary concepts
int CountSecondaryConcepts(const File& file) noexcept;

///Create a concept map with a center node with text
ribi::cmap::ConceptMap CreateConceptMap(const std::string& text) noexcept;

///Get the name of the recovery filename
//std::string GetRecoveryFilename() noexcept;

///Load a File from disk
File LoadFile(const std::string& filename);

///Convert File to XML
std::string ToXml(const File& file) noexcept;

///Convert XML to File
File XmlToFile(const std::string& s);

///Will throw if about is absent
std::string ExtractFileAboutFromXml(const std::string& s);

///Will throw if assessor name is absent
std::string ExtractFileAssessorNameFromXml(const std::string& s);

///Will return an empty cluster if absent
ribi::braw::Cluster ExtractFileClusterFromXml(const std::string& s) noexcept;

///If there is no concept map, will return an empty concept map
ribi::cmap::ConceptMap ExtractFileConceptMapFromXml(const std::string& s) noexcept;

///If there is no question, will return an empty string
std::string ExtractFileQuestionFromXml(const std::string& s) noexcept;

///Will return the default Rating if absent
ribi::cmap::Rating ExtractFileRatingFromXml(const std::string& s) noexcept;

std::string ExtractFileStudentNameFromXml(const std::string& s);
std::string ExtractFileVersionFromXml(const std::string& s);

///Tally the competencies
std::map<ribi::cmap::Competency,int> TallyCompetencies(const File& file);

///Only suitable for exact copies, use 'HasSimilarContent' when saving
///and loading a file
bool operator==(const File& lhs, const File& rhs) noexcept;
bool operator!=(const File& lhs, const File& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const File& f) noexcept;

///Obtain the File filename extension
std::string GetFilenameExtension() noexcept;

///Obtain a temporary filename
std::string GetTempFileName() noexcept;

///Obtain a test filename
std::string GetTestFileName() noexcept;

/// As operator==, except that floating point differences and
/// different Edge and Node IDs are tolerated
bool HasSimilarData(
  const File& lhs,
  const File& rhs,
  const double tolerance) noexcept;

} //~namespace braw
} //~namespace ribi

#endif // BRAINWEAVERFILE_H
