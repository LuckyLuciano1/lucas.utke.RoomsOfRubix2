#include "DecorFourSidedPolygon.h"

DecorFourSidedPolygon::DecorFourSidedPolygon() {}//DecorFourSidedPolygon is an object with no collision that renders a four sided polygon through the use of two triangles

void DecorFourSidedPolygon::Init(double UpperLeftX, double UpperLeftY, double LowerLeftX, double LowerLeftY, double UpperRightX, double UpperRightY, double LowerRightX, double LowerRightY, int R, int G, int B)
{

	if (UpperLeftX < LowerLeftX && UpperLeftX < UpperRightX && UpperLeftX < LowerRightX)//finding upperleftmost points to find rudimentary x and y values for Object class. x and y values otherwise unused, unless (possibly) for sorting
		Object::x = UpperLeftX;
	if (LowerLeftX < UpperLeftX && LowerLeftX < UpperRightX && LowerLeftX < LowerRightX)
		Object::x = LowerLeftX;
	if (UpperRightX < LowerLeftX && UpperRightX < UpperLeftX && UpperRightX < LowerRightX)
		Object::x = UpperRightX;
	if (LowerRightX < LowerLeftX && LowerRightX < UpperRightX && LowerRightX < UpperLeftX)
		Object::x = LowerRightX;

	if (UpperLeftY < LowerLeftY && UpperLeftY < UpperRightY && UpperLeftY < LowerRightY)
		Object::y = UpperLeftY;
	if (LowerLeftY < UpperLeftY && LowerLeftY < UpperRightY && LowerLeftY < LowerRightY)
		Object::y = LowerLeftY;
	if (UpperRightY < LowerLeftY && UpperRightY < UpperLeftY && UpperRightY < LowerRightY)
		Object::y = UpperRightY;
	if (LowerRightY < LowerLeftY && LowerRightY < UpperRightY && LowerRightY < UpperLeftY)
		Object::y = LowerRightY;


	Object::Init(x, y, z);


	DecorFourSidedPolygon::UpperLeftX = UpperLeftX;//values for the four points necessary
	DecorFourSidedPolygon::UpperLeftY = UpperLeftY;

	DecorFourSidedPolygon::LowerLeftX = LowerLeftX;
	DecorFourSidedPolygon::LowerLeftY = LowerLeftY;

	DecorFourSidedPolygon::UpperRightX = UpperRightX;
	DecorFourSidedPolygon::UpperRightY = UpperRightY;

	DecorFourSidedPolygon::LowerRightX = LowerRightX;
	DecorFourSidedPolygon::LowerRightY = LowerRightY;

	DecorFourSidedPolygon::R = R;//color of polygon
	DecorFourSidedPolygon::G = G;
	DecorFourSidedPolygon::B = B;
}

void DecorFourSidedPolygon::Update()
{
	Object::Update();
}

void DecorFourSidedPolygon::Render(double cameraXPos, double cameraYPos)
{
	al_draw_filled_triangle(UpperLeftX + cameraXPos, UpperLeftY + cameraYPos, LowerLeftX + cameraXPos, LowerLeftY + cameraYPos, UpperRightX + cameraXPos, UpperRightY + cameraYPos, al_map_rgb(R, G, B));
	al_draw_filled_triangle(LowerLeftX + cameraXPos, LowerLeftY + cameraYPos, UpperRightX + cameraXPos, UpperRightY + cameraYPos, LowerRightX + cameraXPos, LowerRightY + cameraYPos, al_map_rgb(R, G, B));
}