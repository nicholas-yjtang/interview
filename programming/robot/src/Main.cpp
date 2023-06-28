#include <iostream>

#include "Robot.h"

int main()
{
	Robot robot_1("20220518A01", 4, "Husarion ROSbot 2 Pro", true, 0, 0); 
	Robot::ShowManufactuer();
	robot_1.ShowSerialNo();
	cout << endl;
	Robot::ShowNumberOfRobotsExisting();
	Location loc1 = robot_1.base.GetLocation();
	cout << "The intial location is: " << "(" << loc1.GetX() << ", " << loc1.GetY() << ")" << endl << endl;

	robot_1.base.MoveX(30); 
	robot_1.base.MoveY(-50); 
	robot_1.base.ShowInfo();  
	cout << endl;

	Robot robot_2("20220518B03", 2, "TurtleBot Waffle Pi", false, 10, 10);
	Robot::ShowManufactuer();
	robot_2.ShowSerialNo();
	cout << endl;
	Robot::ShowNumberOfRobotsExisting();

	robot_2.base.MoveX(200);
	robot_2.base.MoveY(-100);
	robot_2.base.ShowInfo();
}