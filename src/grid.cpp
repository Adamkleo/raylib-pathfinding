#include "grid.h"

Grid::Grid(int width, int height) : width(width), height(height) {
    grid.resize(height, std::vector<Node>(width));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[y][x] = Node(x, y, false);
        }
    }
}

void Grid::draw() {
    // Vertical grid lines
    for (int i = 0; i <= width; i++) {
        DrawLineV((Vector2){(float)GRID_CELL_SIZE * i, 0},
                  (Vector2){(float)GRID_CELL_SIZE * i, (float)SCREEN_HEIGHT},
                  LIGHTGRAY);
    }

    // Horizontal grid lines
    for (int i = 0; i <= height; i++) {
        DrawLineV((Vector2){0, (float)GRID_CELL_SIZE * i},
                  (Vector2){(float)SCREEN_WIDTH, (float)GRID_CELL_SIZE * i},
                  LIGHTGRAY);
    }

    // Draw obstacles
    for (const auto &row : grid) {
        for (const auto &node : row) {
            if (node.isObstacle) {
                DrawRectangle(node.x * GRID_CELL_SIZE, node.y * GRID_CELL_SIZE,
                              GRID_CELL_SIZE, GRID_CELL_SIZE, BLACK);
            }
        }
    }
}

void Grid::addObstacles(const std::vector<Vector2>& obstacles) {
    for (const auto& obs : obstacles) {
        int ox = obs.x / GRID_CELL_SIZE;
        int oy = obs.y / GRID_CELL_SIZE;

        if (ox >= 0 && ox < width && oy >= 0 && oy < height) {
            grid[oy][ox].isObstacle = true;
        }
    }
}

