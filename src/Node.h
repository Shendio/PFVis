#pragma once

#include <cstdint>
#include <limits>

enum class NodeState : uint8_t { Empty = 0, Wall, Start, End, Visited, Path, Queued };

struct Node {
    int x, y;
    NodeState state = NodeState::Empty;

    float gCost = std::numeric_limits<float>::infinity();
    float hCost = 0.f;

    inline float fCost() const {
        return gCost + hCost;
    }

    Node* parent = nullptr;
};
