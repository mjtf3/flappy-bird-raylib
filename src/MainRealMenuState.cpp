#include <MainRealMenuState.hpp>
#include <MainMenuState.hpp>
#include <StateMachine.hpp>

MainRealMenuState::MainRealMenuState()
{
}

void MainRealMenuState::init()
{
    this->background = LoadTexture("assets/message.png");
}

void MainRealMenuState::handleInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        this->restart_game = true;
    }
}

void MainRealMenuState::update(float deltaTime)
{
    this->handleInput();
    if (restart_game)
    {
        this->state_machine->add_state(std::make_unique<MainMenuState>(), true);
        //this->state_machine->handle_state_changes(deltaTime);
    }
    
}

void MainRealMenuState::render()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(this->background, GetScreenWidth() / 2 - this->background.width / 2, GetScreenHeight() / 2 - this->background.height / 2, WHITE);
    //DrawText("Te has cagado encima colega", 50, 50, 20, LIGHTGRAY);
    //DrawText("Pulsa ESPACIO para reiniciar", 50, 150, 20, LIGHTGRAY);
    EndDrawing();
}
