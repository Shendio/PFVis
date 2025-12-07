cmake_minimum_required(VERSION 3.31)

project(PFVis)

add_executable(PFVis src/main.cpp)
target_compile_features(PFVis PRIVATE cxx_std_23)
set_target_properties(PFVis PROPERTIES
    CMAKE_CXX_STANDARD_REQUIRED ON
    CMAKE_CXX_EXTENSIONS OFF
)
