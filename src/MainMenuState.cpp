#include <MainMenuState.hpp>
#include <iostream>
extern "C" {
    #include <raylib.h>
}

float gravity = 981.0f;

MainMenuState::MainMenuState()
{
    this->player_bird = Bird{.x = 200, .y = 200, .vy = 0.0f};
}

void MainMenuState::init()
{
    std::cout << "You are in the Main Menu State" << std::endl;
}

void MainMenuState::handleInput()
{
    //std::cout << "Enter a key: ";
    //this->entered_key = std::cin.get();
    if (IsKeyPressed(KEY_SPACE))
    {
        player_bird.vy = -1000.0f;
    }
    
}

void MainMenuState::update(float deltaTime)
{
    this->handleInput();
    //player_bird.x += 1.0f * deltaTime;
    player_bird.vy += gravity * deltaTime;
    player_bird.y += player_bird.vy * deltaTime;
    player_bird.vy = 0;
}

void MainMenuState::render()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Bienvenido a Flappy Bird DCA", 50, 50, 20, LIGHTGRAY);
    DrawCircle(player_bird.x, player_bird.y, 17, RED);
    EndDrawing();
}