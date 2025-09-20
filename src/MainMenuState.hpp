#pragma once
#include <GameState.hpp>
#include <Bird.hpp>

class MainMenuState : public GameState
{
    public:
        MainMenuState();
        ~MainMenuState() = default;

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause(){};
        void resume(){};

    
    private:
        Bird player_bird;
        char entered_key;
};