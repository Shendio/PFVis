#pragma once
#include "Pathfinder.h"

#include <queue>

class BfsPathfinder final : public Pathfinder {
public:
    using Pathfinder::Pathfinder;
    void initialize() override;

    bool step() override;

private:
    std::queue<Node*> m_queue;
};
