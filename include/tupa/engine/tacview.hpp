#include <fstream>
#include <string>

namespace tacview {

class TacviewExporter {

  public:
    static inline TacviewExporter &getInstance() {
        if(!s_instance) {
            s_instance = new TacviewExporter();
        }
        return *s_instance;
    }

    // Delete the copy constructor and assignment operator
    TacviewExporter(const TacviewExporter &) = delete;
    TacviewExporter &operator=(const TacviewExporter &) = delete;

    void exportInstant(float duration);
    void exportEntity(int id, float longitude, float latitude, float altitude);

  private:
    TacviewExporter();
    ~TacviewExporter();

    static TacviewExporter *s_instance;

    std::ofstream m_exportFile;
};

std::string getCurrentDateTime();

inline void exportInstant(float duration) {
    TacviewExporter::getInstance().exportInstant(duration);
};

inline void exportEntity(int id, float longitude, float latitude,
                         float altitude) {
    TacviewExporter::getInstance().exportEntity(id, longitude, latitude,
                                                altitude);
}

} // namespace tacview
