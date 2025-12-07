cmake_minimum_required(VERSION 3.31)

project(PFVis)

add_subdirectory(vendor/raylib)

add_executable(PFVis
    src/main.cpp
    src/Application.h
    src/Application.cpp
)
target_compile_features(PFVis PRIVATE cxx_std_23)
set_target_properties(PFVis PROPERTIES
    CMAKE_CXX_STANDARD_REQUIRED ON
    CMAKE_CXX_EXTENSIONS OFF
)
target_link_libraries(PFVis PRIVATE raylib)
# Link raygui
target_include_directories(PFVis PRIVATE vendor/raygui/src)
