#include "Robot.h"
#include <iostream>

string Robot::robotManufactuer = "SIT Robotics";
int Robot::numberOfRobotsExisting = 0;

Robot::Robot(string serial, int numWheels, string LiDARType, bool withCam, int initial_X, int initial_Y) : base(numWheels, LiDARType, withCam, initial_X, initial_Y)
{
    serialNumber = serial;
    numberOfRobotsExisting++;
}

void Robot::ShowManufactuer()
{
    cout << "Manufacturer is: " << robotManufactuer << endl;
}

void Robot::ShowNumberOfRobotsExisting()
{
    cout << "Number of Robots Existing is: " << numberOfRobotsExisting << endl;
}

void Robot::ShowSerialNo()
{
    cout << "Serial Number is: " << serialNumber << endl;
}