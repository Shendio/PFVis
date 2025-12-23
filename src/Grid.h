#pragma once
#include "Node.h"

#include <vector>

class Grid {
public:
    Grid();

    void reset();
    void clearWalls();

    void setStart(int x, int y);
    void setEnd(int x, int y);
    Node* getStart() const { return m_startNode; }
    Node* getEnd() const { return m_endNode; }
    void handleInput(int x, int y);

    Node* getNode(int x, int y);
    std::vector<Node*> getNeighbors(Node* n);

    void paint(int x, int y, NodeState state);

    void draw();

private:
    const bool isValidIndex(int x, int y) const;
    const int TwoDtoOneD(int x, int y) const;

    std::vector<Node> m_nodes;
    Node* m_startNode = nullptr;
    Node* m_endNode = nullptr;
};
