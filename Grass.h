#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include "GrassJoint.h"
#include <vector>
using namespace std;

class Grass : public Object
{
private:
	vector<GrassJoint *> AllObjectsList;//holds joints
	vector<GrassJoint *>::iterator iter;
public:
	Grass();
	void Init(double x, double y, double z, double boundX, double boundY, double StartR, double StartG, double StartB, double EndR, double EndG, double EndB);
	void Render(double cameraXPos, double cameraYPos);
	void Update();
};