#include <entt/entt.hpp>
#include <spdlog/spdlog.h>

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

    for(auto entity: view) {
        auto &vel = view.get<velocity>(entity);
        spdlog::info("Vel: dx={}, dy={}", vel.dx, vel.dy);
    }
}

int main() {
    entt::registry registry;

    for(auto i = 0u; i < 10u; ++i) {
        const auto entity = registry.create();
        registry.emplace<position>(entity, i * 1.f, i * 1.f);
        if(i % 2 == 0) { registry.emplace<velocity>(entity, i * .1f, i * .1f); }
    }

    update(registry);
}
