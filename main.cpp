#include "node.h"
#include "raylib.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#define PLAYER_SIZE 20
#define GRID_CELL_SIZE 25
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define NUMBER_OF_CELLS_X (SCREEN_WIDTH / GRID_CELL_SIZE )
#define NUMBER_OF_CELLS_Y (SCREEN_HEIGHT / GRID_CELL_SIZE )

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

void drawGrid() {
    for (int i = 0; i <= NUMBER_OF_CELLS_X; i++)
        DrawLineV((Vector2){(float)GRID_CELL_SIZE * i, 0},
                  (Vector2){(float)GRID_CELL_SIZE * i, (float)SCREEN_HEIGHT},
                  LIGHTGRAY);

    for (int i = 0; i <= NUMBER_OF_CELLS_Y; i++)
        DrawLineV((Vector2){0, (float)GRID_CELL_SIZE * i},
                  (Vector2){(float)SCREEN_WIDTH, (float)GRID_CELL_SIZE * i},
                  LIGHTGRAY);
}

std::vector<std::vector<Node>> createGrid () {
    // Create grid of Nodes with 'number of cells y' rows and 'number of cells x' columns
    std::vector<std::vector<Node>> grid(NUMBER_OF_CELLS_Y, std::vector<Node>(NUMBER_OF_CELLS_X));

    // populate grid with empty nodes
    for (int y = 0; y < NUMBER_OF_CELLS_Y; y++) {
        for (int x = 0; x < NUMBER_OF_CELLS_X; x++) {
            grid[y][x] = Node(x, y, false);
        }
    }

    return grid;
}

int main(void) {

    SetRandomSeed(1409);

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib 2D camera single screen");

    std::vector<Node> movementPath;
    std::vector<Node> passed;

    int currentPathStep = 0;

    // PLAYER
    float innerX = 50 + (GRID_CELL_SIZE - PLAYER_SIZE) / 2;
    float innerY = 50 + (GRID_CELL_SIZE - PLAYER_SIZE) / 2;
    Rectangle bot = {innerX, innerY, PLAYER_SIZE, PLAYER_SIZE};
    
    Rectangle goal;
    bool goalSet = false;

    int gridWidth = SCREEN_WIDTH / GRID_CELL_SIZE;
    int gridHeight = SCREEN_HEIGHT / GRID_CELL_SIZE;

    std::vector<std::vector<Node>> grid = createGrid();

    SetTargetFPS(60);

    std::vector<Vector2> obstacles = generateObstacles(240);
    std::vector<Vector2> filteredObstacles;

    for (const auto &obs : obstacles) {
        int ox = obs.x / GRID_CELL_SIZE;
        int oy = obs.y / GRID_CELL_SIZE;
        int botx = bot.x / GRID_CELL_SIZE;
        int boty = bot.y / GRID_CELL_SIZE;

        if (ox == botx && oy == boty)
            continue;

        if (ox >= 0 && ox < gridWidth && oy >= 0 && oy < gridHeight) {
            grid[oy][ox].isObstacle = true;
            filteredObstacles.push_back(obs);
        }
    }

    obstacles = filteredObstacles;

    int frameCounter = 0;
    const int stepDelay = 10;

    while (!WindowShouldClose()) {

        Vector2 mouse = GetMousePosition();

        Rectangle nextPos = bot;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw grid

        drawGrid();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int coordX = ((int)mouse.x / GRID_CELL_SIZE) * GRID_CELL_SIZE;
            int coordY = ((int)mouse.y / GRID_CELL_SIZE) * GRID_CELL_SIZE;

            bool isOnObstacle = false;
            for (const auto &obs : obstacles) {
                if (obs.x == coordX && obs.y == coordY) {
                    isOnObstacle = true;
                    break;
                }
            }

            if (!isOnObstacle) {
                goal = {(float)coordX, (float)coordY, GRID_CELL_SIZE,
                        GRID_CELL_SIZE};
            }

            Node root((int)bot.x / GRID_CELL_SIZE, (int)bot.y / GRID_CELL_SIZE,
                      false);
            Node target(coordX / GRID_CELL_SIZE, coordY / GRID_CELL_SIZE,
                        false);

            movementPath = BFS(grid, root, target, gridWidth, gridHeight);

            currentPathStep = 0;
            passed.clear();
        }

        if (currentPathStep < movementPath.size()) {
            frameCounter++;
            if (frameCounter >= stepDelay) {
                Node step = movementPath[currentPathStep];
                passed.push_back(step);
                bot.x = step.x * GRID_CELL_SIZE +
                        (GRID_CELL_SIZE - PLAYER_SIZE) / 2;
                bot.y = step.y * GRID_CELL_SIZE +
                        (GRID_CELL_SIZE - PLAYER_SIZE) / 2;
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

        DrawRectangleRec(bot, RED);

        DrawRectangleRec(goal, GREEN);

        for (int i = 0; i < obstacles.size(); ++i) {
            DrawRectangle(obstacles[i].x, obstacles[i].y, GRID_CELL_SIZE,
                          GRID_CELL_SIZE, BLACK);
        }

        DrawText(TextFormat("Mouse: %2d,%2d", (int)mouse.x / GRID_CELL_SIZE,
                            (int)mouse.y / GRID_CELL_SIZE),
                 10, 10, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
