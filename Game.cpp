#include"pch.h"
#include "Game.h"

Game::Game(int windowSizeX, int windowSizeY, int paddleSize, bool isRightWall) :
    _windowSizeX(windowSizeX),
    _windowSizeY(windowSizeY),
    _isRightWall(isRightWall),
    _wallThickness(15),
    _playerScore(0),
    _botScore(0),
    _colorSwap(false) 
{
    _ball = std::make_shared<Ball>(windowSizeX, windowSizeY, _wallThickness, 200.0f, 250.0f);
    _paddle = std::make_shared<Paddle>(windowSizeX, windowSizeY, _wallThickness, 300.0f, paddleSize);
    _bot = std::make_shared<Bot>(windowSizeX, windowSizeY, _wallThickness, 300.0f, paddleSize);

    _mIsRunning = true;

    _state = 0;
    _mTicksCount = 0;
    _flag = 0;

    _mWindow = nullptr;
    _mRenderer = nullptr;

    _color = Color();

    _x = 0;
    _y = 0;
    _index = 0;
}

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
    SetCoord(300, 100);
    _mWindow = SDL_CreateWindow("PingPong", _x, _y, _windowSizeX, _windowSizeY, _flag);

    // a note to window settings: x, y sets top left coordinates; w, h sets size; flags 0 - window deliberately not set to full-screen in this case.
    if (_mWindow == nullptr)
    {
        SDL_Log("Game window initialization failed! Error message: %s", SDL_GetError());
        return false;
        // checking whether game window creation succeeded - if not, return false from function
    }

    // Initializing renderer
    _index = -1;
    _mRenderer = SDL_CreateRenderer(_mWindow, _index, _flag);
    if (_mRenderer == nullptr)
    {
        SDL_Log("Game renderer initialization failed! Error message: %s", SDL_GetError());
        return false;
    }
 
    // Setting base color of game window
    SetColor(0, 0, 0, 255);
    SDL_SetRenderDrawColor(_mRenderer, _color.r, _color.g, _color.b, _color.a);
    SDL_RenderClear(_mRenderer);     // clearing back buffer to current draw color
    SDL_RenderPresent(_mRenderer);   // swap front and back buffers

    return true;
}

void Game::ShutDownGame()
{
    // simply destroys previously created objects and quits from SDL
    SDL_DestroyWindow(_mWindow);
    SDL_DestroyRenderer(_mRenderer);
    SDL_Quit();
}

void Game::GameLoop() {

    // Runs the main game loop in an infinite loop until mIsRunning becomes false. We have separate functions for
        // the three stages of the game loop, so this functions only calls these functions when running the loop.
    while (_mIsRunning)
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
            _mIsRunning = false;
            break;
        }
    }

    // Checking for keyboard state - if Esc is pressed, game quits
    _state = SDL_GetKeyboardState(NULL);
    if (_state[SDL_SCANCODE_ESCAPE])
    {
        _mIsRunning = false;
    }
}

void Game::UpdateGame()
{
    // Establishing delta time
    float deltaTime = (SDL_GetTicks() - _mTicksCount) / 1000.0f;
    _mTicksCount = SDL_GetTicks();

    // Clipping delta time
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    UpdateBall(deltaTime);
    UpdateBot(deltaTime);
    UpdatePaddle(deltaTime);
    UpdateScoreInfo();
    CheckOnWinner();
}

void Game::UpdatePaddle(float deltaTime)
{
    if (_paddle)
    {
        _paddle->UpdateObjectPosition(deltaTime, _state[SDL_SCANCODE_W], _state[SDL_SCANCODE_S]);
    }

    _paddle->UpdateDrawingObject();
}

void Game::UpdateBot(float deltaTime)
{
    if (_bot)
    {
        _bot->UpdateObjectPosition(deltaTime, false, false, _ball->GetDirection());
    }

    _bot->UpdateDrawingObject();
}

void Game::UpdateBall(float deltaTime)
{
    if (_ball)
    {
        _ball->UpdateObjectPosition(deltaTime, false, false, _paddle->GetPosition()->y, _bot->GetPosition()->y, _paddle->GetLength(), _wallThickness);
        _ball->SetDirection();
    }

    _ball->UpdateDrawingObject();
}

