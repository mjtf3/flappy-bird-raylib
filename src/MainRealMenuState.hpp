#pragma once
#include <GameState.hpp>
extern "C" {
    #include <raylib.h>
}

class MainRealMenuState : public GameState
{
    public:
        MainRealMenuState();
        ~MainRealMenuState() = default;

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
        Texture2D background;
};