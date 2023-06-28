#pragma once

class Location
{
public: 
	Location(int x_val = 0, int y_val = 0);	
	int GetX() const;
	int GetY() const;
	void SetX(int x_val);
	void SetY(int y_val);
private: 
	int x, y; 
};


