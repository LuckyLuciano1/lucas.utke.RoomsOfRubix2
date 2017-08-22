#include "DecorBox.h"

DecorBox::DecorBox() {}//DecorBox is an object with no collision that renders a simple box

void DecorBox::Init(double x, double y, double z, double boundX, double boundY, int R, int G, int B)
{
	Object::Init(x, y, z);
	EnableSorting(boundX, boundY);
	DecorBox::R = R;//color of box
	DecorBox::G = G;
	DecorBox::B = B;

	BorderR = 0;
	BorderG = 0;
	BorderB = 0;

	BorderThickness = 0;
	Border = false;
}

void DecorBox::Update()
{
	Object::Update();
}

void DecorBox::Render(double cameraXPos, double cameraYPos)
{
	al_draw_filled_rectangle(x + cameraXPos, y + cameraYPos + z, x + boundX + cameraXPos, y + boundY + cameraYPos + z, al_map_rgb(R, G, B));//base
	
	if (Border)
		al_draw_rectangle(x + (BorderThickness/2) + cameraXPos, y + (BorderThickness / 2) + cameraYPos + z, x + boundX - (BorderThickness / 2) + cameraXPos, y+boundY- (BorderThickness / 2) + cameraYPos + z, al_map_rgb(BorderR, BorderG, BorderB), BorderThickness);
}