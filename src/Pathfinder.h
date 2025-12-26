#pragma once

#include "Grid.h"

#include <chrono>

class Pathfinder {
public:
    explicit Pathfinder(Grid& grid)
        : m_grid(grid) {}
    virtual ~Pathfinder() = default;

    virtual void initialize() = 0;
    virtual bool step() = 0;

    const float getTimeElapsed() const {
        return std::chrono::duration<float, std::milli>(m_time_elapsed).count() / 1000;
    }

protected:
    void reconstructPath(Node* end) {
        Node* curr = end;

        while (curr && curr->parent) {
            if (curr->state != NodeState::End && curr->state != NodeState::Start) {
                curr->state = NodeState::Path;
            }
            curr = curr->parent;
        }
        curr->state = NodeState::Start;
    }

    Grid& m_grid;
    bool m_finished = false;

    std::chrono::nanoseconds m_time_elapsed;
    std::chrono::steady_clock::time_point m_last_time;
};
