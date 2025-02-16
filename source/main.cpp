#include <entt/entt.hpp>
#include <spdlog/spdlog.h>

#include <tupa/engine/aircraft.hpp>
#include <tupa/engine/tacview.hpp>

// Main Loop
void update(entt::registry &registry) {
    auto view = registry.view<coordinates, velocity, name>();

    for(auto entity : view) {
        auto &crd = view.get<coordinates>(entity);
        auto &vel = view.get<velocity>(entity);
        auto &eName = view.get<name>(entity);

        crd.lon += vel.deltaLon;
        crd.lat += vel.deltaLat;

        spdlog::info("Entity ID: {}", static_cast<uint32_t>(entity) + 1);
        spdlog::info("Entity Name: {}", eName.value);
        spdlog::info("longitude: {}, latitude: {}", crd.lon, crd.lat);
        spdlog::info("spd: dlat={}, dlon={}", vel.deltaLon, vel.deltaLat);

        tacview::exportEntity(static_cast<uint32_t>(entity) + 1, eName.value,
                              crd.lon, crd.lat, 10000);
    }
}

int main() {
    int timeStep = 100;         //       Time step (milliseconds)
    int simulationTime = 10000; // Simulation time (milisseconds)
    int timeElapsed = 0;        //    Time elapsed (milisseconds)

    entt::registry registry;

    createAircraft(registry, -46.473056, -23.435556, 0.04, 0.09, "C172");

    while(timeElapsed < simulationTime) {
        tacview::TacviewExporter::getInstance().exportInstant(timeElapsed /
                                                              1000.0);
        update(registry);
        timeElapsed += timeStep;
    }

    // class destructor isn't called during execution time
    tacview::TacviewExporter::getInstance().flush();

    return 0;
}
