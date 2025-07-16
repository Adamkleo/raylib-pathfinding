#pragma once

#include "constants.h"
#include "raylib.h"
#include "node.h"
#include <vector>

std::vector<Vector2> generateObstacles(int n);

void addObstaclesToGrid(std::vector<std::vector<Node>> &grid, const std::vector<Vector2> &obstacles);