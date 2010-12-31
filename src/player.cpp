#include "player.h"
#include <cmath>

Player::Player() : Speed(0), Yrot(0), Zrot(0), X(0), Y(0), Z(0), Moving(false) {}
Player::Player(float initspeed, float initYrot, float initZrot, float initX, float initY, float initZ) :
    Speed(initspeed), Yrot(initYrot), Zrot(initZrot), X(initX), Y(initY), Z(initZ), Moving(false) {}

void Player::Forward(float amount)
{
    Moving = true;
    float xStep = Speed * sin((PI * Zrot) / 180) * amount;
    float yStep = Speed * cos((PI * Zrot) / 180) * amount;
    float zStep = -Speed * sin((PI * Yrot) / 180) * amount;
    X += (xStep * cos((PI * Yrot) / 180));
    Y += (yStep * cos((PI * Yrot) / 180));
    Z += zStep;
}

void Player::Strafe(float amount)
{
    float xStep = Speed * sin((PI * Zrot) / 180) * amount;
    float yStep = Speed * cos((PI * Zrot) / 180) * amount;
    //TODO: Find out why this is necessary
    if(Moving == true)
    {
        xStep *= 0.707106;        
        yStep *= 0.707106;
    }

    X -= yStep;
    Y += xStep;
}

void Player::ChangeRotation(float deltaYrot, float deltaZrot)
{
    Zrot += deltaZrot;
    Yrot += deltaYrot;

    if(Zrot >= 360)
        Zrot -= 360;
    else if (Zrot < 0)
        Zrot += 360;

    if(Yrot < -90)
        Yrot = -90;
    else if(Yrot >= 90)
        Yrot = 90;
}
