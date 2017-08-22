#include "Grass.h"
#include "GrassJoint.h"

Grass::Grass() {}

void Grass::Init(double x, double y, double z, double boundX, double boundY, double StartR, double StartG, double StartB, double EndR, double EndG, double EndB)
{
	Object::Init(x, y - boundY, z);//does not collide or use images
	EnableSorting(boundX, -boundY);

	double R = (EndR - StartR) / boundY;
	double G = (EndG - StartG) / boundY;
	double B = (EndB - StartB) / boundY;

	double ChangeRatio = boundX / boundY;

	int counter = rand() % 1000;
	for (double a = 0; a < boundY; a++) {
		GrassJoint *joint = new GrassJoint();
		joint->Init(a, x + ChangeRatio*a/2, y - a, x + boundX - ChangeRatio*a/2, y - a, StartR + R*a, StartG + G*a, StartB + B*a, counter);
		AllObjectsList.push_back(joint);
	}

}

void Grass::Render(double cameraXPos, double cameraYPos)
{
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
		(*iter)->Render(cameraXPos, cameraYPos);
	}
}

void Grass::Update() {
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
		(*iter)->Update();
	}
}