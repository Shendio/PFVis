#pragma once

#include "Pathfinder.h"

#include <cmath>
#include <queue>
#include <vector>

class HeuristicPathfinder : public Pathfinder {
public:
    HeuristicPathfinder(Grid& grid, bool useHeuristic)
        : Pathfinder(grid)
        , m_useHeuristic(useHeuristic) {};

    // Manhattan Distance
    float calculateHeuristic(Node* a, Node* b) {
        return static_cast<float>(std::abs(a->x - b->x) + std::abs(a->y - b->y));
    }

    void initialize() override;
    bool step() override;

protected:
    struct CompareNode {
        bool operator()(Node* a, Node* b) {
            return a->fCost() > b->fCost();
        }
    };
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> m_open_set{};
    bool m_useHeuristic;
};

class DijkstraPathfinder final : public HeuristicPathfinder {
public:
    DijkstraPathfinder(Grid& grid)
        : HeuristicPathfinder(grid, false) {}
};

class AStarPathfinder final : public HeuristicPathfinder {
public:
    AStarPathfinder(Grid& grid)
        : HeuristicPathfinder(grid, true) {}
};

class GreedyBfsPathfinder final : public HeuristicPathfinder {
public:
    GreedyBfsPathfinder(Grid& grid)
        : HeuristicPathfinder(grid, true) {}

    bool step() override;
};
