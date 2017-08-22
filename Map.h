#pragma once

#include <iostream>
#include "Globals.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <vector>

using namespace std;

class Map
{
private:
	ALLEGRO_FONT *font;
	ALLEGRO_COLOR TileGradient;

	double ForeLayerX;//coordinates of three layers
	double MidLayerX;
	double BackLayerX;

	double ForeLayerY;
	double MidLayerY;
	double BackLayerY;

	int TileSpacing;//spacing between room 'tiles' of map
	int LayerSpacing;//spacing between layers upon expansion
	int MapRadius;//range that map can be stretched to

	int TileBoundX;
	int TileBoundY;

	int TileVel;//speed at which tile layers move

	int TileColor;
	int CurRoomColor;
	double TileTransparency;

	bool FlashIncrease;//decides whther the current room flashing should be going up or down

public:
	Map();
	void virtual Destroy();
	void Init(ALLEGRO_FONT *font);
	void Render(char (&RoomMatrix)[3][3][3], char CurrentRoom);
	void Update();

	void ResetLayers() { //resets coordinates of layers to make sliding animation work when map is repeatedly activated
	ForeLayerX = SCREENW/2;
	MidLayerX = SCREENW/2;
	BackLayerX = SCREENW/2;
	ForeLayerY = SCREENH/2;
	MidLayerY = SCREENH/2;
	BackLayerY = SCREENH/2;	};

	void MouseInteraction(double MouseX, double MouseY);
};