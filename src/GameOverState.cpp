#include <GameOverState.hpp>
#include <MainMenuState.hpp>
#include <StateMachine.hpp>

GameOverState::GameOverState(int score)
{
    this->score = score;
}

void GameOverState::init()
{
}

void GameOverState::handleInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        this->restart_game = true;
    }
}

void GameOverState::update(float deltaTime)
{
    this->handleInput();
    if (restart_game)
    {
        this->state_machine->add_state(std::make_unique<MainMenuState>(), true);
        //this->state_machine->handle_state_changes(deltaTime);
    }
    
}

void GameOverState::render()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Te has cagado encima colega", 50, 50, 20, LIGHTGRAY);
    std::string score_str = "Puntuacion Final: " + std::to_string(score);
    DrawText(score_str.c_str(), 50, 100, 20, LIGHTGRAY);
    DrawText("Pulsa ESPACIO para reiniciar", 50, 150, 20, LIGHTGRAY);
    EndDrawing();
}
