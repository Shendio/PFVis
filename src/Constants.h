#pragma once

#include <string_view>

inline constexpr int c_defaultWidth = 1100;
inline constexpr int c_defaultHeight = 800;
inline constexpr std::string_view c_defaultTitle = "Pathfinding Visualizer";
inline constexpr int c_menuWidth = c_defaultWidth - c_defaultHeight;

inline constexpr int c_gridSize = 40;
inline constexpr int c_nodesSize = (c_defaultWidth - c_menuWidth) / c_gridSize;
