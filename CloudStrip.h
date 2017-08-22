#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "DecorCircle.h"
#include "DecorBox.h"
#include "Object.h"
#include <vector>
using namespace std;

class CloudStrip : public Object
{
private:
	int R;//color of base
	int G;
	int B;

	DecorBox *CloudBottom = new DecorBox;//needs to be seperate from vector due to the vectors need to use the commands GetRadius(), and as a result is the decorcircle class type, and not object class type

	vector<DecorCircle*> AllObjectsList;
	vector<DecorCircle*>::iterator iter;

public:
	CloudStrip();
	void Init(double x, double y, double z, double boundX, int RadiusRange, int RadiusMin, double velX, int R, int G, int B);
	void Update();
	void Render(double cameraXPos, double cameraYPos);
};