#include "DfsPathfinder.h"

void DfsPathfinder::initialize() {
    m_grid.reset();
    Node* start = m_grid.getStart();
    m_stack = std::stack<Node*>();
    m_stack.push(start);
    start->state = NodeState::Queued;
    m_finished = false;
}

bool DfsPathfinder::step() {
    if (m_stack.empty()) {
        m_finished = true;
        return false;
    }

    Node* curr = m_stack.top();
    m_stack.pop();

    if (curr == m_grid.getEnd()) {
        reconstructPath(curr);
        m_finished = true;
        return false;
    }

    if (curr->state != NodeState::Start) {
        curr->state = NodeState::Visited;
    }

    for (auto neighbor : m_grid.getNeighbors(curr)) {
        if (neighbor->state != NodeState::Visited && neighbor->state != NodeState::Queued && neighbor->state != NodeState::Start) {
            neighbor->parent = curr;
            neighbor->state = NodeState::Queued;
            m_stack.push(neighbor);
        }
    }
    m_operations++;
    return true;
}
