cmake_minimum_required(VERSION 3.31)

project(PFVis)

add_subdirectory(vendor/raylib)

add_executable(PFVis
    src/main.cpp
    src/Application.h
    src/Application.cpp
    src/Node.h
    src/Grid.h
    src/Grid.cpp
    src/Constants.h
    src/Pathfinder.h
    src/BfsPathfinder.h
    src/BfsPathfinder.cpp
    src/DfsPathfinder.h
    src/DfsPathfinder.cpp
    src/HeuristicPathfinder.h
    src/HeuristicPathfinder.cpp
)
target_compile_features(PFVis PRIVATE cxx_std_23)
set_target_properties(PFVis PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
target_link_libraries(PFVis PRIVATE raylib)
# Link raygui
target_include_directories(PFVis PRIVATE vendor/raygui/src)
