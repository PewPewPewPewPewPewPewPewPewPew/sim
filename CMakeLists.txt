cmake_minimum_required(VERSION 3.10)
project(simulation)

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

add_executable(sim
    sim.cc
    construction.cc
    PrimaryGeneratorAction.cc
    action.cc
    physics.cc
    Hit.cc
    SensitiveDetector.cc
)

target_include_directories(sim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sim ${Geant4_LIBRARIES})
