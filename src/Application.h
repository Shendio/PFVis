#pragma once

#include "Grid.h"
#include "Pathfinder.h"

#include <memory>

enum class Algorithm : uint8_t { BFS, DFS, Dijkstra, Astar };

class Application {
public:
    Application();
    ~Application();

    Application(const Application& other) = delete;
    Application& operator=(const Application& other) = delete;

    void run();

private:
    void update();
    void render();
    void drawGUI();

    Grid m_grid;
    std::unique_ptr<Pathfinder> m_pathfinder = nullptr;

    bool m_running = false;
    bool m_dropdown_active = false;
    Algorithm m_chosen_algorithm = Algorithm::BFS;
};
