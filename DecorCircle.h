#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include <vector>
using namespace std;

class DecorCircle : public Object
{
private:
	int R;//color of base
	int G;
	int B;

	double Radius;//size of circle
	bool Shading;//whether circle has shading or not

public:
	DecorCircle();
	void Init(double x, double y, double z, double Radius, int R, int G, int B, bool Shading);
	void Update();
	void Render(double cameraXPos, double cameraYPos);

	bool SetShading(bool Shading) { DecorCircle::Shading = Shading;  }
	
	void SetRadius(double Radius) { DecorCircle::Radius = Radius; }
	double GetRadius() { return Radius; }
};