#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include <vector>
using namespace std;

class DecorFourSidedPolygon : public Object
{
private:
	int R;//color of base
	int G;
	int B;

	double UpperLeftX;//values for the four points necessary
	double UpperLeftY;

	double LowerLeftX;
	double LowerLeftY;

	double UpperRightX;
	double UpperRightY;

	double LowerRightX;
	double LowerRightY;

public:
	DecorFourSidedPolygon();
	void Init(double UpperLeftX, double UpperLeftY, double LowerLeftX, double LowerLeftY, double UpperRightX, double UpperRightY, double LowerRightX, double LowerRightY, int R, int G, int B);
	void Update();
	void Render(double cameraXPos, double cameraYPos);
};