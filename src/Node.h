#pragma once

#include <cstdint>
#include <limits>

enum class NodeState : uint8_t { Empty = 0, Wall, Start, End, Visited, Path, Queued };

struct Node {
    int x, y;
    NodeState state = NodeState::Empty;

    Node* parent = nullptr;
    float gCost = std::numeric_limits<float>::infinity();
    float hCost = 0.f;

    inline float fCost() const {
        return gCost + hCost;
    }

    void reset() {
        parent = nullptr;
        gCost = std::numeric_limits<float>::infinity();
        hCost = 0.f;

        if (state == NodeState::Visited || state == NodeState::Path || state == NodeState::Queued) {
            state = NodeState::Empty;
        }
    }
};
