#include "HeuristicPathfinder.h"

void HeuristicPathfinder::initialize() {
    m_grid.reset();
    Node* start = m_grid.getStart();
    start->gCost = 0;
    start->hCost = m_useHeuristic ? calculateHeuristic(start, m_grid.getEnd()) : 0;
    m_open_set.push(start);
    start->state = NodeState::Queued;
    m_time_elapsed = std::chrono::nanoseconds{0};
    m_last_time = std::chrono::steady_clock::now();
    m_finished = false;
}

bool HeuristicPathfinder::step() {
    auto now = std::chrono::steady_clock::now();
    m_time_elapsed += now - m_last_time;
    m_last_time = now;

    if (m_open_set.empty()) {
        m_finished = true;
        return false;
    }

    Node* curr = m_open_set.top();
    m_open_set.pop();

    if (curr->state == NodeState::Visited) {
        return true;
    }

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
            m_open_set.push(neighbor);
        }
    }
    return true;
}

bool GreedyBfsPathfinder::step() {
    auto now = std::chrono::steady_clock::now();
    m_time_elapsed += now - m_last_time;
    m_last_time = now;

    if (m_open_set.empty()) {
        m_finished = true;
        return false;
    }

    Node* curr = m_open_set.top();
    m_open_set.pop();

    if (curr->state == NodeState::Visited) {
        return true;
    }

    if (curr == m_grid.getEnd()) {
        reconstructPath(curr);
        m_finished = true;
        return false;
    }

    if (curr->state != NodeState::Start) {
        curr->state = NodeState::Visited;
    }

    for (auto neighbor : m_grid.getNeighbors(curr)) {
        if (neighbor->state != NodeState::Visited && neighbor->state != NodeState::Queued) {
            neighbor->parent = curr;
            neighbor->gCost = 0;
            neighbor->hCost = calculateHeuristic(neighbor, m_grid.getEnd());

            if (neighbor->state != NodeState::End) {
                neighbor->state = NodeState::Queued;
            }

            m_open_set.push(neighbor);
        }
    }
    return true;
}
