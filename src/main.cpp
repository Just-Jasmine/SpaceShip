#include "raylib.h"
#include "raymath.h"

typedef struct {
    Vector2 position;
    Color RAYWHITE;
    float radius;
} Star;

Vector2 getInput() {
    Vector2 input = Vector2{0.0, 0.0};
    if (IsKeyDown(KEY_W)) input.y = -1;
    if (IsKeyDown(KEY_A)) input.x = -1;
    if (IsKeyDown(KEY_S)) input.y = 1;
    if (IsKeyDown(KEY_D)) input.x = 1;
    return input;
}

int main(void) {
    const int numStars = 100;
    float acceleration = .05;
    float maxSpeed = 6;
    float screenWidth = 800;
    float screenHeight = 450;
    Vector2 ballPosition = Vector2{400, 225};
    Vector2 ballVelocity = Vector2{0, 0};
    Star stars[numStars];

    InitWindow(screenWidth, screenHeight, "SpaceShip");

    SetTargetFPS(60);



    for (int i = 0; i < numStars; i++) {
        stars[i].position.x = GetRandomValue(0, screenWidth);
        stars[i].position.y = GetRandomValue(0, screenHeight);
        stars[i].radius = GetRandomValue(1, 3); 
    }


    while (!WindowShouldClose()){
        Vector2 targetVelocity = Vector2Scale(Vector2Normalize(getInput()), maxSpeed);
        ballVelocity = Vector2Add(ballVelocity, Vector2Scale(Vector2Normalize(targetVelocity), acceleration));
        ballVelocity = Vector2Clamp(ballVelocity, Vector2{-maxSpeed, -maxSpeed}, Vector2{maxSpeed, maxSpeed});

        for (int i = 0; i < numStars; i++) {
            DrawCircleV(stars[i].position, stars[i].radius, stars[i].Color);
        }

        ballPosition = Vector2Add(ballPosition, ballVelocity);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircleV(ballPosition, 60, RED);
        EndDrawing();
    }
    CloseWindow();

    return 0;

}