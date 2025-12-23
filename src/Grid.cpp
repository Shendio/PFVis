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

void Grid::reset() {
    for (auto& node : m_nodes) {
        node.reset();
        if (&node == m_startNode) {
            node.state = NodeState::Start;
        }
        if (&node == m_endNode) {
            node.state = NodeState::End;
        }
    }
}

void Grid::clearWalls() {
    for (auto& node : m_nodes) {
        if (node.state == NodeState::Wall) {
            node.state = NodeState::Empty;
        }
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

    if (int nodeIndex = TwoDtoOneD(x, y); nodeIndex != -1) {
        m_startNode = &m_nodes[nodeIndex];
        m_startNode->state = NodeState::Start;
    }
}

void Grid::setEnd(int x, int y) {
    if (m_endNode) {
        m_endNode->state = NodeState::Empty;
    }

    if (int nodeIndex = TwoDtoOneD(x, y); nodeIndex != -1) {
        m_endNode = &m_nodes[nodeIndex];
        m_endNode->state = NodeState::End;
    }
}

void Grid::handleInput(int x, int y) {
    // Convert screen cords to grid coords.
    x /= c_nodesSize;
    y /= c_nodesSize;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        paint(x, y, NodeState::Wall);
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        paint(x, y, NodeState::Empty);
    }

    if (IsKeyPressed(KEY_S)) {
        setStart(x, y);
    }

    if (IsKeyPressed(KEY_T)) {
        setEnd(x, y);
    }
}

Node* Grid::getNode(int x, int y) {
    if (int nodeIndex = TwoDtoOneD(x, y); nodeIndex != -1) {
        return &m_nodes[nodeIndex];
    }
    return nullptr;
}

std::vector<Node*> Grid::getNeighbors(Node* n) {
    std::vector<Node*> outVec;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (size_t i = 0; i < 4; ++i) {
        Node* neighbor = getNode(n->x + dx[i], n->y + dy[i]);
        if (neighbor && neighbor->state != NodeState::Wall) {
            outVec.push_back(neighbor);
        }
    }
    return outVec;
}

void Grid::paint(int x, int y, NodeState state) {
    if (int nodeIndex = TwoDtoOneD(x, y); nodeIndex != -1) {
        m_nodes[nodeIndex].state = state;
    }
}

void Grid::draw() {
    for (size_t i = 0; i < m_nodes.size(); ++i) {
        Color nodeColor;
        switch (m_nodes[i].state) {
        case NodeState::Empty:
            nodeColor = c_node_empty_color;
            break;
        case NodeState::Wall:
            nodeColor = c_node_wall_color;
            break;
        case NodeState::Start:
            nodeColor = c_node_start_color;
            break;
        case NodeState::End:
            nodeColor = c_node_end_color;
            break;
        case NodeState::Visited:
            nodeColor = c_node_visited_color;
            break;
        case NodeState::Queued:
            nodeColor = c_node_queued_color;
            break;
        case NodeState::Path:
            nodeColor = c_node_path_color;
            break;
        }

        int x = (i % c_gridSize) * c_nodesSize;
        int y = (i / c_gridSize) * c_nodesSize;

        DrawRectangle(x, y, c_nodesSize, c_nodesSize, nodeColor);
        DrawRectangleLines(x, y, c_nodesSize, c_nodesSize, c_grid_lines_color);
    }
}
