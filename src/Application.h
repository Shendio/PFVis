#pragma once

#include "Grid.h"

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
};
