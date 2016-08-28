//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2013-2016 Richel Bilderbeek

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
#ifndef BRAINWEAVERFILE_H
#define BRAINWEAVERFILE_H

#include <string>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmap.h"
#include "brainweaverfwd.h"
#include "brainweavercluster.h"
#pragma GCC diagnostic pop

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

  ///Set the student his/her name
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

  ///The student his/her name
  std::string m_student_name;

  ///The version of this class
  std::string m_version;
};


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
std::string ExtractFileStudentNameFromXml(const std::string& s);
std::string ExtractFileVersionFromXml(const std::string& s);

///Tally the competencies
std::map<ribi::cmap::Competency,int> TallyCompetencies(const File& file);

bool operator==(const File& lhs, const File& rhs) noexcept;
bool operator!=(const File& lhs, const File& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const File& f) noexcept;

///Obtain the File filename extension
std::string GetFilenameExtension() noexcept;

///Obtain a temporary filename
std::string GetTempFileName() noexcept;

///Obtain a test filename
std::string GetTestFileName() noexcept;

} //~namespace braw
} //~namespace ribi

#endif // BRAINWEAVERFILE_H
