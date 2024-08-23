#pragma once

#include <vector>
#include <random>
#include "SDL.h"

struct XYPosition 
{
    float x;
    float y;
};

class PongObject 
{
public:
    PongObject(int windowLimitX, int windowLimitY, int wallThickness);
    ~PongObject() {};

    void updateDrawingObject();
    void switchColor();

    XYPosition* getPosition();

    SDL_Rect* getDrawingObject();
    std::vector<unsigned short int> getColor();
    int getLength();
    int getThickness();
    void setPosition(float x, float y);
    void setWindowLimits(int, int);

protected:
    int _windowLimitX;
    int _windowLimitY;
    XYPosition _position;
    int _length;
    int _thickness;
    std::vector<unsigned short int> _color;
    SDL_Rect _drawingObject;
};

