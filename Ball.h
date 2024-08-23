#pragma once

#include "PongObject.h"
#include "pch.h"

class Ball : public PongObject
{
public:
    Ball(int windowLimitX,
        int windowLimitY,
        int wallThickness,
        float movingSpeedX, float movingSpeedY) :
        PongObject(windowLimitX, windowLimitY, wallThickness),
        _velocityX(movingSpeedX),
        _velocityY(movingSpeedY),
        _startVelocityX(movingSpeedX),
        _startVelocityY(movingSpeedY),
        _hasBounced(false),
        _acceleration(0.02) {};

    void updatePosition(float deltaTime, int wallThickness, float paddlePositionY, float botPaddlePositionY, int paddleLength);
    bool ballOut();
    int getRoundWinner(int wallThickness);
    void resetVelocity();
    void setDirection();
    void setPreviousPosition(XYPosition position) { _previousPosition = position; }
    float getDirection() { return _ballDirection; }

private:
    float _startVelocityX;
    float _startVelocityY;
    float _velocityX;
    float _velocityY;
    float _acceleration;
    bool _hasBounced;

    XYPosition _previousPosition;

    float _ballDirection;
};

