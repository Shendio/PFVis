#include "Grid.h"
#include "Constants.h"
#include "Node.h"

#include <algorithm>
#include <random>
#include <stack>

#include "raylib.h"

Grid::Grid() {
    m_nodes.resize(c_grid_size * c_grid_size);

    for (size_t i = 0; i < c_grid_size * c_grid_size; ++i) {
        int x = i % c_grid_size;
        int y = i / c_grid_size;
        m_nodes[i].x = x;
        m_nodes[i].y = y;
    }
}

void Grid::reset() {
    for (auto& node : m_nodes) {
        node.reset();
        if (&node == m_start_node) {
            node.state = NodeState::Start;
        }
        if (&node == m_end_node) {
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

void Grid::generateMaze() {
    for (auto& node : m_nodes) {
        node.state = NodeState::Wall;
        node.reset();
    }

    std::stack<Node*> maze_stack;

    std::random_device rd;
    std::mt19937 gen(rd());

    Node* initial = nullptr;

    if (m_start_node) {
        initial = m_start_node;
    } else {
        initial = getNode(1, 1);
    }

    initial->state = NodeState::Empty;
    maze_stack.push(initial);

    while (!maze_stack.empty()) {
        Node* curr = maze_stack.top();
        maze_stack.pop();

        auto neighbors = getNeighborsMaze(curr);

        if (!neighbors.empty()) {
            maze_stack.push(curr);
            std::shuffle(neighbors.begin(), neighbors.end(), gen);
            Node* next = neighbors[0];

            next->state = NodeState::Empty;

            int wall_x = curr->x + (next->x - curr->x) / 2;
            int wall_y = curr->y + (next->y - curr->y) / 2;
            getNode(wall_x, wall_y)->state = NodeState::Empty;

            maze_stack.push(next);
        }
    }

    if (m_start_node) {
        m_start_node->state = NodeState::Start;
    }

    if (m_end_node) {
        m_end_node->state = NodeState::End;
    }
}

const bool Grid::isValidIndex(int x, int y) const {
    return (x < c_grid_size && y < c_grid_size && x >= 0 && y >= 0);
}

const int Grid::TwoDtoOneD(int x, int y) const {
    if (isValidIndex(x, y)) {
        return c_grid_size * y + x;
    }
    return -1;
}

void Grid::setStart(int x, int y) {
    if (m_start_node) {
        m_start_node->state = NodeState::Empty;
    }

    if (int nodeIndex = TwoDtoOneD(x, y); nodeIndex != -1) {
        m_start_node = &m_nodes[nodeIndex];
        m_start_node->state = NodeState::Start;
    }
}

void Grid::setEnd(int x, int y) {
    if (m_end_node) {
        m_end_node->state = NodeState::Empty;
    }

    if (int nodeIndex = TwoDtoOneD(x, y); nodeIndex != -1) {
        m_end_node = &m_nodes[nodeIndex];
        m_end_node->state = NodeState::End;
    }
}

void Grid::handleInput(int x, int y) {
    // Convert screen cords to grid coords.
    x /= c_nodes_size;
    y /= c_nodes_size;

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

std::vector<Node*> Grid::getNeighborsMaze(Node* n) {
    std::vector<Node*> outVec;
    int dx[] = {0, 0, 2, -2};
    int dy[] = {2, -2, 0, 0};

    for (size_t i = 0; i < 4; ++i) {
        Node* neighbor = getNode(n->x + dx[i], n->y + dy[i]);
        if (neighbor && neighbor->state == NodeState::Wall) {
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

        int x = (i % c_grid_size) * c_nodes_size;
        int y = (i / c_grid_size) * c_nodes_size;

        DrawRectangle(x, y, c_nodes_size, c_nodes_size, nodeColor);
        DrawRectangleLines(x, y, c_nodes_size, c_nodes_size, c_grid_lines_color);
    }
}
