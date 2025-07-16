#pragma once

struct Bot {
    float startX;
    float startY;

    Bot(float x, float y) {
        startX = x;
        startY = y;
    };

    void draw() {
        float centeringFactor = (GRID_CELL_SIZE - PLAYER_SIZE) / 2;
        float innerX = startX + centeringFactor;
        float innerY = startY + centeringFactor;
        DrawRectangle(innerX, innerY, PLAYER_SIZE, PLAYER_SIZE, RED);
    };

    void setPosition(float x, float y) {
        startX = x;
        startY = y;
    };
};