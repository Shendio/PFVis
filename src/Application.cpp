#include "Application.h"

#include <string>

#include "raylib.h"

static constexpr int s_defaultWidth = 1000;
static constexpr int s_defaultHeight = 800;
static const std::string s_defaultTitle = "Pathfinding Visualizer";

Application::Application() {
    InitWindow(s_defaultWidth, s_defaultHeight, s_defaultTitle.c_str());
}

Application::~Application() {
    CloseWindow();
}

void Application::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }
}
