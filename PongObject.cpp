#include "pch.h"
#include "PongObject.h"

PongObject::PongObject(int windowLimitX, int windowLimitY, int wallThickness) :
    _thickness(wallThickness),
    _length(wallThickness),
    _position({ static_cast<float>(windowLimitX) / 2, static_cast<float>(windowLimitY) / 2 }),
    _windowLimitX(windowLimitX),
    _windowLimitY(windowLimitY),
    _color({ 255, 255, 255 })
{
    _drawingObject.x = _position.x - static_cast<float>(_thickness) / 2;
    _drawingObject.y = _position.y - static_cast<float>(_length) / 2;
    _drawingObject.w = _thickness;
    _drawingObject.h = _length;
}

void PongObject::setPosition(float x, float y)
{
    _position.x = x;
    _position.y = y;
}

void PongObject::setWindowLimits(int windowLimitX, int windowLimitY)
{
    _windowLimitX = windowLimitX;
    _windowLimitY = windowLimitY;
}

SDL_Rect* PongObject::getDrawingObject() { return &_drawingObject; }

void PongObject::updateDrawingObject()
{
    _drawingObject.x = _position.x - _thickness / 2;
    _drawingObject.y = _position.y - _length / 2;
    _drawingObject.w = _thickness;
    _drawingObject.h = _length;
}

void PongObject::switchColor() {
    std::random_device fluxCapacitor;
    std::uniform_int_distribution<int> randomColor(50, 255);
    std::mt19937 randomGen(fluxCapacitor());

    for (int i = 0; i < 3; i++)
    {
        _color[i] = randomColor(randomGen);
    }
}

std::vector<unsigned short int> PongObject::getColor() { return _color; }

XYPosition* PongObject::getPosition() { return &_position; }

int PongObject::getLength() { return _length; }

int PongObject::getThickness() { return _thickness; }
