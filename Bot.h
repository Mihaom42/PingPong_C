#pragma once

#include "pch.h"
#include "PongObject.h"

class Bot : public PongObject
{
public:
    Bot(int windowLimitX, int windowLimitY, int wallThickness, float movingSpeed, int length);

    void changeBotPosition(bool, bool, float, float, float);

private:
    short int _mBotDirection;
    float _mBotMovingSpeed;
};

