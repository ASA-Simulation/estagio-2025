#include <tupa/engine/aircraft.hpp>

entt::entity createAircraft(entt::registry &registry, float lon, float lat,
                            float deltaLon, float deltaLat,
                            const std::string &entityName) {
    const auto aircraft = registry.create();
    registry.emplace<coordinates>(aircraft, lon, lat);
    registry.emplace<velocity>(aircraft, deltaLon, deltaLat);
    registry.emplace<name>(aircraft, entityName);
    return aircraft;
}
