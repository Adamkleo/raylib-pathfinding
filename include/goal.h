#pragma once


struct Goal {
    float x;
    float y;
    bool active = false;

    Goal() {};

    void draw() {
        // Calculate cell coordinates
        int cellX = (int)(x / GRID_CELL_SIZE);
        int cellY = (int)(y / GRID_CELL_SIZE);

        // Calculate center of the cell to draw in
        int centerX = cellX * GRID_CELL_SIZE + GRID_CELL_SIZE / 2;
        int centerY = cellY * GRID_CELL_SIZE + GRID_CELL_SIZE / 2;

        DrawCircle(centerX, centerY, GOAL_SIZE, GREEN);
    }

    void set(float selectedX, float selectedY) {
        x = selectedX;
        y = selectedY;
    }
};