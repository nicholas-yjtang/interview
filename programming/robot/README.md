# Problem

Given a set of c++ headers, and the main.cpp, complete the implementation of the robot program.

```cpp
class Location
{
public: 
	Location(int x_val = 0, int y_val = 0);	
	...
	
private: 
	int x, y; 
};

class MobileBase
{
public: 
	MobileBase(int numWheels, string LiDARType, bool withCam, int initial_X, int initial_Y);
	void MoveX(int dist); 
	void MoveY(int dist);
	...
	
private:
	int numOfWheels; 
	string LiDAR; 
	bool withCamera; 
	...
};

class Robot
{
public: 
	Robot(string serial, int numWheels, string LiDARType, bool withCam, int initial_X, int initial_Y); 
	
	...
	
	static void ShowManufactuer(); 
	static void ShowNumberOfRobotsExisting(); 

	MobileBase base;

private: 
	static string robotManufactuer;
	static int numberOfRobotsExisting; 

	string serialNumber; 
};


```

Draw a class and sequence diagram for the robot program.

Convert this c++ program to a java program.

# Solution

## Part 1 - implement the robot program in c++

We implement the Location class first.\
Seeing as the x and y coordinates are private, we create getter and setter methods to access and set the coordinates.

See the final Location.h and Location.cpp which simply implements these simple methods

We then implement the MobileBase class.\
Looking at the original Main.cpp, we see that the MobileBase class has a few methods, namely MoveX, MoveY, GetLocation and ShowLocation.

We add these function definitions to the MobileBase class header file.\
We also add a private member variable of type Location to the MobileBase class.

Utilizing this location variable we declared, we can now implement the MoveX and MoveY methods.\
MoveX means we move the robot in the x direction, so we simply add the distance to the current x coordinate.\
MoveY means we move the robot in the y direction, so we simply add the distance to the current y coordinate.

The showLocation method simply prints out the current location of the robot.\
The getLocation method simply returns the current location of the robot.

The final result is the MobileBase.h and MobileBase.cpp files.

Finally we implement the Robot class.

Looking at the original Main.cpp, we see that the Robot class has one method missing from the header file, namely ShowSerialNo.

We implement all the function prototypes in the Robot class header file.

The final result is the Robot.h and Robot.cpp files.

## Part 2 - draw the class and sequence diagram for the robot program

Using the header files we created, we can abstract the class and sequence diagrams for the robot program.

We used plantuml to create the diagrams.

### Class Diagram
The class diagram for the robot program

The original can be found under diagrams/robotics_class.puml

![Class Diagram](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/nicholas-yjtang/interview/main/programming/robot/diagrams/robotics_class.puml)

### Sequence Diagram
The sequence diagram for the robot program

![Sequence Diagram](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/nicholas-yjtang/interview/main/programming/robot/diagrams/move_sequence.puml)

## Part 3 - convert the c++ program to java

Although there are some tools that automate the conversion of c++ to java, we will do it manually.

We start first looking at Location.h. We don't change anything in particular for the conversion, so it was rather straight forward to convert the syntax via the header file.

Then we look at MobileBase.h

The conversion is also rather straight forward. The only thing we need to take care of is the print statements, converting from cout to System.out.println.

Last we look at Robot.h.\
In our implementation (Robot.cpp), we actually utilized the initializer list to initialize the MobileBase class.\
However, in java, we cannot do this.

So we explicitly initialize the MobileBase class in the constructor of the Robot class.

See the final Location.java, MobileBase.java and Robot.java files for the final result.

# Compile
To compile run the compile.sh

# Clean
To clean the build, run clean.sh