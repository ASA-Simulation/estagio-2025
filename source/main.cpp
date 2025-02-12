#include <entt/entt.hpp>
#include <spdlog/spdlog.h>

#include <tupa/engine/tacview.hpp>

struct position {
    float x;
    float y;
};

struct velocity {
    float dx;
    float dy;
};

void update(entt::registry &registry) {
    auto view = registry.view<position, velocity>();

    for (auto entity : view) {
        auto &pos = view.get<position>(entity);
        auto &vel = view.get<velocity>(entity);

        pos.x += vel.dx;
        pos.y += vel.dy;

        spdlog::info("Entity ID: {}", static_cast<uint32_t>(entity) + 1);
        spdlog::info("pos: x={}, y={}", pos.x, pos.y);
        spdlog::info("spd: dx={}, dy={}", vel.dx, vel.dy);

        tacview::exportEntity(static_cast<uint32_t>(entity) + 1, pos.x, pos.y,
                              10000);
    }
}

int main() {
    int frameRate = 24;     // Frames per Second
    int simulationTime = 5; // Simulation time (seconds)

    entt::registry registry;

    const auto plane = registry.create();
    struct position initialPos {
        -46.473056, -23.435556
    };
    struct velocity initialSpd {
        0.04, 0.09
    };

    registry.emplace<position>(plane, initialPos.x, initialPos.y);
    registry.emplace<velocity>(plane, initialSpd.dx, initialSpd.dy);

    const std::chrono::milliseconds frameDuration(1000 / frameRate);
    auto inicioTotal = std::chrono::high_resolution_clock::now();
    auto fimTotal = inicioTotal + std::chrono::seconds(simulationTime);

    while (std::chrono::high_resolution_clock::now() < fimTotal) {

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
