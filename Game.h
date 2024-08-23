#pragma once

#define SDL_MAIN_HANDLED

#include "SDL.h"
#include <iostream>
#include <thread>
#include "Ball.h"
#include "Paddle.h"
#include "Bot.h"


class Game
{
public:
    Game(int windowSizeX, int windowSizeY, int paddleSize, bool isRightWall);
    bool Initialize();
    void GameLoop();
    void ShutDownGame();

private:
    bool mIsRunning = true;


    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    int _windowSizeX;
    int _windowSizeY;
    bool _isRightWall;
    int _wallThickness;
    int _playerScore;
    int _botScore;
    bool _colorSwap;

    int* getWallThickness();

    const Uint8* state;

    Uint32 mTicksCount;     // var to save elapsed game time

    std::shared_ptr<Ball> ball1;       // declaring ball1 as a private member of game
    std::shared_ptr<Paddle> paddle1;   // declaring paddle1 as written above
    std::shared_ptr<Bot> bot;
};

