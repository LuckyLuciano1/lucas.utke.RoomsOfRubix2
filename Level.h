#pragma once

#include <iostream>
#include "Globals.h"
#include "Object.h"
#include "Player.h"
#include "Island.h"
#include "Camera.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>

using namespace std;

class Level
{
private:
	bool paused;//tracks whether level is paused or not from opening of menu/map. when paused, stops objects from updating.

	vector<Island *> IslandList;//list that keeps track of all islands within each Level. Used for deciding which island to render, update, etc.
	vector<Island *>::iterator iter;

	vector<Object *> AllObjectsList;//stores objects currently onscreen that need to be rendered/updated
	vector<Object *>::iterator oiter;

	vector<Object *> CollisionObjectsList;//stores objects (characters) that need to be restrained within Island dimensions (and CollisionMatrix)
	vector<Object *>::iterator citer;

	ALLEGRO_FONT *font18;

	Player *player = new Player();
	Camera *camera = new Camera();

	int LevelMinX;//max and minimum bounds of level. used for both cloudstrips and camera rendering
	int LevelMaxX;
	int LevelMinY;
	int LevelMaxY;

	//int IslandMatrix[3][3];
	int SlotSize = 25;
	int CollisionMatrixSize = 240;
	double CollisionMatrix[240][240] = {};//used for containing player (and land enemies) within islands, as well as tracking sizes and locations of islands.

	double StartingX;//position of start for player
	double StartingY;

protected:
	char ID;//means of identifying what Level it is. Every letter in the alphabet, plus '_' (27 Levels, 26 letters).

	int x;//coordinate of Level in 3D matrix. Used to identify what Level should be connected to what.
	int y;
	int z;

	char XAdj;//tracks what other Levels this Level is linked to (via ID). '/' mark means it is next to nothing on that plane.
	char NegXAdj;
	char YAdj;
	char NegYAdj;
	char ZAdj;
	char NegZAdj;

public:

	Level();
	void virtual Destroy();
	void Init(char ID, int x, int y, int z, Player *player, Camera *camera, ALLEGRO_FONT *font18);

	char GetID() { return ID; }
	void SetID(char ID) { Level::ID = ID; }


	//==============================================
	//OBJECT LIST MANAGEMENT
	//==============================================
	void ObjectUpdate();
	void ObjectRender(double cameraXPos, double cameraYPos);
	void ObjectCollision();
	void ObjectDeletion();

	void Pause() { paused = true; }
	void Resume() { paused = false; }

	//==============================================
	//COORDINATE ACCESS/MODIFICATION
	//==============================================
	int GetX() { return x; }
	int GetY() { return y; }
	int GetZ() { return z; }

	void SetX(int x) { Level::x = x; }
	void SetY(int y) { Level::y = y; }
	void SetZ(int z) { Level::z = z; }

	//==============================================
	//ADJACENT LEVEL ACCESS/MODIFICATION
	//==============================================
	char GetXAdj() { return XAdj; }
	char GetNegXAdj() { return NegXAdj; }
	char GetYAdj() { return YAdj; }
	char GetNegYAdj() { return NegYAdj; }
	char GetZAdj() { return ZAdj; }
	char GetNegZAdj() { return NegZAdj; }

	void SetXAdj(char XAdj) { Level::XAdj = XAdj; }
	void SetNegXAdj(char NegXAdj) { Level::NegXAdj = NegXAdj; }
	void SetYAdj(char YAdj) { Level::YAdj = YAdj; }
	void SetNegYAdj(char NegYAdj) { Level::NegYAdj = NegYAdj; }
	void SetZAdj(char ZAdj) { Level::ZAdj = ZAdj; }
	void SetNegZAdj(char NegZAdj) { Level::NegZAdj = NegZAdj; }

	//==============================================
	//SHUFFLING GUIDELINES
	//==============================================
	void Shuffle(int shuffletype);

	void RedClockwise();
	void RedCounterClockwise();

	void WhiteClockwise();
	void WhiteCounterClockwise();

	void BlueClockwise();
	void BlueCounterClockwise();

	void YellowClockwise();
	void YellowCounterClockwise();

	void GreenClockwise();
	void GreenCounterClockwise();

	void OrangeClockwise();
	void OrangeCounterClockwise();

	//==============================================
	//MISC
	//==============================================
	int GetLevelMaxX() { return LevelMaxX; }
	void SetLevelMaxX(int LevelMaxX) { Level::LevelMaxX = LevelMaxX; }
	int GetLevelMinX() { return LevelMinX; }
	void SetLevelMinX(int LevelMinX) { Level::LevelMinX = LevelMinX; }

	int GetLevelMaxY() { return LevelMaxY; }
	void SetLevelMaxY(int LevelMaxY) { Level::LevelMaxY = LevelMaxY; }
	int GetLevelMinY() { return LevelMinX; }
	void SetLevelMinY(int LevelMinY) { Level::LevelMinY = LevelMinY; }

	double GetPlayerX() { return StartingX; }//temporary means of returning thelevel's starting player position to main
	double GetPlayerY() { return StartingY; }
};