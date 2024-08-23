#pragma once

#include "PongObject.h"
#include "pch.h"

class Paddle :  public PongObject
{
public:
    Paddle(int windowLimitX, int windowLimitY, int wallThickness, float movingSpeed, int length) :
        PongObject(windowLimitX, windowLimitY, wallThickness), _mPaddleMovingSpeed(movingSpeed), _mPaddleDirection(0) {
        _length = length;
        _position.x = _thickness / 2;
        _position.y = _windowLimitY / 2;
    };

    void changePaddlePosition(bool, bool, float);

private:
    short int _mPaddleDirection;
    float _mPaddleMovingSpeed;
};

