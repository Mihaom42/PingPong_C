#include "pch.h"
#include "Bot.h"

Bot::Bot(int windowLimitX, int windowLimitY, int wallThickness, float movingSpeed, int length) :
    PongObject(windowLimitX, windowLimitY, wallThickness), _mBotMovingSpeed(200), _mBotDirection(0)
{
    _length = length;
    _position.x = _thickness * 39;
    _position.y = _windowLimitY / 2;
}

void Bot::changeBotPosition(bool sdlKeyboardStateUp, bool sdlKeyBoardStateDown, float deltaTime, float ballX, float ballY) {

    _mBotDirection = 0;

    float direction = ballX;

    if (direction < 0)
    {
        _mBotDirection -= 1;
    }

    if (direction > 0)
    {
        _mBotDirection += 1;
    }

    // Implementing paddle movement and clipping position if paddle reaches window border
    if (_position.y + _length / 2 > _windowLimitY)
    {
        _position.y = _windowLimitY - _length / 2;
    }
    else if (_position.y - _length / 2 < 0)
    {
        _position.y = 0 + _length / 2;
    }
    else
    {
        _position.y += _mBotDirection * _mBotMovingSpeed * deltaTime;
    }
}