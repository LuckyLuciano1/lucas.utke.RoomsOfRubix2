#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include "DecorTriangle.h"
#include <vector>

using namespace std;



class Diamond3D : public Object
{
private:

	struct Point
	{
		double OrigX, OrigY, OrigZ, x, y, z;//the x/yz values are used for rendering, and are the Orig values with trig+Angle factored in within Update().
	};

	struct Triangle//data used for sorting the triangles.
	{
		double y1, y2, y3, SmallestY;//the three y values that the triangle is connected to. uses these to find which one is currently smallest, and put the smallest value into the SmallestY storage.
		int ID;
		bool render;
	};
	double Angle;
	bool Spinning;

	Point PointArray[6];
	Triangle TriangleArray[8];
public:
	Diamond3D();
	void Init(double x, double y, double z);
	void Render(double cameraXPos, double cameraYPos);
	void Update();

	void SetSpinning(bool Spinning) { Diamond3D::Spinning = Spinning; }
};