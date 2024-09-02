#pragma once

#include "PongObject.h"
#include "pch.h"

class Paddle :  public PongObject
{
public:
    Paddle(int windowLimitX, int windowLimitY, int wallThickness, float movingSpeed, int length);

    virtual void UpdateObjectPosition(float deltaTime, bool sdlKeyboardStateUp = false, bool sdlKeyBoardStateDown = false, float objectPositionX = 0.f, float objectPositionY = 0.f, int paddleLength = 0, int wallThickness = 0) override;

private:
    int _mPaddleDirection;
    float _mPaddleMovingSpeed;
};

