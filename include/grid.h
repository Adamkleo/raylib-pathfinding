#pragma once
#include "node.h"
#include "constants.h"
#include "raylib.h"
#include <vector>

std::vector<std::vector<Node>> createGrid();

void drawGrid(const std::vector<Vector2> &obstacles);
