#include "constants.h"
#include "grid.h"
#include "node.h"
#include "obstacle.h"
#include "raylib.h"
#include "bot.h"
#include "goal.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

std::vector<Node> BFS(std::vector<std::vector<Node>> &grid, Node root,
                      Node goal, int gridWidth, int gridHeight) {
    std::queue<Node> open;
    std::vector<Node> visited;
    std::vector<Node> path;
    std::unordered_map<Node, Node> cameFrom;

    open.push(root);
    visited.push_back(root);
    cameFrom[root] = root;

    while (!open.empty()) {
        Node current = open.front();
        open.pop();

        if (current == goal) {
            Node step = goal;
            while (!(step == root)) {
                path.push_back(step);
                step = cameFrom[step];
            }
            path.push_back(root);
            std::reverse(path.begin(), path.end());
            return path;
        }

        std::vector<Node> neighbors =
            current.getAdjacentNodes(grid, gridWidth, gridHeight);
        for (auto &neighbor : neighbors) {
            bool exists = std::find(visited.begin(), visited.end(), neighbor) !=
                          visited.end();
            if (exists) {
                continue;
            }
            visited.push_back(neighbor);
            cameFrom[neighbor] = current;
            open.push(neighbor);
        }
    }
    return {}; // no path found
}



int main(void) {

    SetRandomSeed(1409);
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib 2D camera single screen");

    std::vector<Node> movementPath;
    std::vector<Node> passed;

    int currentPathStep = 0;

    // Create player
    float startX = 100;
    float startY = 100;
    Bot player(startX, startY);

    // Create goal
    Goal goal;

    // Create grid
    std::vector<std::vector<Node>> grid = createGrid();

    // Generate obstacles
    const std::vector<Vector2> obstacles =
        generateObstacles(NUMBER_OF_OBSTACLES);

    // Add obstacles to grid
    addObstaclesToGrid(grid, obstacles);

    int frameCounter = 0;
    const int stepDelay = 10;

    while (!WindowShouldClose()) {

        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw grid
        drawGrid(obstacles);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            goal.set(mouse.x, mouse.y);
            goal.active = true;

            Node root((int)player.startX / GRID_CELL_SIZE,
                      (int)player.startY / GRID_CELL_SIZE, false);

            Node target((int)goal.x / GRID_CELL_SIZE,
                        (int)goal.y / GRID_CELL_SIZE, false);

            movementPath =
                BFS(grid, root, target, NUMBER_OF_CELLS_X, NUMBER_OF_CELLS_Y);

            currentPathStep = 0;
            passed.clear();
        }

        if (currentPathStep < movementPath.size()) {
            frameCounter++;
            if (frameCounter >= stepDelay) {
                Node step = movementPath[currentPathStep];
                passed.push_back(step);
                player.setPosition(step.x * GRID_CELL_SIZE,
                                   step.y * GRID_CELL_SIZE);
                currentPathStep++;
                frameCounter = 0;
            }
        }

        for (auto &cell : movementPath) {
            bool cellPassed =
                std::find(passed.begin(), passed.end(), cell) != passed.end();
            if (!cellPassed) {
                DrawRectangle(cell.x * GRID_CELL_SIZE + GRID_CELL_SIZE / 4,
                              cell.y * GRID_CELL_SIZE + GRID_CELL_SIZE / 4,
                              GRID_CELL_SIZE / 2, GRID_CELL_SIZE / 2, BLUE);
            }
        }

        if (goal.active)
            goal.draw();

        // Draw player
        player.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}