#include "pch.h"
#include "PongObject.h"

PongObject::PongObject(int windowLimitX, int windowLimitY, int wallThickness) :
    _thickness(wallThickness),
    _length(wallThickness),
    _position({ static_cast<float>(windowLimitX) / 2, static_cast<float>(windowLimitY) / 2 }),
    _windowLimit({ windowLimitX , windowLimitY }),
    _color({ 255, 255, 255 })
{
    _drawingObject.x = _position.x - static_cast<float>(_thickness) / 2;
    _drawingObject.y = _position.y - static_cast<float>(_length) / 2;
    _drawingObject.w = _thickness;
    _drawingObject.h = _length;

    _offset = XYOffset();
}

void PongObject::SetPosition(float x, float y)
{
    _position.x = x;
    _position.y = y;
}

void PongObject::UpdateDrawingObject()
{
    _drawingObject.x = _position.x - _thickness / 2;
    _drawingObject.y = _position.y - _length / 2;
    _drawingObject.w = _thickness;
    _drawingObject.h = _length;
}

void PongObject::SwitchColor() {
    std::random_device fluxCapacitor;
    std::uniform_int_distribution<int> randomColor(50, 255);
    std::mt19937 randomGen(fluxCapacitor());

    for (int i = 0; i < 3; i++)
    {
        _color[i] = randomColor(randomGen);
    }
}

void PongObject::MoveObject(float deltaTime, int objectDirection, int objectSpeed)
{
    // Implementing paddle movement and clipping position if paddle reaches window border
    if (static_cast<int>(_position.y) + _length / 2 > _windowLimit.y)
    {
        _position.y = static_cast<float>(_windowLimit.y) - static_cast<float>(_length) / 2;
    }
    else if (static_cast<int>(_position.y) - _length / 2 < 0)
    {
        _position.y = 0 + static_cast<float>(_length) / 2;
    }
    else
    {
        _position.y += static_cast<float>(objectDirection) * objectSpeed * deltaTime;
    }
}

std::vector<unsigned short int> PongObject::GetColor() { return _color; }

const XYPosition* PongObject::GetPosition() { return &_position; }

const XYWindowLimit* PongObject::GetWindowLimits() { return &_windowLimit; }

const XYOffset* PongObject::GetOffset() { return &_offset; }

const SDL_Rect* PongObject::GetDrawingObject() { return &_drawingObject; }

int PongObject::GetLength() { return _length; }

int PongObject::GetThikness() { return _thickness; }