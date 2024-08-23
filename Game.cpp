/*
 * This source file implements the procedures for the Game class.
 */

#include"pch.h"
#include "Game.h"

Game::Game(int windowSizeX, int windowSizeY, int paddleSize, bool isRightWall) :
    _windowSizeX(windowSizeX),
    _windowSizeY(windowSizeY),
    _isRightWall(isRightWall),
    _wallThickness(15),
    _playerScore(0),
    _botScore(0),
    _colorSwap(false),
    ball1(new Ball(windowSizeX, windowSizeY, _wallThickness, 200.0f, 250.0f)),
    paddle1(new Paddle(windowSizeX, windowSizeY, _wallThickness, 300.0f, paddleSize)),
    bot(new Bot(windowSizeX, windowSizeY, _wallThickness, 300.0f, paddleSize)) 
   {};

bool Game::Initialize()
{
    // Initializing graphics functions
    int sdlInitializeResult = SDL_Init(SDL_INIT_VIDEO);     // initializing SDL with video only
    if (sdlInitializeResult != 0)
    {
        SDL_Log("Have not been able to initialize SDL; error message: %s", SDL_GetError());
        return false;
        // SDL_Init return int; if return value is non-zero, initialization failed.
    }

    // Initializing game window
    mWindow = SDL_CreateWindow("PingPong", 300, 100, _windowSizeX, _windowSizeY, 0);

    // a note to window settings: x, y sets top left coordinates; w, h sets size; flags 0 - window deliberately not set to full-screen in this case.
    if (mWindow == nullptr)
    {
        SDL_Log("Game window initialization failed! Error message: %s", SDL_GetError());
        return false;
        // checking whether game window creation succeeded - if not, return false from function
    }

    // Initializing renderer
    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    if (mRenderer == nullptr)
    {
        SDL_Log("Game renderer initialization failed! Error message: %s", SDL_GetError());
        return false;
    }

    // Setting base color of game window
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);     // clearing back buffer to current draw color
    SDL_RenderPresent(mRenderer);   // swap front and back buffers

    return true;
}

void Game::ShutDownGame()
{
    // simply destroys previously created objects and quits from SDL
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

void Game::GameLoop() {

    // Runs the main game loop in an infinite loop until mIsRunning becomes false. We have separate functions for
        // the three stages of the game loop, so this functions only calls these functions when running the loop.
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    // Continuously polling SDL event queue - if window is closed, game quits
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }

    // Checking for keyboard state - if Esc is pressed, game quits
    state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
}

void Game::UpdateGame()
{
    // Guarding against too fast refresh
    //    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    // Establishing delta time
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    mTicksCount = SDL_GetTicks();

    // Clipping delta time
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    if (paddle1 != nullptr)
    {
        // Handling paddle movements
        paddle1->changePaddlePosition(state[SDL_SCANCODE_W], state[SDL_SCANCODE_S], deltaTime);
    }

    if (bot != nullptr)
    {
        bot->changeBotPosition(state[SDL_SCANCODE_W], state[SDL_SCANCODE_S], deltaTime, ball1->getDirection(), ball1->getPosition()->y);
    }

    if (ball1 == nullptr)
    {
        return;
    }

    // Implementing ball movements
    ball1->updatePosition(deltaTime, _wallThickness, paddle1->getPosition()->y, bot->getPosition()->y, paddle1->getLength());
    ball1->setDirection();

    if (ball1->getRoundWinner(_wallThickness) == 0)
    {
        ball1->setPosition(_windowSizeX / 2, _windowSizeY / 2);
        ball1->resetVelocity();
        _colorSwap = true;
        _botScore += 1;

        std::cout << "\n BOT has won this round. Score: " << _botScore << '\n';
    }

    else if (ball1->getRoundWinner(_wallThickness) == 1)
    {
        ball1->setPosition(_windowSizeX / 2, _windowSizeY / 2);
        ball1->resetVelocity();
        _colorSwap = true;
        _playerScore += 1;

        std::cout << "\n PLAYER has won this round. Score: " << _playerScore << '\n';
    }

    if (_playerScore == 5)
    {
        mIsRunning = false;
        std::cout << "\n PLAYER has won !!! Congrats! \n";
    }
    else if (_botScore == 5)
    {
        mIsRunning = false;
        std::cout << "\n This time BOT has won. Keep yourself together and try again! \n";
    }

    // Updating drawing objects in Paddle and Ball
    paddle1->updateDrawingObject();
    ball1->updateDrawingObject();
    bot->updateDrawingObject();
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);  // setting draw color
    SDL_RenderClear(mRenderer);

    const int thickness = 15;
    // Drawing top wall
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);  // setting draw color
    SDL_Rect wallTop{ 0, 0, _windowSizeX, thickness };
    SDL_RenderFillRect(mRenderer, &wallTop);

    // Drawing bottom wall
    SDL_Rect wallBottom{ 0, _windowSizeY - thickness, _windowSizeX, thickness };
    SDL_RenderFillRect(mRenderer, &wallBottom);

    // Drawing right wall
    //if (_isRightWall) 
    //{
    //    SDL_Rect wallRight {_windowSizeX - thickness, 0, thickness, _windowSizeY};
    //    SDL_RenderFillRect(mRenderer, &wallRight);
    //}

    // Drawing ball and paddle
    if (paddle1 != nullptr)
    {
        SDL_RenderFillRect(mRenderer, paddle1->getDrawingObject());
    }

    if (bot != nullptr)
    {
        SDL_RenderFillRect(mRenderer, bot->getDrawingObject());
    }

    if (_colorSwap)
    {
        ball1->switchColor();
    }

    if (ball1 != nullptr)
    {
        SDL_SetRenderDrawColor(mRenderer, ball1->getColor()[0], ball1->getColor()[1], ball1->getColor()[2], 255);
        SDL_RenderFillRect(mRenderer, ball1->getDrawingObject());
    }

    SDL_RenderPresent(mRenderer);   // swap front and back buffers

    if (_colorSwap)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        _colorSwap = false;
    }
}

int* Game::getWallThickness()
{
    return &_wallThickness;
}
