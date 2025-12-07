#include "Grid.h"

static constexpr int s_gridSize = 40;

Grid::Grid() {
    m_nodes.resize(s_gridSize * s_gridSize);

    for (size_t i = 0; i < s_gridSize * s_gridSize; ++i) {
        int x = i % s_gridSize;
        int y = i / s_gridSize;
        m_nodes[i].x = x;
        m_nodes[i].y = y;
    }
}

const bool Grid::isValidIndex(int x, int y) const {
    return (x < s_gridSize && y < s_gridSize && x >= 0 && y >= 0);
}

const int Grid::TwoDtoOneD(int x, int y) const {
    if (isValidIndex(x, y)) {
        return s_gridSize * y + x;
    }
    return -1;
}

void Grid::setStart(int x, int y) {
    if (m_startNode) {
        m_startNode->state = NodeState::Empty;
    }

    if (isValidIndex(x, y)) {
        m_startNode = &m_nodes[TwoDtoOneD(x, y)];
        m_startNode->state = NodeState::Start;
    }
}

void Grid::setEnd(int x, int y) {
    if (m_endNode) {
        m_endNode->state = NodeState::Empty;
    }

    if (isValidIndex(x, y)) {
        m_endNode = &m_nodes[TwoDtoOneD(x, y)];
        m_endNode->state = NodeState::End;
    }
}
