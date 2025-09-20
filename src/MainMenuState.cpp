#include <MainMenuState.hpp>
#include <iostream>
#include <deque>
extern "C" {
    #include <raylib.h>
}

float gravity = 2000.0f;

int pipe_gap = 120;
int pipe_width = 200;
int pipe_speed = 200;

int spawnTimer = 0;
int spawnEvery = 1500;

float PIPE_W = 32;
float PIPE_H = 320;

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
    for (auto &&i : pipes)
    {
        i.bottom.x -= pipe_speed * deltaTime;
        i.top.x -= pipe_speed * deltaTime;
    }
    
    if (pipes.front().bottom.x < 0 - pipe_width)
    {
        pipes.pop_front();
    }
    
    
    
    this->handleInput();
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
    for (auto &&i : pipes)
    {
        DrawRectangleRec(i.top, GREEN);
        DrawRectangleRec(i.bottom, GREEN);
    }
    EndDrawing();
}