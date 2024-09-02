#include "pch.h"
#include "Paddle.h"

Paddle::Paddle(int windowLimitX, int windowLimitY, int wallThickness, float movingSpeed, int length) :
    PongObject(windowLimitX, windowLimitY, wallThickness), _mPaddleMovingSpeed(movingSpeed), _mPaddleDirection(0) 
{
    _offset.x = 2;
    _offset.y = 2;

    _length = length;
    _position.x = static_cast<int>(_thickness / _offset.x);
    _position.y = static_cast<int>(_windowLimit.y / _offset.y);
} 

void Paddle::UpdateObjectPosition(float deltaTime, bool sdlKeyboardStateUp, bool sdlKeyBoardStateDown, float objectPositionX, float objectPositionY, int paddleLength, int wallThickness)
{
    _mPaddleDirection = 0;
    if (sdlKeyboardStateUp)
    {
        _mPaddleDirection -= 1;
    }
    if (sdlKeyBoardStateDown)
    {
        _mPaddleDirection += 1;
    }

    MoveObject(deltaTime, _mPaddleDirection, _mPaddleMovingSpeed);
}
