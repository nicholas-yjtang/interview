#pragma once

#include <string>
#include "MobileBase.h"

using namespace std; 

class Robot
{
public: 
	Robot(string serial, int numWheels, string LiDARType, bool withCam, int initial_X, int initial_Y); 		
	static void ShowManufactuer(); 
	static void ShowNumberOfRobotsExisting(); 
	void ShowSerialNo();
	MobileBase base;

private: 
	static string robotManufactuer;
	static int numberOfRobotsExisting; 

	string serialNumber; 
};




