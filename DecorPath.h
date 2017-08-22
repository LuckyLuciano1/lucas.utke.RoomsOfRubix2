#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include <vector>
using namespace std;

class DecorPath : public Object
{
private:
	int PathSideWidth;
	int CrossSize;//size of the bars forming the cross
	double CrossBoundX;
	double CrossBoundY;
	int CrossNum;//number of crosses before a horizontal bar.


	vector<Object*> AllObjectsList;
	vector<Object*>::iterator iter;

public:
	DecorPath();
	void Init(double IslandX, double IslandY, int IslandBoundX, int IslandBoundY, int PathFrequency, int PathWideness, int MinimumCircleSize, int CircleSizeRange, int MinimumCircleColor, int CircleColorRange, int CircleAmount, int PathDirection);
	void Update();
	void Render(double cameraXPos, double cameraYPos);
};