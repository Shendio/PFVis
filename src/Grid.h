#pragma once
#include "Constants.h"
#include "Node.h"

#include <vector>

class Grid {
public:
    Grid();

    void setStart(int x, int y);
    void setEnd(int x, int y);
    void paint(int x, int y, NodeState state);

    void draw();

private:
    const bool isValidIndex(int x, int y) const;
    const int TwoDtoOneD(int x, int y) const;

    inline const int ScreenToGrid(int index) const {
        return index / c_nodesSize;
    }

    std::vector<Node> m_nodes;
    Node* m_startNode = nullptr;
    Node* m_endNode = nullptr;
};