void Game::UpdateScoreInfo()
{
    if (GetRoundWinner(_wallThickness) == -1)
    {
        return;
    }

    if (GetRoundWinner(_wallThickness) == 0)
    {
        _botScore += 1;
        std::cout << "\n BOT has won this round. Score: " << _botScore << '\n';
    }
    else if (GetRoundWinner(_wallThickness) == 1)
    {
        _playerScore += 1;
        std::cout << "\n PLAYER has won this round. Score: " << _playerScore << '\n';
    }

    ResetObjectsPosition();
    _ball->ResetVelocity();
    _colorSwap = true;
}

void Game::CheckOnWinner()
{
    if (_playerScore == 5)
    {
        _mIsRunning = false;
        std::cout << "\n PLAYER has won !!! Congrats! \n";
    }
    else if (_botScore == 5)
    {
        _mIsRunning = false;
        std::cout << "\n This time BOT has won. Keep yourself together and try again! \n";
    }
}

int Game::GetRoundWinner(int wallThickness)
{
    XYPosition ballPosition = *_ball->GetPosition();
    XYWindowLimit windowLimit = *_ball->GetWindowLimits();
    XYVelocity ballVelocity = *_ball->GetVelocity();

    if (ballPosition.x < 0 ||
        ballPosition.y < 0 ||
        ballPosition.x > windowLimit.x ||
        ballPosition.y > windowLimit.y)
    {
        return 0; //bot has won
    }
    else if (ballPosition.x >= windowLimit.x - wallThickness && ballVelocity.x > 0)
    {
        return 1; //player has won
    }
    else
    {
        return -1; //another case
    }
}

void Game::GenerateOutput()
{
    SetColor();
    SDL_SetRenderDrawColor(_mRenderer, _color.r, _color.g, _color.b, _color.a);  // setting draw color
    SDL_RenderClear(_mRenderer);

    // Drawing top wall
    const int thickness = 15;
    
    SetColor(255, 255, 255, 255);
    SetCoord();
    SDL_SetRenderDrawColor(_mRenderer, _color.r, _color.g, _color.b, _color.a);  // setting draw color
    SDL_Rect wallTop{ _x, _y, _windowSizeX, thickness };
    SDL_RenderFillRect(_mRenderer, &wallTop);

    // Drawing bottom wall
    SDL_Rect wallBottom{ _x, _windowSizeY - thickness, _windowSizeX, thickness };
    SDL_RenderFillRect(_mRenderer, &wallBottom);

    // Drawing ball and paddle
    if (_paddle != nullptr)
    {
        SDL_RenderFillRect(_mRenderer, _paddle->GetDrawingObject());
    }

    if (_bot != nullptr)
    {
        SDL_RenderFillRect(_mRenderer, _bot->GetDrawingObject());
    }

    if (_colorSwap)
    {
        _ball->SwitchColor();
    }

    if (_ball != nullptr)
    {
        SDL_SetRenderDrawColor(_mRenderer, _ball->GetColor()[0], _ball->GetColor()[1], _ball->GetColor()[2], 255);
        SDL_RenderFillRect(_mRenderer, _ball->GetDrawingObject());
    }

    SDL_RenderPresent(_mRenderer);   // swap front and back buffers

    if (_colorSwap)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        _colorSwap = false;
    }
}

void Game::ResetObjectsPosition()
{
    XYOffset paddleOffset = *_paddle->GetOffset();
    XYOffset botOffset = *_bot->GetOffset();
    XYOffset ballOffset = *_ball->GetOffset();

    _ball->SetPosition(_windowSizeX / ballOffset.x, _windowSizeY / ballOffset.y);
    _paddle->SetPosition(_paddle->GetThikness() / paddleOffset.x, _paddle->GetWindowLimits()->y / paddleOffset.y);
    _bot->SetPosition(_bot->GetThikness() * botOffset.x, _bot->GetWindowLimits()->y / botOffset.y);
}

void Game::SetCoord(int x, int y)
{
    _x = x;
    _y = y;
}

void Game::SetColor(Uint32 r, Uint32 g, Uint32 b, Uint32 a)
{
    _color.r = r;
    _color.g = g;
    _color.b = b;
    _color.a = a;
}