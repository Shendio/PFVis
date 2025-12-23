#pragma once
#include "Pathfinder.h"

#include <stack>

class DfsPathfinder final : public Pathfinder {
public:
    using Pathfinder::Pathfinder;
    void initialize() override;

    bool step() override;

private:
    std::stack<Node*> m_stack;
};
