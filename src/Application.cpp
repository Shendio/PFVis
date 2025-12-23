#include "Application.h"
#include "BfsPathfinder.h"
#include "Constants.h"
#include "DfsPathfinder.h"
#include "HeuristicPathfinder.h"

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

Application::Application() {
    InitWindow(c_defaultWidth, c_defaultHeight, c_defaultTitle.data());
    SetTargetFPS(60);
}

Application::~Application() {
    CloseWindow();
}

void Application::run() {
    while (!WindowShouldClose()) {
        update();
        render();
    }
}

void Application::update() {
    if (!m_running && !m_dropdown_active) {
        auto mouse_pos = GetMousePosition();

        m_grid.handleInput(static_cast<int>(mouse_pos.x), static_cast<int>(mouse_pos.y));
    }

    if (m_running && m_pathfinder) {
        if (!m_pathfinder->step()) {
            m_running = false;
        }
    }
}

void Application::render() {
    BeginDrawing();

    ClearBackground(DARKGRAY);
    m_grid.draw();
    drawGUI();

    EndDrawing();
}

void Application::drawGUI() {
    DrawRectangle(c_defaultWidth - c_menuWidth, 0, c_menuWidth, c_defaultHeight, {0, 60, 130, 255});

    if (GuiButton({850, 50, 200, 50}, m_running ? "Stop" : "Start")) {
        if (!m_running && m_grid.getStart() && m_grid.getEnd()) {
            switch (m_chosen_algorithm) {
            case Algorithm::BFS:
                m_pathfinder = std::make_unique<BfsPathfinder>(m_grid);
                break;
            case Algorithm::DFS:
                m_pathfinder = std::make_unique<DfsPathfinder>(m_grid);
                break;
            case Algorithm::Dijkstra:
                m_pathfinder = std::make_unique<DijkstraPathfinder>(m_grid);
                break;
            case Algorithm::Astar:
                m_pathfinder = std::make_unique<AStarPathfinder>(m_grid);
                break;
            default:
                std::unreachable();
            }
            m_pathfinder->initialize();
            m_running = true;
        } else {
            m_running = false;
        }
    }

    int selection = static_cast<int>(m_chosen_algorithm);

    if (GuiDropdownBox({850, 150, 200, 50}, "BFS;DFS;Dijkstra;A*", &selection, m_dropdown_active)) {
        m_dropdown_active = !m_dropdown_active;
        m_chosen_algorithm = static_cast<Algorithm>(selection);
    }

    if (GuiButton({850, 450, 200, 50}, "Clear walls") && !m_running) {
        m_grid.reset();
        m_grid.clearWalls();
    }
}
