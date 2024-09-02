#pragma once

#include "pch.h"
#include "PongObject.h"

class Bot : public PongObject
{
public:
    Bot(int windowLimitX, int windowLimitY, int wallThickness, float movingSpeed, int length);

    virtual void UpdateObjectPosition(float deltaTime, bool sdlKeyboardStateUp = false, bool sdlKeyBoardStateDown = false, float objectPositionX = 0.f, float objectPositionY = 0.f, int paddleLength = 0, int wallThickness = 0) override;

private:
    int _mBotDirection;
    float _mBotMovingSpeed;
};

