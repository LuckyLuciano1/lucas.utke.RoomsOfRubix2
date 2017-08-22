#include "Map.h"
#include "Globals.h"
#include "Level.h"
#include <math.h>
#include <iostream>
#include <algorithm>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>

using namespace std;

Map::Map() {};

void Map::Destroy() {}

void Map::Init(ALLEGRO_FONT *font) {
	Map::font = font;

	TileGradient = al_map_rgba_f(1, 1, 1, 1);
	ForeLayerX = (SCREENW / 2) - TileSpacing / 2;
	MidLayerX = (SCREENW / 2) - TileSpacing / 2;
	BackLayerX = (SCREENW / 2) - TileSpacing / 2;

	ForeLayerY = (SCREENH / 2) - TileSpacing / 2;
	MidLayerY = (SCREENH / 2) - TileSpacing / 2;
	BackLayerY = (SCREENH / 2) - TileSpacing / 2;

	TileColor = 1;
	CurRoomColor = 1;
	FlashIncrease = true;

	TileBoundX = 50;
	TileBoundY = 50;
	TileTransparency = 1;

	TileSpacing = 50;
	LayerSpacing = 25;

	MapRadius = TileSpacing * 3;
	TileVel = 2;
}

void Map::Render(char(&RoomMatrix)[3][3][3], char CurrentRoom) {
	/*
	for (int z = 0; z < 3 * TileSpacing; z += TileSpacing) {
		for (int x = 0; x < 3 * TileSpacing; x += TileSpacing) {
			for (int y = 0; y < 3 * TileSpacing; y += TileSpacing) {
				if (RoomMatrix[x / TileSpacing][y / TileSpacing][z / TileSpacing] == CurrentRoom)//making current room be displayed as special color
					TileGradient = al_map_rgba_f(CurRoomColor, CurRoomColor, CurRoomColor, TileTransparency);
				else
					TileGradient = al_map_rgba_f(TileColor, TileColor, TileColor, TileTransparency);

				if (z == 0) {
					al_draw_tinted_scaled_rotated_bitmap_region(MapImage, 0, 0, TileBoundX, TileBoundY, TileGradient, TileBoundX / 2, TileBoundY / 2, x + BackLayerX, y + BackLayerY, 1, 1, 0, 0);
					al_draw_textf(font, al_map_rgb(150, 150, 150), x + BackLayerX - TileSpacing/3, y + BackLayerY, 0, "%c", RoomMatrix[x / TileSpacing][y / TileSpacing][z / TileSpacing]);
				}
				else if (z == TileSpacing) {
					al_draw_tinted_scaled_rotated_bitmap_region(MapImage, 0, 0, TileBoundX, TileBoundY, TileGradient, TileBoundX / 2, TileBoundY / 2, x + MidLayerX, y + MidLayerY, 1, 1, 0, 0);
					al_draw_textf(font, al_map_rgb(150, 150, 150), x + MidLayerX - TileSpacing / 3, y + MidLayerY, 0, "%c", RoomMatrix[x / TileSpacing][y / TileSpacing][z / TileSpacing]);
				}
				else if (z == TileSpacing * 2) {
					al_draw_tinted_scaled_rotated_bitmap_region(MapImage, 0, 0, TileBoundX, TileBoundY, TileGradient, TileBoundX / 2, TileBoundY / 2, x + ForeLayerX, y + ForeLayerY, 1, 1, 0, 0);
					al_draw_textf(font, al_map_rgb(150, 150, 150), x + ForeLayerX - TileSpacing / 3, y + ForeLayerY, 0, "%c", RoomMatrix[x / TileSpacing][y / TileSpacing][z / TileSpacing]);
				}
				else
					cout << "LETTER DISPLAY ERROR FOR MAP" << endl;
			}
		}
	}
	*/
}

void Map::Update() {
	//MidLayer will not move. Fore and Back layers will mirror each other.

	//map startup and reset
	if (MidLayerX - ForeLayerX < LayerSpacing)
		ForeLayerX--;

	if (ForeLayerY - MidLayerY < LayerSpacing)
		ForeLayerY++;
	
	//Backlayer mirror of ForeLayer
	BackLayerX = MidLayerX + (MidLayerX - ForeLayerX);
	BackLayerY = MidLayerY + (MidLayerY - ForeLayerY);

	//making current room color fluctuate
	int FluctuationVel = 5;
	if (CurRoomColor + FluctuationVel > 255)
		FlashIncrease = false;
	if (CurRoomColor - FluctuationVel < 0)
		FlashIncrease = true;

	if (FlashIncrease)
		CurRoomColor += FluctuationVel;
	else
		CurRoomColor -= FluctuationVel;

}

void Map::MouseInteraction(double MouseX, double MouseY) {

	/*if (MouseX > MidLayerX + TileSpacing / 2 - MapRadius && MouseX < MidLayerX + TileSpacing / 2 + MapRadius &&//if mouse position is within the map range, Forelayer moves in its direction. (BackLayer then mimicks ForeLayer in Update section)
		MouseY > MidLayerY + TileSpacing / 2 - MapRadius && MouseY < MidLayerY + TileSpacing / 2 + MapRadius) {
		if (ForeLayerX < MouseX)
			ForeLayerX += (MouseX - ForeLayerX) / TileVel - TileSpacing / 2;//speed is proportional to distance from mouse
		else
			ForeLayerX -= (ForeLayerX - MouseX) / TileVel + TileSpacing / 2;

		if (ForeLayerY < MouseY)
			ForeLayerY += (MouseY - ForeLayerY) / TileVel - TileSpacing / 2;
		else
			ForeLayerY -= (ForeLayerY - MouseY) / TileVel + TileSpacing / 2;
	}*/
	double hypotenuse = sqrt((MidLayerX - TileSpacing/2 - MouseX)*(MidLayerX - TileSpacing/2 - MouseX) + (MidLayerY - TileSpacing/2 - MouseY)*(MidLayerY - TileSpacing/2 - MouseY));
	if (hypotenuse <= MapRadius) {//hypoetnuse formed between midlayer and mouse positions
		ForeLayerX += (MouseX - ForeLayerX - TileSpacing)/TileVel;
		ForeLayerY += (MouseY - ForeLayerY - TileSpacing)/TileVel;
	}
	else//mouse is outside of MapRadius
	{
		//ForeLayerX += TileVel/(ForeLayerX - ((MapRadius/hypotenuse)*(MouseX - ForeLayerX)));
		//ForeLayerY += TileVel/(ForeLayerY - ((MapRadius/hypotenuse)*(MouseY - ForeLayerY)));
	}
}
