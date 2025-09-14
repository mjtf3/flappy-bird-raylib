#include <MainMenuState.hpp>
#include <iostream>
extern "C" {
    #include <raylib.h>
}

MainMenuState::MainMenuState()
{
}

void MainMenuState::init()
{
    std::cout << "You are in the Main Menu State" << std::endl;
}

void MainMenuState::handleInput()
{
    std::cout << "Enter a key: ";
    this->entered_key = std::cin.get();
}

void MainMenuState::update(float deltaTime)
{
    this->handleInput();
}

void MainMenuState::render()
{
    BeginDrawing();
    DrawText("Bienvenido a Flappy Bird DCA", 50, 50, 20, LIGHTGRAY);
    EndDrawing();
}