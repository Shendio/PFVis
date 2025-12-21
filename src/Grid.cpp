#include "Grid.h"
#include "Constants.h"
#include "Node.h"

#include <raylib.h>

Grid::Grid() {
    m_nodes.resize(c_gridSize * c_gridSize);

    for (size_t i = 0; i < c_gridSize * c_gridSize; ++i) {
        int x = i % c_gridSize;
        int y = i / c_gridSize;
        m_nodes[i].x = x;
        m_nodes[i].y = y;
    }
}

const bool Grid::isValidIndex(int x, int y) const {
    return (x < c_gridSize && y < c_gridSize && x >= 0 && y >= 0);
}

const int Grid::TwoDtoOneD(int x, int y) const {
    if (isValidIndex(x, y)) {
        return c_gridSize * y + x;
    }
    return -1;
}

void Grid::setStart(int x, int y) {
    if (m_startNode) {
        m_startNode->state = NodeState::Empty;
    }

    // Convert screen coords to grid coords
    x = ScreenToGrid(x);
    y = ScreenToGrid(y);

    if (int nodeIndex = TwoDtoOneD(x, y); nodeIndex != -1) {
        m_startNode = &m_nodes[nodeIndex];
        m_startNode->state = NodeState::Start;
    }
}

void Grid::setEnd(int x, int y) {
    if (m_endNode) {
        m_endNode->state = NodeState::Empty;
    }

    // Convert screen coords to grid coords
    x = ScreenToGrid(x);
    y = ScreenToGrid(y);

    if (int nodeIndex = TwoDtoOneD(x, y); nodeIndex != -1) {
        m_endNode = &m_nodes[nodeIndex];
        m_endNode->state = NodeState::End;
    }
}

void Grid::paint(int x, int y, NodeState state) {
    x = ScreenToGrid(x);
    y = ScreenToGrid(y);

    if (int nodeIndex = TwoDtoOneD(x, y); nodeIndex != -1) {
        m_nodes[nodeIndex].state = state;
    }
}

void Grid::draw() {
    for (size_t i = 0; i < m_nodes.size(); ++i) {
        Color nodeColor;
        switch (m_nodes[i].state) {
        case NodeState::Empty:
            nodeColor = RAYWHITE;
            break;
        case NodeState::Wall:
            nodeColor = DARKGRAY;
            break;
        case NodeState::Start:
            nodeColor = GREEN;
            break;
        case NodeState::End:
            nodeColor = RED;
            break;
        case NodeState::Visited:
            nodeColor = {173, 216, 230, 255};
            break;
        case NodeState::Queued:
            nodeColor = {230, 230, 250, 255};
            break;
        case NodeState::Path:
            nodeColor = GOLD;
            break;
        }

        int x = (i % c_gridSize) * c_nodesSize;
        int y = (i / c_gridSize) * c_nodesSize;

        DrawRectangle(x, y, c_nodesSize, c_nodesSize, nodeColor);
        DrawRectangleLines(x, y, c_nodesSize, c_nodesSize, BLACK);
    }
}
