#pragma once

#include <entt/entity/fwd.hpp>
#include <entt/entity/registry.hpp>
#include <entt/entt.hpp>
#include <entt/process/fwd.hpp>
#include <entt/process/scheduler.hpp>

namespace tupa::engine {

class Simulation final {

  public:
    Simulation();

    void step(std::uint64_t delta);

  private:
    // simulation information
    std::uint64_t m_exec_time;

    // simulation phases
    entt::basic_scheduler<std::uint64_t> m_dynamics;
    entt::basic_scheduler<std::uint64_t> m_transmit;
    entt::basic_scheduler<std::uint64_t> m_receive;
    entt::basic_scheduler<std::uint64_t> m_process;

    entt::basic_registry<std::uint64_t> m_registry;
};

} // namespace tupa::engine
