#include "DecorTriangle.h"

DecorTriangle::DecorTriangle() {}//DecorTriangle is an object with no collision that renders a four sided polygon through the use of two triangles

void DecorTriangle::Init(double X1, double Y1, double X2, double Y2, double X3, double Y3, int R, int G, int B)
{

	if (X1 < X2 && X1 < X3)//finding upperleftmost corner
		x = X1;
	if (X2 < X1 && X2 < X3)
		x = X2;
	if (X3 < X1 && X3 < X2)
		x = X3;

	if (Y1 < Y2 && Y1 < Y3)
		y = Y1;
	if (Y2 < Y1 && Y2 < Y3)
		y = Y2;
	if (Y3 < Y1 && Y3 < Y2)
		y = Y3;


	Object::Init(x, y, 0);//defaults to 0 for z (this will mostly be used in ClusterObjects, where the z axis is not relevant).


	DecorTriangle::X1 = X1;//values for the four points necessary
	DecorTriangle::Y1 = Y1;

	DecorTriangle::X2 = X2;
	DecorTriangle::Y2 = Y2;

	DecorTriangle::X3 = X3;
	DecorTriangle::Y3 = Y3;

	DecorTriangle::R = R;//color of polygon
	DecorTriangle::G = G;
	DecorTriangle::B = B;
}

void DecorTriangle::Update()
{
	Object::Update();
}

void DecorTriangle::Render(double cameraXPos, double cameraYPos)
{
	al_draw_filled_triangle(X1 + cameraXPos, Y1 + cameraYPos, X2 + cameraXPos, Y2 + cameraYPos, X3 + cameraXPos, Y3 + cameraYPos, al_map_rgb(R, G, B));
}