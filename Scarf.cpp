#include "Scarf.h"

Scarf::Scarf() {}

void Scarf::Init(double x, double y, int ScarfWidth, int R, int G, int B)
{
	Scarf::R = R;
	Scarf::G = G;
	Scarf::B = B;
	Scarf::ScarfWidth = ScarfWidth;

	float float_x = x;
	float float_y = y;

	for (int a = 0; a < ScarfPointNum_int; a++) {
		PointArray[a] = {float_x, float_y, 0, 0, a+2};
	}

	counter = 0;
	
}

void Scarf::Update(double x, double y, double dirX, double dirY)
{
	Object::Update();
	counter+=.03;

	if (dirX == 0 && dirY == 0) {//setting up 'resting position' of Scarf when player/object is in idle state
		dirX = 0;
		dirY = -1;
	}

	for (int a = 0; a < ScarfPointNum_int; a++) {
		PointArray[a].dirX = (((PointArray[a].x + PointArray[a].dirX) - (x + PointArray[a].Vel*dirX)) / PointArray[a].Vel) + sin(counter);
		PointArray[a].dirY = (((PointArray[a].y + PointArray[a].dirY) - (y + PointArray[a].Vel*-dirY)) / PointArray[a].Vel) + sin(counter);
		PointArray[a].x -= PointArray[a].dirX;
		PointArray[a].y -= PointArray[a].dirY;
	}
}

void Scarf::Render(double cameraXPos, double cameraYPos) {
	for (int a = 0; a < ScarfPointNum_int; a++) {
		PointArray[a].x += cameraXPos;
		PointArray[a].y += cameraYPos;
	}

	al_draw_ribbon((float*)PointArray, sizeof(Point), al_map_rgb(R, G, B), ScarfWidth, ScarfPointNum);

	for (int a = 0; a < ScarfPointNum_int; a++) {
		PointArray[a].x -= cameraXPos;
		PointArray[a].y -= cameraYPos;
	}
}