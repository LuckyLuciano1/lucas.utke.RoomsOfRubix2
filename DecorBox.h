#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include <vector>
using namespace std;

class DecorBox : public Object
{
private:
	int R;//color of base
	int G;
	int B;

	bool Border;
	int BorderThickness;//necessary variables for Border
	int BorderR;
	int BorderG;
	int BorderB;

public:
	DecorBox();
	void Init(double x, double y, double z, double boundX, double boundY, int R, int G, int B);
	void Update();
	void Render(double cameraXPos, double cameraYPos);

	void EnableBorder(int Thickness, int R, int G, int B) { Border = true, BorderThickness = Thickness, BorderR = R, BorderG = G, BorderB = B; }
};