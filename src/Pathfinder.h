#pragma once

#include "Grid.h"

class Pathfinder {
public:
    explicit Pathfinder(Grid& grid)
        : m_grid(grid) {}
    virtual ~Pathfinder() = default;

    virtual void initialize() = 0;
    virtual bool step() = 0;

protected:
    void reconstructPath(Node* end) {
        Node* curr = end;

        while (curr && curr->parent) {
            if (curr->state != NodeState::End && curr->state != NodeState::Start) {
                curr->state = NodeState::Path;
            }
            curr = curr->parent;
        }
    }

    Grid& m_grid;
    bool m_finished = false;
};
