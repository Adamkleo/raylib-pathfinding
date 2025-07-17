#pragma once
#include "node.h"
#include "constants.h"
#include "raylib.h"
#include <vector>



struct Grid {
    int width, height;
    std::vector<std::vector<Node>> grid;

    Grid(int width, int height); // constructor

    void addObstacles(const std::vector<Vector2> &obstacles);

    void draw();
};
