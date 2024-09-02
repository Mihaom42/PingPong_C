#pragma once

#include "PongObject.h"
#include "pch.h"

struct XYVelocity
{
    float x;
    float y;
};

class Ball : public PongObject
{
public:
    Ball(int windowLimitX, int windowLimitY, int wallThickness, float movingSpeedX, float movingSpeedY);    
   
    void ResetVelocity();
    void SetDirection();

    float GetDirection() { return _ballDirection; }
    XYVelocity* GetVelocity() { return &_velocity; }

    virtual void UpdateObjectPosition(float deltaTime, bool sdlKeyboardStateUp = false, bool sdlKeyBoardStateDown = false, float paddlePositionY = 0.f, float botPaddlePositionY = 0.f, int paddleLength = 0, int wallThickness = 0) override;

private:
    XYVelocity _velocity;
    float _startVelocityX;
    float _startVelocityY;
    bool _hasBounced;
    float _acceleration;
    
    XYPosition _previousPosition;
    float _ballDirection;
};

