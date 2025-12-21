#pragma once

#include "Grid.h"

enum class Algorithm : uint8_t {
    BFS,
    DFS,
    Dijkstra,
    Astar
};

class Application {
public:
    Application();
    ~Application();

    Application(const Application& other) = delete;
    Application& operator=(const Application& other) = delete;

    void run();

private:
    void drawGUI();

    Grid m_grid;

    bool m_dropdown_active = false;
    Algorithm m_chosen_algorithm = Algorithm::BFS;
};
