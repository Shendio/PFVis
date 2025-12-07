#include <raylib.h>

int main() {
    InitWindow(1280, 720, "Pathfinding Visualizer");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
}
