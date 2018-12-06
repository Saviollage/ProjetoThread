#include "robot.h"

Robot::Robot()
{
    id = 0;
    posX = 0;
    posY = 0;
}


int Robot::getId()
{
    return id;
}

double Robot::getX()
{
    return posX;
}

double Robot::getY()
{
    return posY;
}


void Robot::setId(int Id)
{
    id = Id;
}


void Robot::setLocation(double X, double Y)
{
    posX = X;
    posY = Y;
}
