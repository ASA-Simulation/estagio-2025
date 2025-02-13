#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

#include <tupa/engine/tacview.hpp>

namespace tacview {

TacviewExporter *TacviewExporter::s_instance = nullptr;

TacviewExporter::TacviewExporter() {
  m_exportFile.open("../../teste.acmi");

  std::string dateTime = getCurrentDateTime();

  m_exportFile << "FileType=text/acmi/tacview" << std::endl
               << "FileVersion=2.2" << std::endl;

  m_exportFile << "0,RecordingTime=" << dateTime << std::endl
               << "0,MissionTime=" << dateTime << std::endl;

  m_exportFile << "0,LongitudeOffset=0" << std::endl
               << "0,LatitudeOffset=0" << std::endl;
}

// TacviewExporter::~TacviewExporter() {
//   std::cerr << "Been called" << std::endl;
//   m_exportFile.flush();
//   m_exportFile.close();
// }

std::string getCurrentDateTime() {
  std::time_t now = std::time(nullptr);

  std::tm tm_now = *std::gmtime(&now);

  tm_now.tm_hour -= 3; // UTC-3

  std::ostringstream oss;
  oss << std::put_time(&tm_now, "%Y-%m-%dT%H:%M:%SZ");

  return oss.str();
}

void TacviewExporter::exportInstant(float timeElapsed) {
  m_exportFile << std::fixed << std::setprecision(2) << '#' << timeElapsed
               << '\n';
  m_exportFile.flush();
}

void TacviewExporter::exportEntity(int id, std::string name, float latitude,
                                   float longitude, float altitude) {
  m_exportFile << id << ",T=" << std::fixed << std::setprecision(7) << latitude
               << '|' << longitude << '|' << std::setprecision(2) << altitude
               << ",Name=" << name << '\n';
}

} // namespace tacview
