#include <MainMenuState.hpp>
#include <iostream>
#include <deque>
#include <GameOverState.hpp>
#include <StateMachine.hpp>

extern "C" {
    #include <raylib.h>
}

int score = 0;

float gravity = 600.0f;

int pipe_gap = 120;
int pipe_width = 200;
int pipe_speed = 200;

int spawnTimer = 0;
int spawnEvery = 1500;

float PIPE_W = 32;
float PIPE_H = 320;

bool CheckCollision(Rectangle bird_col, PipePair pipes) {
    if (CheckCollisionRecs(bird_col, pipes.top) || CheckCollisionRecs(bird_col, pipes.bottom))
    {
        return true;
    }
    if (bird_col.y < 0 || bird_col.y + bird_col.height > GetScreenHeight())
    {
        return true;
    }
    return false;
}

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
        player_bird.vy = -300.0f;
    }
    
}

void MainMenuState::update(float deltaTime)
{
    //PAJARO
    this->handleInput();
    player_bird.vy += gravity * deltaTime;
    player_bird.y += player_bird.vy * deltaTime;

    this->bird_col = Rectangle{.x = player_bird.x - player_bird.radio, .y = player_bird.y - player_bird.radio, .width = player_bird.radio*2, .height = player_bird.radio*2};
    
    //TUBERIAS
    // Acumular tiempo para el spawn de pipes
    spawnTimer += deltaTime * 1000.0f; // Convertir a milisegundos
    
    // Verificar si es tiempo de spawnar
    if (spawnTimer >= spawnEvery)
    {
        float pipe_y_offset_top = GetRandomValue(PIPE_H/2, GetScreenWidth()/2);
        float pipe_y_offset_bottom = GetRandomValue(PIPE_H/2, GetScreenWidth()/2);
        
        float start_x = GetScreenWidth();
        PipePair new_pipe = PipePair{
            .top = Rectangle{.x = start_x, .y = -pipe_y_offset_top, .width = PIPE_W, .height = PIPE_H},
            .bottom = Rectangle{.x = start_x, .y = (PIPE_H - pipe_y_offset_top) + pipe_y_offset_bottom, .width = PIPE_W, .height = PIPE_H}
        };
        
        pipes.push_back(new_pipe);
        
        // Resetear el timer
        spawnTimer = 0;
    }

    if (!pipes.empty() && (pipes.front().bottom.x < 0 - pipe_width))
    {
        pipes.pop_front();
    }

    for (auto &&i : pipes)
    {
        i.bottom.x -= pipe_speed * deltaTime;
        i.top.x -= pipe_speed * deltaTime;
        if (CheckCollision(bird_col, i))
        {
            this->state_machine->add_state(std::make_unique<GameOverState>(score), true);
            this->state_machine->handle_state_changes(deltaTime);
            score = 0;
            return;
        }
        if (i.bottom.x + PIPE_W < player_bird.x && !i.scored)
        {
            score++;
            i.scored = true;
            std::cout << "Score: " << score << std::endl;
        }
        
    }
}

void MainMenuState::render()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Bienvenido a Flappy Bird DCA", 50, 50, 20, LIGHTGRAY);
    //DrawRectanglePro(bird_col, {0,0}, 0.0f, BLUE);
    DrawCircle(player_bird.x, player_bird.y, player_bird.radio, RED);
    for (auto &&i : pipes)
    {
        DrawRectangleRec(i.top, GREEN);
        DrawRectangleRec(i.bottom, GREEN);
    }

    std::string score_str = "Puntuacion " + std::to_string(score);

    DrawText(score_str.c_str(), 50, 100, 20, LIGHTGRAY);

    EndDrawing();
}