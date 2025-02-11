#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <tupa/engine/tacview.hpp>
#include <vector>

namespace tacview {

std::ofstream exportFile;

std::string getCurrentDateTime() {
    std::time_t now = std::time(nullptr);

    std::tm tm_now = *std::gmtime(&now);

    tm_now.tm_hour -= 3; // UTC-3

    std::ostringstream oss;
    oss << std::put_time(&tm_now, "%Y-%m-%dT%H:%M:%SZ");

    return oss.str();
}

void startFile() {
    exportFile.open("../../teste.acmi");
    std::string dateTime = getCurrentDateTime();

    exportFile << "FileType=text/acmi/tacview" << std::endl
               << "FileVersion=2.2" << std::endl;

    exportFile << "0,RecordingTime=" << dateTime << std::endl
               << "0,MissionTime=" << dateTime << std::endl;

    exportFile << "0,LongitudeOffset=0" << std::endl
               << "0,LatitudeOffset=0" << std::endl;

    exportFile.close();
}

void exportInstant(float timeElapsed) {
    exportFile.open("../../teste.acmi", std::ios::app);

    exportFile << std::fixed << std::setprecision(2) << '#' << timeElapsed
               << '\n';

    exportFile.close();
}

void exportEntity(int id, float longitude, float latitude, float altitude) {
    exportFile.open("../../teste.acmi", std::ios::app);

    exportFile << id << ",T=" << id << std::fixed << std::setprecision(2)
               << longitude << '|' << latitude << '|' << altitude << '\n';

    exportFile.close();
}

} // namespace tacview
