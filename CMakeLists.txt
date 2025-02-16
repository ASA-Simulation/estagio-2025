cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(tupa CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_DEBUG_POSTFIX "d")

add_compile_options("-fPIC")

find_package(EnTT CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(tupa_engine)

target_sources(tupa_engine
    PRIVATE
        source/main.cpp
        source/tacview.cpp
        source/aircraft.cpp
)

target_include_directories(tupa_engine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(tupa_engine
    EnTT::EnTT
    spdlog::spdlog
)

install(
    TARGETS     tupa_engine
    EXPORT      TupaTargets

    LIBRARY     DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE     DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME     DESTINATION ${CMAKE_INSTALL_BINDIR}
)
