#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include <vector>
using namespace std;

class DecorTriangle : public Object
{
private:
	int R;//color of base
	int G;
	int B;

	double X1;//the three coordinates necessary to form the triangle
	double Y1;

	double X2;
	double Y2;

	double X3;
	double Y3;

public:
	DecorTriangle();
	void Init(double X1, double Y1, double X2, double Y2, double X3, double Y3, int R, int G, int B);
	void Update();
	void Render(double cameraXPos, double cameraYPos);

	//coordinate modification
	double GetX1() { return X1; }
	double GetY1() { return Y1; }

	void SetX1(double x) { X1 = x; }
	void SetY1(double y) { Y1 = y; }

	double GetX2() { return X2; }
	double GetY2() { return X2; }

	void SetX2(double x) { X2 = x; }
	void SetY2(double y) { X2 = y; }

	double GetX3() { return X3; }
	double GetY3() { return Y3; }

	void SetX3(double x) { X3 = x; }
	void SetY3(double y) { Y3 = y; }

	void ResetPos(int x1, int y1, int x2, int y2, int x3, int y3) { X1 = x1, Y1 = y1, X2 = x2, Y2 = y2, X3 = x3, Y3 = y3; }
};