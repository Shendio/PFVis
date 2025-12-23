#include "HeuristicPathfinder.h"

void HeuristicPathfinder::initialize() {
    m_grid.reset();
    m_openSet = std::priority_queue<Node*, std::vector<Node*>, CompareNode>();
    Node* start = m_grid.getStart();
    start->gCost = 0;
    start->hCost = m_useHeuristic ? calculateHeuristic(start, m_grid.getEnd()) : 0;
    m_openSet.push(start);
    start->state = NodeState::Queued;
    m_finished = false;
}

bool HeuristicPathfinder::step() {
    if (m_openSet.empty()) {
        m_finished = true;
        return false;
    }

    Node* curr = m_openSet.top();
    m_openSet.pop();

    if (curr == m_grid.getEnd()) {
        reconstructPath(curr);
        m_finished = true;
        return false;
    }

    if (curr->state != NodeState::Start) {
        curr->state = NodeState::Visited;
    }

    for (auto neighbor : m_grid.getNeighbors(curr)) {
        float newCost = curr->gCost + 1;
        if (newCost < neighbor->gCost) {
            neighbor->parent = curr;
            neighbor->gCost = newCost;
            neighbor->hCost = m_useHeuristic ? calculateHeuristic(neighbor, m_grid.getEnd()) : 0;

            if (neighbor->state != NodeState::Queued && neighbor->state != NodeState::Visited && neighbor->state != NodeState::End) {
                neighbor->state = NodeState::Queued;
            }
            m_openSet.push(neighbor);
        }
    }
    return true;
}
