#pragma once

#include <vector>
#include <random>
#include "SDL.h"

struct XYPosition 
{
    float x;
    float y;
};

struct XYWindowLimit
{
    int x;
    int y;
};

struct XYOffset
{
    int x;
    int y;
};

class PongObject
{
public:
    PongObject(int windowLimitX, int windowLimitY, int wallThickness);
    ~PongObject() {};

    void UpdateDrawingObject();
    void SwitchColor();

    const XYPosition* GetPosition();
    const XYWindowLimit* GetWindowLimits();
    const XYOffset* GetOffset();
    const SDL_Rect* GetDrawingObject();
    std::vector<unsigned short int> GetColor();
    int GetLength();
    int GetThikness();

    void SetPosition(float x, float y);

protected:
    int _thickness;
    int _length;
    XYPosition _position;
    XYWindowLimit _windowLimit;
    std::vector<unsigned short int> _color;
    //std::vector <Color> _color;
    
    SDL_Rect _drawingObject;

    XYOffset _offset;

    int offsetByX;
    int offsetByY;

    void MoveObject(float deltaTime, int objectDirection, int objectSpeed);
    virtual void UpdateObjectPosition(float deltaTime, bool sdlKeyboardStateUp = false, bool sdlKeyBoardStateDown = false, float objectPositionX = 0.f, float objectPositionY = 0.f, int paddleLength = 0, int wallThickness = 0) = 0;
};

