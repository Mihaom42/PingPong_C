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
    int _windowSizeX;
    int _windowSizeY;
    bool _isRightWall;
    int _wallThickness;
    int _playerScore;
    int _botScore;
    bool _colorSwap;

    std::shared_ptr<Ball> _ball;
    std::shared_ptr<Paddle> _paddle;
    std::shared_ptr<Bot> _bot;

    bool _mIsRunning;

    const Uint8* _state;
    Uint32 _mTicksCount;    
    Uint32 _flag;

    SDL_Window* _mWindow;
    SDL_Renderer* _mRenderer;

    Color _color;

    int _x;
    int _y;
    int _index;

private:
    void ProcessInput();
    void GenerateOutput();

    void UpdateGame();
    void UpdatePaddle(float deltaTime);
    void UpdateBot(float deltaTime);
    void UpdateBall(float deltaTime);
    void UpdateScoreInfo();
    void CheckOnWinner();

    int GetRoundWinner(int wallThickness);

    void SetColor(Uint32 r = 0, Uint32 g = 0, Uint32 b = 0, Uint32 a = 0);
    void SetCoord(int x = 0, int y = 0);

    void ResetObjectsPosition();
};

