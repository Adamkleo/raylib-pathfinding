#include "obstacle.h"

std::vector<Vector2> generateObstacles(int n) {

    std::vector<Vector2> obstacles;

    for (int i = 0; i < n; i++) {
        // Get random cell numbers
        float randomCellX = (float)GetRandomValue(0, NUMBER_OF_CELLS_X);
        float randomCellY = (float)GetRandomValue(0, NUMBER_OF_CELLS_Y);

        // Convert cell numbers to grid coordinates
        float cellCoordinateX = randomCellX * GRID_CELL_SIZE;
        float cellCoordinateY = randomCellY * GRID_CELL_SIZE;

        Vector2 coords = {cellCoordinateX, cellCoordinateY};
        obstacles.push_back(coords);
    }

    return obstacles;
}
