#include "pch.h"
#include "Ball.h"

bool Ball::ballOut() {
    return _position.x < 0 ||
        _position.y < 0 ||
        _position.x > static_cast<float>(_windowLimitX) ||
        _position.y > static_cast<float>(_windowLimitY);
}

int Ball::getRoundWinner(int wallThickness)
{
    if (_position.x < 0 ||
        _position.y < 0 ||
        _position.x > _windowLimitX ||
        _position.y > _windowLimitY)
    {
        return 0; //bot has won
    }

    if (_position.x >= _windowLimitX - wallThickness && _velocityX > 0)
    {
        return 1; //player has won
    }
}

void Ball::resetVelocity() {
    _velocityX = _startVelocityX;
    _velocityY = _startVelocityY;
}

void Ball::setDirection()
{
    if (_previousPosition.y == getPosition()->y)
    {
        return;
    }

    float position = getPosition()->y;

    _ballDirection = position - _previousPosition.y;
    _previousPosition.y = position;
}

void Ball::updatePosition(float deltaTime, int wallThickness, float paddlePositionY, float botPaddlePositionY, int paddleLength)
{
    _position.x += _velocityX * deltaTime;
    _position.y += _velocityY * deltaTime;

    _hasBounced = false;

    // Handling bouncing off walls
    // Top wall
    if (_position.y <= wallThickness && _velocityY < 0)
    {
        _velocityY *= -(1 + _acceleration);
        _hasBounced = true;
    }
    // Bottom wall
    if (_position.y >= _windowLimitY - wallThickness && _velocityY > 0)
    {
        _velocityY *= -(1 + _acceleration);
        _hasBounced = true;
    }

    // Handling bouncing off paddles
    if (_position.x <= wallThickness &&
        _velocityX < 0 &&
        _position.y <= paddlePositionY + paddleLength / 2 &&
        _position.y >= paddlePositionY - paddleLength / 2)
    {
        _velocityX *= -(1 + _acceleration);
        _hasBounced = true;
    }

    else if (_position.x >= _windowLimitX - wallThickness &&
        _velocityX > 0 &&
        _position.y <= botPaddlePositionY + paddleLength / 2 &&
        _position.y >= botPaddlePositionY - paddleLength / 2)
    {
        _velocityX *= -(1 + _acceleration);
        _hasBounced = true;
    }
}