#include "MobileBase.h"
#include <iostream>

MobileBase::MobileBase(int numWheels, string LiDARType, bool withCam, int initial_X, int initial_Y)
{
    numOfWheels = numWheels;
    LiDAR = LiDARType;
    withCamera = withCam;
    location = Location(initial_X, initial_Y);
}

void MobileBase::MoveX(int dist)
{
    location.SetX(location.GetX() + dist);
}

void MobileBase::MoveY(int dist)
{
    location.SetY(location.GetY() + dist);
}

void MobileBase::ShowInfo()
{
    cout << "**** Mobile base specs and status ****" << endl;
    cout << "Number of wheels: " << numOfWheels << endl;
    cout << "LiDAR type: " << LiDAR << endl;
    cout << "With Camera: " << (withCamera ? "Yes" : "No") << endl;
    cout << "Current Location: (" << location.GetX() << ", " << location.GetY() << ")" << endl;
}

Location & MobileBase::GetLocation()
{
    return location;
}