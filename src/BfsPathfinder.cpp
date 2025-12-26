#include "BfsPathfinder.h"

void BfsPathfinder::initialize() {
    m_grid.reset();
    Node* start = m_grid.getStart();
    m_queue.push(start);
    start->state = NodeState::Queued;
    m_time_elapsed = std::chrono::nanoseconds{0};
    m_last_time = std::chrono::steady_clock::now();
    m_finished = false;
}

bool BfsPathfinder::step() {
    auto now = std::chrono::steady_clock::now();
    m_time_elapsed += now - m_last_time;
    m_last_time = now;

    if (m_queue.empty()) {
        m_finished = true;
        return false;
    }

    Node* curr = m_queue.front();
    m_queue.pop();

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
            m_queue.push(neighbor);
        }
    }
    return true;
}
