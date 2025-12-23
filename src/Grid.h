#pragma once
#include "Node.h"

#include <vector>

class Grid {
public:
    Grid();

    void reset();
    void clearWalls();
    void generateMaze();

    void setStart(int x, int y);
    void setEnd(int x, int y);
    Node* getStart() const { return m_start_node; }
    Node* getEnd() const { return m_end_node; }
    void handleInput(int x, int y);

    Node* getNode(int x, int y);
    std::vector<Node*> getNeighbors(Node* n);
    std::vector<Node*> getNeighborsMaze(Node* n);

    void paint(int x, int y, NodeState state);

    void draw();

private:
    const bool isValidIndex(int x, int y) const;
    const int TwoDtoOneD(int x, int y) const;

    std::vector<Node> m_nodes;
    Node* m_start_node = nullptr;
    Node* m_end_node = nullptr;
};
