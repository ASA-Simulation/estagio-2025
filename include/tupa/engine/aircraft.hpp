#pragma once

#include <entt/entt.hpp>
#include <string>

struct coordinates {
    float lon;
    float lat;
};

struct velocity {
    float deltaLon;
    float deltaLat;
};

struct name {
    std::string value;
};

entt::entity createAircraft(entt::registry &registry, float lon, float lat,
                            float deltaLon, float deltaLat,
                            const std::string &entityName);
