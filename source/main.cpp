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
    auto view = registry.view<const position, velocity>();

    for (auto entity : view) {
        auto &vel = view.get<velocity>(entity);
        spdlog::info("Vel: dx={}, dy={}", vel.dx, vel.dy);
    }
}

int main() {
    int frameRate = 24;     // Frames per Second
    int simulationTime = 5; // Simulation time (seconds)

    entt::registry registry;

    tacview::startFile();

    const auto entity = registry.create();

    const std::chrono::milliseconds frameDuration(1000 / frameRate);
    auto inicioTotal = std::chrono::high_resolution_clock::now();
    auto fimTotal = inicioTotal + std::chrono::seconds(simulationTime);

    tacview::exportInstant(0.00);

    while (std::chrono::high_resolution_clock::now() < fimTotal) {
        auto start = std::chrono::high_resolution_clock::now();

        update(registry);

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;

        std::this_thread::sleep_for(
            frameDuration -
            std::chrono::duration_cast<std::chrono::milliseconds>(duration));

        std::chrono::duration<float> currentFrame =
            std::chrono::high_resolution_clock::now() - inicioTotal;

        tacview::exportInstant(currentFrame.count());
    }
}
