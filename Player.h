#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include "Object.h"
#include "Scarf.h"

#include <vector>
using namespace std;

class Player : public Object
{
private:
	enum ACTION {
		IDLE,
		MOVING,
		DASH,
		CHARGE,
		LUNGE
	};//list of all the various animations that the player has
	int Action;//tracks which action is being performed by the main character
	double MouseAngleRadians;//angle of mouse in radians. Used to track which direction the player faces (check flags)

	Scarf *scarf = new Scarf();

	struct Point
	{
		float x, y, z, OrigX, OrigY;
		float dirX, dirY;
		int Vel;
	};

	struct Strand
	{
		Point PointArray[10];
	};
	const size_t StrandLength = 10;
	int StrandLength_int = 10;	

	Strand StrandArray[180];
	int StrandNum = 180;

	double counter;

public:
	Player();
	void Init(double x, double y, double z);
	void Update();
	void Render(double cameraXPos, double cameraYPos);

	//==============================================
	//MOVEMENT
	//==============================================
	void PlayerKeyboard(bool UP, bool DOWN, bool LEFT, bool RIGHT, bool SHIFT);
	void AnimationHandler();//stores what row of animations corresponds to what animation. Can also be expanded to modify specific player characteristics (size, position, velocity, etc).

	//==============================================
	//MOUSEANGLE
	//==============================================
	double GetMouseAngleRadians() { return MouseAngleRadians; }
	void SetMouseAngleRadians(double MouseAngleRadians) { Player::MouseAngleRadians = MouseAngleRadians; }
};