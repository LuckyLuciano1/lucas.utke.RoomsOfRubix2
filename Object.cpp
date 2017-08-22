#include "Object.h"
#include <math.h>
#include <iostream>
using namespace std;

Object::Object()
{
	valid = true;
	verticality = VERTICAL;
	sortable = false;
	Layer = DECOR;//defaults to decor because the majority of objects will be on the top layer of the level

	Collidable = true;
	MatrixCollidable = true;

	x = 0;
	y = 0;
	z = 0;

	velX = 1;
	velY = 1;
	velZ = 1;

	dirX = 0;
	dirY = 0;
	dirZ = 0;

	boundX = 0;
	boundY = 0;

	ClusterID = 0;
}

void Object::Destroy() {}

void Object::Init(double x, double y, double z)
{
	Object::x = x;
	Object::y = y;
	Object::z = z;
}

void Object::Update() 
{	
	x += velX*dirX;
	y += velY*dirY;
	z += velZ*dirZ;
}

void Object::Render(double cameraXPos, double cameraYPos)
{
	//al_draw_tinted_scaled_rotated_bitmap_region(image, imageX, imageY, imageboundX, imageboundY, transparency, 0, 0, x + cameraXPos, y + z + cameraYPos, boundX/imageboundX, boundY/imageboundY, angle, FlipHorizontal);
	//cumulative drawing function that should be able to handle all possible drawing commands.

	/* reason for being commented out:
	as of now, objects are essentially clusters of allegro draw commands. 
	This means very little, if not no actual image files are being used. 
	*/
}