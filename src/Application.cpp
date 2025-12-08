#include "Application.h"

#include "Constants.h"

#include "raylib.h"

Application::Application() {
    InitWindow(c_defaultWidth, c_defaultHeight, c_defaultTitle.data());
}

Application::~Application() {
    CloseWindow();
}

void Application::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(DARKGRAY);
        m_grid.draw();
        drawGUI();

        EndDrawing();
    }
}

void Application::drawGUI() {
    DrawRectangle(c_defaultWidth - c_menuWidth, 0, c_menuWidth, c_defaultHeight, {0, 60, 130, 255});
}
