#include "Grass.h"
#include "GrassJoint.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

GrassJoint::GrassJoint() {}

void GrassJoint::Init(int JointID, double BegX, double BegY, double EndX, double EndY, double R, double G, double B, int counter)
{
	GrassJoint::JointID = JointID;
	GrassJoint::BegX = BegX;
	GrassJoint::BegY = BegY;
	GrassJoint::EndX = EndX;
	GrassJoint::EndY = EndY;


	GrassJoint::R = R;
	GrassJoint::G = G;
	GrassJoint::B = B;

	GrassJoint::counter = counter;
	WindDirection = -1;
}

void GrassJoint::Update()
{
	counter++;

	Object::Update();
}

void GrassJoint::Render(double cameraXPos, double cameraYPos)
{
	double XDisp = JointID*sin(counter / 100.0) + (JointID*WindDirection);

	al_draw_line(BegX + XDisp + cameraXPos, BegY + cameraYPos, EndX + XDisp + cameraXPos, EndY + cameraYPos, al_map_rgb(R, G, B), 1);
}