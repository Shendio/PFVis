#pragma once
#include "Node.h"

#include <vector>

class Grid {
public:
    Grid();

    const bool isValidIndex(int x, int y) const;
    const int TwoDtoOneD(int x, int y) const;

    void setStart(int x, int y);
    void setEnd(int x, int y);

private:
    std::vector<Node> m_nodes;
    Node* m_startNode = nullptr;
    Node* m_endNode = nullptr;
};
