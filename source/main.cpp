#include <entt/entt.hpp>
#include <spdlog/spdlog.h>

#include <tupa/engine/tacview.hpp>

// Aircraft coordinates in decimal notation
struct coordinates {
    float lon;
    float lat;
};

// Aircraft speed
struct velocity {
    float deltaLon;
    float deltaLat;
};

// Aircraft name
struct name {
    std::string value;
};

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

        tacview::exportEntity(static_cast<uint32_t>(entity) + 1, eName.value, crd.lon, crd.lat,
                              10000);
    }
}

int main() {
    int frameRate = 24;     // Frames per Second
    int simulationTime = 5; // Simulation time (seconds)

    entt::registry registry;

    const auto aircraft = registry.create();
    struct coordinates initialCrd{-46.473056, -23.435556};
    struct velocity initialSpd{0.04, 0.09};
    struct name entityName{"C172"};

    registry.emplace<coordinates>(aircraft, initialCrd.lon, initialCrd.lat);
    registry.emplace<velocity>(aircraft, initialSpd.deltaLon, initialSpd.deltaLat);
    registry.emplace<name>(aircraft, entityName.value);

    const std::chrono::milliseconds frameDuration(1000 / frameRate);
    auto inicioTotal = std::chrono::high_resolution_clock::now();
    auto fimTotal = inicioTotal + std::chrono::seconds(simulationTime);

    while(std::chrono::high_resolution_clock::now() < fimTotal) {

        std::chrono::duration<float> currentFrame =
            std::chrono::high_resolution_clock::now() - inicioTotal;

        tacview::exportInstant(currentFrame.count());

        auto start = std::chrono::high_resolution_clock::now();

        update(registry);

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;

        std::this_thread::sleep_for(
            frameDuration -
            std::chrono::duration_cast<std::chrono::milliseconds>(duration));
    }
}
