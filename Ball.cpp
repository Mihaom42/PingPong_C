#include "pch.h"
#include "Ball.h"

Ball::Ball(int windowLimitX, int windowLimitY, int wallThickness, float movingSpeedX, float movingSpeedY) :
    PongObject(windowLimitX, windowLimitY, wallThickness),
    _velocity({movingSpeedX, movingSpeedY}),
    _startVelocityX(movingSpeedX),
    _startVelocityY(movingSpeedY),
    _hasBounced(false),
    _acceleration(0.02) 
{
    _offset.x = 2;
    _offset.y = 2;

    _previousPosition = XYPosition();
    _ballDirection = 0;
}

void Ball::ResetVelocity() {
    _velocity.x = _startVelocityX;
    _velocity.y = _startVelocityY;
}

void Ball::SetDirection()
{
    if (_previousPosition.y == GetPosition()->y)
    {
        return;
    }

    float position = GetPosition()->y;

    _ballDirection = position - _previousPosition.y;
    _previousPosition.y = position;
}

void Ball::UpdateObjectPosition(float deltaTime, bool sdlKeyboardStateUp, bool sdlKeyBoardStateDown, float paddlePositionY, float botPaddlePositionY, int paddleLength, int wallThickness)
{
    _position.x += _velocity.x * deltaTime;
    _position.y += _velocity.y * deltaTime;

    _hasBounced = false;

    // Handling bouncing off walls
    // Top wall
    if (_position.y <= static_cast<float>(wallThickness) && _velocity.y < 0)
    {
        _velocity.y *= -(1 + _acceleration);
        _hasBounced = true;
    }
    // Bottom wall
    if (_position.y >= static_cast<float>(_windowLimit.y - wallThickness) && _velocity.y > 0)
    {
        _velocity.y *= -(1 + _acceleration);
        _hasBounced = true;
    }

    // Handling bouncing off paddles
    if (_position.x <= static_cast<float>(wallThickness) &&
        _velocity.x < 0 &&
        _position.y <= paddlePositionY + paddleLength / 2 &&
        _position.y >= paddlePositionY - paddleLength / 2)
    {
        _velocity.x *= -(1 + _acceleration);
        _hasBounced = true;
    }

    else if (_position.x >= static_cast<float>(_windowLimit.x - wallThickness) &&
        _velocity.x > 0 &&
        _position.y <= botPaddlePositionY + paddleLength / 2 &&
        _position.y >= botPaddlePositionY - paddleLength / 2)
    {
        _velocity.x *= -(1 + _acceleration);
        _hasBounced = true;
    }
}