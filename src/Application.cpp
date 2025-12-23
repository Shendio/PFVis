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
    setupStyling();
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

void Application::setupStyling() {
    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, ColorToInt(c_menu_color));
    GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, ColorToInt(c_node_visited_color));
    GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, ColorToInt(c_node_start_color));

    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(c_node_wall_color));
    GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(c_base_color));
    GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, ColorToInt(c_base_color));

    GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt(c_base_color));
    GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, ColorToInt(c_node_queued_color));
    GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, ColorToInt(c_node_start_color));
    GuiSetStyle(DEFAULT, BORDER_WIDTH, 1);

    GuiSetStyle(DROPDOWNBOX, BASE_COLOR_NORMAL, ColorToInt(c_menu_color));
    GuiSetStyle(DROPDOWNBOX, BASE_COLOR_PRESSED, ColorToInt(c_menu_color));
    GuiSetStyle(DROPDOWNBOX, BASE_COLOR_FOCUSED, ColorToInt(c_menu_color));

    GuiSetStyle(DROPDOWNBOX, TEXT_COLOR_NORMAL, ColorToInt(c_node_wall_color));
    GuiSetStyle(DROPDOWNBOX, TEXT_COLOR_FOCUSED, ColorToInt(c_node_queued_color));
    GuiSetStyle(DROPDOWNBOX, TEXT_COLOR_PRESSED, ColorToInt(c_node_path_color));

    GuiSetStyle(DROPDOWNBOX, ARROW_PADDING, 30);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
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

    m_grid.draw();
    drawGUI();

    EndDrawing();
}

void Application::drawGUI() {
    DrawRectangle(c_defaultWidth - c_menuWidth, 0, c_menuWidth, c_defaultHeight, c_menu_color);

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

    if (GuiButton({850, 450, 200, 50}, "Reset") && !m_running) {
        m_grid.reset();
        m_grid.clearWalls();
    }

    if (m_pathfinder) {
        GuiLabel({865, 550, 250, 20}, TextFormat("Ilosc operacji: %d", m_pathfinder->getOperationCount()));
    }

    GuiLabel({850, 750, 250, 20}, "Autor: Szymon Szedziol");
    GuiLabel({885, 775, 250, 20}, "II EF-DI 179624");
}
