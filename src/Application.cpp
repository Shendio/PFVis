#include "Application.h"
#include "Constants.h"

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <print>

Application::Application() {
    InitWindow(c_defaultWidth, c_defaultHeight, c_defaultTitle.data());
    SetTargetFPS(60);
}

Application::~Application() {
    CloseWindow();
}

void Application::run() {
    while (!WindowShouldClose()) {
        // Update
        if (1) {
            auto mouse_pos = GetMousePosition();

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                m_grid.paint(static_cast<int>(mouse_pos.x), static_cast<int>(mouse_pos.y), NodeState::Wall);
            }

            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                m_grid.paint(static_cast<int>(mouse_pos.x), static_cast<int>(mouse_pos.y), NodeState::Empty);
            }

            if (IsKeyPressed(KEY_S)) {
                m_grid.setStart(static_cast<int>(mouse_pos.x), static_cast<int>(mouse_pos.y));
                std::println("Set start at cords: {}x{}", mouse_pos.x, mouse_pos.y);
            }

            if (IsKeyPressed(KEY_T)) {
                m_grid.setEnd(static_cast<int>(mouse_pos.x), static_cast<int>(mouse_pos.y));
                std::println("Set end at cords: {}x{}", mouse_pos.x, mouse_pos.y);
            }
        }
        // Render
        BeginDrawing();

        ClearBackground(DARKGRAY);
        m_grid.draw();
        drawGUI();

        EndDrawing();
    }
}

void Application::drawGUI() {
    DrawRectangle(c_defaultWidth - c_menuWidth, 0, c_menuWidth, c_defaultHeight, {0, 60, 130, 255});

    if (GuiButton({850, 50, 200, 50}, "Start")) {
    }

    int selection = static_cast<int>(m_chosen_algorithm);

    if (GuiDropdownBox({850, 150, 200, 50}, "BFS;DFS;Dijkstra;A*", &selection, m_dropdown_active)) {
        m_dropdown_active = !m_dropdown_active;
        m_chosen_algorithm = static_cast<Algorithm>(selection);
    }
}
