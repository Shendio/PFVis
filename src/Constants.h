#pragma once

#include <raylib.h>
#include <string_view>

// Theme
inline constexpr Color c_background_color = {40, 42, 54, 255};
inline constexpr Color c_menu_color = {68, 71, 90, 255};
inline constexpr Color c_node_empty_color = {40, 42, 54, 255};
inline constexpr Color c_node_wall_color = {248, 248, 242, 255};
inline constexpr Color c_node_start_color = {80, 250, 123, 255};
inline constexpr Color c_node_end_color = {255, 85, 85, 255};
inline constexpr Color c_node_visited_color = {65, 75, 120, 255};
inline constexpr Color c_node_queued_color = {139, 233, 253, 255};
inline constexpr Color c_node_path_color = {241, 250, 140, 255};
inline constexpr Color c_grid_lines_color = {98, 114, 164, 80};

inline constexpr int c_defaultWidth = 1100;
inline constexpr int c_defaultHeight = 800;
inline constexpr std::string_view c_defaultTitle = "Wizualizacja algorytmów szukania ścieżki";
inline constexpr int c_menuWidth = 300;

inline constexpr int c_gridSize = 40;
inline constexpr int c_nodesSize = 20;
