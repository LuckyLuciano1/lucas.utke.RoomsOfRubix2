#include "DecorCircle.h"

DecorCircle::DecorCircle() {}//DecorCircle is an object with no collision that renders a simple circle (shading optional).

void DecorCircle::Init(double x, double y, double z, double Radius, int R, int G, int B, bool Shading)
{
	Object::Init(x, y, z);

	DecorCircle::R = R;//color of circle
	DecorCircle::G = G;
	DecorCircle::B = B;

	DecorCircle::Shading = Shading;
	DecorCircle::Radius = Radius;

	Object::EnableSorting(Radius*2, Radius*2);
}

void DecorCircle::Update()
{
	Object::Update();
}

void DecorCircle ::Render(double cameraXPos, double cameraYPos)
{
	//al_draw_rectangle(x - Radius + cameraXPos, y - Radius + cameraYPos, x + Radius + cameraXPos, y + Radius + cameraYPos, al_map_rgb(255, 255, 255), 1);

	if (Shading) {
		al_draw_filled_circle(x + cameraXPos, y + cameraYPos + z, Radius, al_map_rgb(R-20, G-20, B-20));
		al_draw_filled_circle(x+cameraXPos, y+cameraYPos+z-(Radius*.1), Radius*.9, al_map_rgb(R, G, B));
	}
	else
		al_draw_filled_circle(x + cameraXPos, y + cameraYPos + z, Radius, al_map_rgb(R, G, B));
}