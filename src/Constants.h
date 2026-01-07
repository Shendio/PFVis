#pragma once

#include <cstdint>
#include <string_view>

namespace Utils {
    inline constexpr unsigned int toHex(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        return (r << 24 | g << 16 | b << 8 | a);
    }
}

namespace Theme {
    inline constexpr unsigned int base_color = Utils::toHex(40, 42, 54);
    inline constexpr unsigned int menu_color = Utils::toHex(68, 71, 90);
    inline constexpr unsigned int node_empty_color = Utils::toHex(40, 42, 54);
    inline constexpr unsigned int node_wall_color = Utils::toHex(218, 218, 218);
    inline constexpr unsigned int node_start_color = Utils::toHex(80, 250, 123);
    inline constexpr unsigned int node_end_color = Utils::toHex(255, 85, 85);
    inline constexpr unsigned int node_visited_color = Utils::toHex(65, 75, 120);
    inline constexpr unsigned int node_queued_color = Utils::toHex(139, 233, 253);
    inline constexpr unsigned int node_path_color = Utils::toHex(241, 250, 140);
    inline constexpr unsigned int grid_lines_color = Utils::toHex(98, 114, 164, 80);
}

namespace Settings {
    inline constexpr int default_width = 1100;
    inline constexpr int default_height = 800;
    inline constexpr std::string_view default_title = "Wizualizacja algorytmów szukania ścieżki";
    inline constexpr int menu_width = 300;

    inline constexpr int grid_size = 40;
    inline constexpr int nodes_size = 20;
}
