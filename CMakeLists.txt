cmake_minimum_required(VERSION 3.10)
project(simulation)

# Find Geant4 package
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

# Find ROOT package
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})
link_directories(${ROOT_LIBRARY_DIR})

# List of source files
set(SOURCES
    sim.cc
    construction.cc
    PrimaryGeneratorAction.cc
    action.cc
    physics.cc
    Hit.cc
    SensitiveDetector.cc
    Run.cc
)

# Add the executable
add_executable(sim ${SOURCES})

# Include directories
target_include_directories(sim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link libraries
target_link_libraries(sim ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
