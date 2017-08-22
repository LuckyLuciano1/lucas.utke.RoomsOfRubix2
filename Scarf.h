#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"

using namespace std;


class Scarf : public Object
{
private:
	struct Point
	{
		float x, y;
		float dirX, dirY;
		int Vel;
	};

	int R;
	int G;
	int B;

	int ScarfWidth;

	const size_t ScarfPointNum = 50;
	int ScarfPointNum_int = 50;
	Point PointArray[50];

	double counter;
public:
	Scarf();
	void Init(double x, double y, int ScarfWidth, int R, int G, int B);
	void Update(double x, double y, double dirX, double dirY);
	void Render(double cameraXPos, double cameraYPos);
};