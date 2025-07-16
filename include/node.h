#pragma once
#include <vector>


struct Node {
    int x;
    int y;
    bool isObstacle;

    Node() : x(0), y(0), isObstacle(false) {}

    Node(int x, int y, bool isObstacle) : x(x), y(y), isObstacle(isObstacle) {}

    bool operator==(const Node &other) const {
        return (x == other.x && y == other.y);
    }

    std::vector<Node>
    getAdjacentNodes(const std::vector<std::vector<Node>> &grid, int gridWidth,
                     int gridHeight) const {
        std::vector<Node> neighbors;
        std::pair<int, int> directions[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (auto &dir : directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight) {
                if (!grid[ny][nx].isObstacle) {
                    neighbors.push_back(grid[ny][nx]);
                }
            }
        }
        return neighbors;
    }
};

namespace std {
template <> struct hash<Node> {
    size_t operator()(const Node &n) const {
        return hash<int>()(n.x) ^ (hash<int>()(n.y) << 1);
    }
};
} // namespace std
