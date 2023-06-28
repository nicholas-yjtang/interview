#pragma once

#include <string>
#include "Location.h"

using namespace std; 

class MobileBase
{
public: 
	MobileBase(int numWheels, string LiDARType, bool withCam, int initial_X, int initial_Y);
	void MoveX(int dist); 
	void MoveY(int dist);
	void ShowInfo();
	Location & GetLocation();

private:
	int numOfWheels; 
	string LiDAR; 
	bool withCamera; 
	Location location;
};


