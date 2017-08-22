#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include "Grass.h"
#include <vector>
using namespace std;

class GrassJoint : public Object
{
private:
	int JointID;//ID of line, used for calculating degree to which line sways in the wind 
	
	int BegX;//start and end of line
	int BegY;
	int EndX;
	int EndY;

	double R;//color of line
	double G;
	double B;

	int counter;
	int WindDirection;

public:
	GrassJoint();
	void Init(int JointID, double BegX, double BegY, double EndX, double EndY, double R, double G, double B, int counter);
	void Update();
	void Render(double cameraXPos, double cameraYPos);
};