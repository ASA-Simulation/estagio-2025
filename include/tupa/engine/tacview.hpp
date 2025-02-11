#include <string>

namespace tacview {

void startFile();
std::string getCurrentDateTime();
void exportInstant(float duration);
void exportEntity(int id, float longitude, float latitude, float altitude);

} // namespace tacview
