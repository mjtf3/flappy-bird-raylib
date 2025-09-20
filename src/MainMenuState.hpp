#pragma once
#include <GameState.hpp>
#include <Bird.hpp>
#include <deque>
#include <PipePair.hpp>

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
        std::deque<PipePair> pipes;
        Bird player_bird;
        char entered_key;
};