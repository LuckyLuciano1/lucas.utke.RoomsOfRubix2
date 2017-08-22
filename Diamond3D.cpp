#include "Diamond3D.h"
#include "math.h"

#define PI 3.14159265

Diamond3D::Diamond3D() {}

void Diamond3D::Init(double x, double y, double z)
{
	/*Here's the concept:
	this class holds a series of x/y/z points within a data structure.
	these points are used within eight different triangles, in order to create an eight sided diamond.
	these points are displaced by a 'rotation' variable with a circle being viewed at a 45 degree angle (the ingame angle), which will be seen as an ellipses.
	*/
	EnableSorting(20, 40);
	Object::Init(x + boundX, y, z);
	Angle = 0;
	Spinning = true;

	PointArray[0] = { 0, 0, 0, 0, 0, 0 };
	PointArray[1] = { -10, 0, 20, -10, 0, 20 };
	PointArray[2] = { 0, -10, 20, 0, -10, 20 };
	PointArray[3] = { 0, 10, 20, 0, 10, 20 };
	PointArray[4] = { 10, 0, 20, 10, 0, 20 };
	PointArray[5] = { 0, 0, 40, 0, 0, 40 };

	TriangleArray[0] = { PointArray[5].y, PointArray[1].y, PointArray[3].y, 0, 0, true };//FUL
	TriangleArray[1] = { PointArray[5].y, PointArray[4].y, PointArray[3].y, 0, 1, true };//FUR
	TriangleArray[2] = { PointArray[0].y, PointArray[1].y, PointArray[3].y, 0, 2, true };//FLL
	TriangleArray[3] = { PointArray[0].y, PointArray[4].y, PointArray[3].y, 0, 3, true };//FLR
	TriangleArray[4] = { PointArray[5].y, PointArray[1].y, PointArray[2].y, 0, 4, true };//BUL
	TriangleArray[5] = { PointArray[5].y, PointArray[4].y, PointArray[2].y, 0, 5, true };//BUR
	TriangleArray[6] = { PointArray[0].y, PointArray[1].y, PointArray[2].y, 0, 6, true };//BLL
	TriangleArray[7] = { PointArray[0].y, PointArray[4].y, PointArray[2].y, 0, 7, true };//BLR
}



void Diamond3D::Update() {
	if (Spinning)
		Angle += 1;
	if (Angle >= 360)
		Angle -= 360;
	for (int a = 0; a < 6; a++) {
		double Hyp = sqrt(PointArray[a].OrigX*PointArray[a].OrigX + PointArray[a].OrigY*PointArray[a].OrigY);
		double Theta = atan2(PointArray[a].OrigY, PointArray[a].OrigX) * 180 / PI;//angle of original position

		PointArray[a].x = Hyp*cos((Angle + Theta)*PI / 180);
		PointArray[a].y = Hyp*sin((Angle + Theta)*PI / 180);

		//cout << PointArray[a].x << ", " << PointArray[a].y << ", ";
	}
	//cout << endl;

	//updating Triangle Array coordinates
	TriangleArray[0].y1 = PointArray[5].y, TriangleArray[0].y2 = PointArray[1].y, TriangleArray[0].y3 = PointArray[3].y;
	TriangleArray[1].y1 = PointArray[5].y, TriangleArray[1].y2 = PointArray[4].y, TriangleArray[1].y3 = PointArray[3].y;
	TriangleArray[2].y1 = PointArray[0].y, TriangleArray[2].y2 = PointArray[1].y, TriangleArray[2].y3 = PointArray[3].y;
	TriangleArray[3].y1 = PointArray[0].y, TriangleArray[3].y2 = PointArray[4].y, TriangleArray[3].y3 = PointArray[3].y;
	TriangleArray[4].y1 = PointArray[5].y, TriangleArray[4].y2 = PointArray[1].y, TriangleArray[4].y3 = PointArray[2].y;
	TriangleArray[5].y1 = PointArray[5].y, TriangleArray[5].y2 = PointArray[4].y, TriangleArray[5].y3 = PointArray[2].y;
	TriangleArray[6].y1 = PointArray[0].y, TriangleArray[6].y2 = PointArray[1].y, TriangleArray[6].y3 = PointArray[2].y;
	TriangleArray[7].y1 = PointArray[0].y, TriangleArray[7].y2 = PointArray[4].y, TriangleArray[7].y3 = PointArray[2].y;

	//finding the smallest y point of each triangle within TriangleArray
	for (int a = 0; a < 8; a++) {
		if (TriangleArray[a].y1 < TriangleArray[a].y2 && TriangleArray[a].y1 < TriangleArray[a].y3)
			TriangleArray[a].SmallestY = TriangleArray[a].y1;
		if (TriangleArray[a].y2 < TriangleArray[a].y1 && TriangleArray[a].y2 < TriangleArray[a].y3)
			TriangleArray[a].SmallestY = TriangleArray[a].y2;
		if (TriangleArray[a].y3 < TriangleArray[a].y2 && TriangleArray[a].y3 < TriangleArray[a].y1)
			TriangleArray[a].SmallestY = TriangleArray[a].y3;
	}

	for (int a = 0; a < 6; a++) {
		//cout << "(" << PointArray[a].x << ", " << PointArray[a].y << ", " << PointArray[a].z << ")" << endl;
		//al_draw_circle(PointArray[SmallestTriangleY_ID].x + cameraXPos + x, PointArray[SmallestTriangleY_ID].y + PointArray[SmallestTriangleY_ID].z + cameraYPos + y + z, 2, al_map_rgb(255, 0, 0), 1);
	}
	//cout << endl;

	for (int a = 0; a < 8; a++) {
		//cout << "(" << TriangleArray[a].y1 << ", " << TriangleArray[a].y2 << ", " << TriangleArray[a].y3 << ")" << endl;
	}
}



