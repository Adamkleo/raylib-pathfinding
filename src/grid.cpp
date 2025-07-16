#include "grid.h"

std::vector<std::vector<Node>> createGrid() {
    // Create grid of Nodes with 'number of cells y' rows and 'number of cells
    // x' columns
    std::vector<std::vector<Node>> grid(NUMBER_OF_CELLS_Y,
                                        std::vector<Node>(NUMBER_OF_CELLS_X));

    // populate grid with empty nodes
    for (int y = 0; y < NUMBER_OF_CELLS_Y; y++) {
        for (int x = 0; x < NUMBER_OF_CELLS_X; x++) {
            grid[y][x] = Node(x, y, false);
        }
    }

    return grid;
}

void drawGrid(const std::vector<Vector2> &obstacles) {
    // Draw vertical grid lines
    for (int i = 0; i <= NUMBER_OF_CELLS_X; i++)
        DrawLineV((Vector2){(float)GRID_CELL_SIZE * i, 0},
                  (Vector2){(float)GRID_CELL_SIZE * i, (float)SCREEN_HEIGHT},
                  LIGHTGRAY);

    // Draw horizontal grid lines
    for (int i = 0; i <= NUMBER_OF_CELLS_Y; i++)
        DrawLineV((Vector2){0, (float)GRID_CELL_SIZE * i},
                  (Vector2){(float)SCREEN_WIDTH, (float)GRID_CELL_SIZE * i},
                  LIGHTGRAY);

    for (int i = 0; i < obstacles.size(); ++i) {
        DrawRectangle(obstacles[i].x, obstacles[i].y, GRID_CELL_SIZE,
                      GRID_CELL_SIZE, BLACK);
    }
}