#include "pch.h"
#include "Bot.h"

Bot::Bot(int windowLimitX, int windowLimitY, int wallThickness, float movingSpeed, int length) :
    PongObject(windowLimitX, windowLimitY, wallThickness), _mBotMovingSpeed(200), _mBotDirection(0)
{
    _offset.x = 39;
    _offset.y = 2;

    _length = length;
    _position.x = _thickness * _offset.x;
    _position.y = _windowLimit.y / _offset.y;
}

void Bot::UpdateObjectPosition(float deltaTime, bool sdlKeyboardStateUp, bool sdlKeyBoardStateDown, float objectPositionX, float objectPositionY, int paddleLength, int wallThickness)
{
    _mBotDirection = 0;

    float direction = objectPositionX;

    if (direction < 0)
    {
        _mBotDirection -= 1;
    }

    if (direction > 0)
    {
        _mBotDirection += 1;
    }

    MoveObject(deltaTime, _mBotDirection, _mBotMovingSpeed);
}