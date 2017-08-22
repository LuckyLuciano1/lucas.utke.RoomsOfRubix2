#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include <vector>
using namespace std;

class DecorGirder : public Object
{
private:
	int GirderSideWidth;
	int CrossSize;//size of the bars forming the cross
	double CrossBoundX;
	double CrossBoundY;
	int CrossNum;//number of crosses before a horizontal bar.

	int CrossR;//color of crosses within girder
	int CrossG;
	int CrossB;

	int FrameR;//color of outside frame of girder (sides and horizontal bars)
	int FrameG;
	int FrameB;

	vector<Object*> AllObjectsList;
	vector<Object*>::iterator iter;

public:
	DecorGirder();
	void Init(double x, double y, double boundX, double boundY, int GirderSideWidth, int CrossSize, double CrossBoundX, double CrossBoundY, int CrossNum, int CrossR, int CrossG, int CrossB, int FrameR, int FrameG, int FrameB);
	void Update();
	void Render(double cameraXPos, double cameraYPos);
};