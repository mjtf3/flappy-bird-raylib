#pragma once
#include <GameState.hpp>
#include <raylib.h>

class GameOverState : public GameState
{
    public:
        GameOverState(int score);
        ~GameOverState() = default;

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause(){};
        void resume(){};

    
    private:
        char entered_key;
        bool restart_game = false;
        int score;
};