void Diamond3D::Render(double cameraXPos, double cameraYPos)
{
	for (int a = 0; a < 8; a++) {//drawing each triangle
		double SmallestY = 0;
		int SmallestTriangleY_ID = 0;

		for (int b = 0; b < 8; b++) {
			if (TriangleArray[b].SmallestY <= SmallestY && TriangleArray[b].render) {//finding Smallest y value of all the triangles in TriangleArray, then the next smallest, then the next...
				SmallestY = TriangleArray[b].SmallestY;
				SmallestTriangleY_ID = TriangleArray[b].ID;
			}
		}

		if (SmallestTriangleY_ID == 0)
			al_draw_filled_triangle(PointArray[5].x + cameraXPos + x, PointArray[5].y - PointArray[5].z + cameraYPos + y + z, PointArray[1].x + cameraXPos + x, PointArray[1].y - PointArray[1].z + cameraYPos + y + z, PointArray[3].x + cameraXPos + x, PointArray[3].y - PointArray[3].z + cameraYPos + y + z, al_map_rgb(255, 255, 255));//FUL
		if (SmallestTriangleY_ID == 1)
			al_draw_filled_triangle(PointArray[5].x + cameraXPos + x, PointArray[5].y - PointArray[5].z + cameraYPos + y + z, PointArray[4].x + cameraXPos + x, PointArray[4].y - PointArray[4].z + cameraYPos + y + z, PointArray[3].x + cameraXPos + x, PointArray[3].y - PointArray[3].z + cameraYPos + y + z, al_map_rgb(0, 0, 0));//FUR
		if (SmallestTriangleY_ID == 2)
			al_draw_filled_triangle(PointArray[0].x + cameraXPos + x, PointArray[0].y - PointArray[0].z + cameraYPos + y + z, PointArray[1].x + cameraXPos + x, PointArray[1].y - PointArray[1].z + cameraYPos + y + z, PointArray[3].x + cameraXPos + x, PointArray[3].y - PointArray[3].z + cameraYPos + y + z, al_map_rgb(0, 255, 0));//FLL
		if (SmallestTriangleY_ID == 3)
			al_draw_filled_triangle(PointArray[0].x + cameraXPos + x, PointArray[0].y - PointArray[0].z + cameraYPos + y + z, PointArray[4].x + cameraXPos + x, PointArray[4].y - PointArray[4].z + cameraYPos + y + z, PointArray[3].x + cameraXPos + x, PointArray[3].y - PointArray[3].z + cameraYPos + y + z, al_map_rgb(255, 255, 0));//FLR

		if (SmallestTriangleY_ID == 4)
			al_draw_filled_triangle(PointArray[5].x + cameraXPos + x, PointArray[5].y - PointArray[5].z + cameraYPos + y + z, PointArray[1].x + cameraXPos + x, PointArray[1].y - PointArray[1].z + cameraYPos + y + z, PointArray[2].x + cameraXPos + x, PointArray[2].y - PointArray[2].z + cameraYPos + y + z, al_map_rgb(0, 0, 0));//BUL
		if (SmallestTriangleY_ID == 5)
			al_draw_filled_triangle(PointArray[5].x + cameraXPos + x, PointArray[5].y - PointArray[5].z + cameraYPos + y + z, PointArray[4].x + cameraXPos + x, PointArray[4].y - PointArray[4].z + cameraYPos + y + z, PointArray[2].x + cameraXPos + x, PointArray[2].y - PointArray[2].z + cameraYPos + y + z, al_map_rgb(255, 255, 255));//BUR
		if (SmallestTriangleY_ID == 6)
			al_draw_filled_triangle(PointArray[0].x + cameraXPos + x, PointArray[0].y - PointArray[0].z + cameraYPos + y + z, PointArray[1].x + cameraXPos + x, PointArray[1].y - PointArray[1].z + cameraYPos + y + z, PointArray[2].x + cameraXPos + x, PointArray[2].y - PointArray[2].z + cameraYPos + y + z, al_map_rgb(255, 0, 255));//BLL
		if (SmallestTriangleY_ID == 7)
			al_draw_filled_triangle(PointArray[0].x + cameraXPos + x, PointArray[0].y - PointArray[0].z + cameraYPos + y + z, PointArray[4].x + cameraXPos + x, PointArray[4].y - PointArray[4].z + cameraYPos + y + z, PointArray[2].x + cameraXPos + x, PointArray[2].y - PointArray[2].z + cameraYPos + y + z, al_map_rgb(255, 0, 0));//BLR

		TriangleArray[SmallestTriangleY_ID].render = false;//clearing Smallest Y from now drawn TriangleArray value, so that next SmallestY is drawn next
	}

	for (int a = 0; a < 8; a++) {//resetting ability to be drawn for the the next render cycle
		TriangleArray[a].render = true;
	}

	for (int a = 0; a < 6; a++) {//indicating positions of points via a circle
		//al_draw_circle(PointArray[a].x + cameraXPos + x, PointArray[a].y + PointArray[a].z + cameraYPos + y + z, 2, al_map_rgb(255, 0, 0), 1);
	}

}

