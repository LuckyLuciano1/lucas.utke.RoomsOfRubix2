#include "Player.h"

#define PI 3.14159265
#define DEGREES(x) int((x)/360.0*0xFFFFFF)
#define RADIANS(x) int((x)/2/M_PI*0xFFFFFF)

Player::Player() {}

void Player::Init(double x, double y, double z)
{

	Object::Init(x, y, z);
	EnableSorting(25, 25);

	//TestBox->Init(x, y, z, 50, 50, 5, 255, 255, 255);

	MouseAngleRadians = 0;//temporary value
	velX = 6;
	velY = 6;
	counter = 0;

	float float_x =  x + boundX * sin(360 / StrandNum)*PI / 180;//(boundX / StrandNum);
	float float_y = y + boundY*cos(360/StrandNum)*PI / 180;
	float float_z = 10;

	float float_boundX = boundX;
	float float_boundY = boundY;

	float float_radius = boundX;
	float ratio = (360 / StrandNum);

	for (int a = 0; a < StrandNum; a++) {//setting up PointArray within Strands of StrandArray
		for (int b = 0; b < StrandLength_int; b++) {
			StrandArray[a].PointArray[b] = { 0, 0, float_z*b, float_radius*sin(ratio*a), float_radius*cos(ratio*a), 0, 0, b + 2 };
			//float_radius = boundX + b;
		}
	}
}

void Player::Update()
{
	Object::Update();
	//scarf->Update(x + boundX / 2, y + z, dirX, dirY);

	counter += .03;

	if (dirX == 0 && dirY == 0) {//setting up 'resting position' of Scarf when player/object is in idle state
		dirX = 0;
		dirY = -1;
	}

	for (int a = 0; a < StrandNum; a++) {
		for (int b = 0; b < StrandLength_int; b++) {
			StrandArray[a].PointArray[b].dirX = (((StrandArray[a].PointArray[b].x + StrandArray[a].PointArray[b].dirX) - (x + StrandArray[a].PointArray[b].OrigX + StrandArray[a].PointArray[b].Vel*dirX)) / StrandArray[a].PointArray[b].Vel) + sin(counter);
			StrandArray[a].PointArray[b].dirY = (((StrandArray[a].PointArray[b].y + StrandArray[a].PointArray[b].dirY) - (y + StrandArray[a].PointArray[b].OrigY + StrandArray[a].PointArray[b].Vel*-dirY)) / StrandArray[a].PointArray[b].Vel);// +sin(counter);
			StrandArray[a].PointArray[b].x -= StrandArray[a].PointArray[b].dirX;
			StrandArray[a].PointArray[b].y -= StrandArray[a].PointArray[b].dirY;
		}
	}
}

void Player::Render(double cameraXPos, double cameraYPos)
{
	al_draw_rectangle(x + cameraXPos, y + z + cameraYPos, x + cameraXPos + boundX, y + z + cameraYPos + boundY, al_map_rgb(255, 255, 255), 2);
	//scarf->Render(cameraXPos, cameraYPos);

	for (int a = 0; a < StrandNum; a++) {//adding in cameraposition and z axis
		for (int b = 0; b < StrandLength_int; b++) {
			StrandArray[a].PointArray[b].x += cameraXPos;
			StrandArray[a].PointArray[b].y += cameraYPos + StrandArray[a].PointArray[b].z;
		}
	}

	for (int a = 0; a < StrandNum; a++) {

		/*Point HorizPointArray[5];//StrandNum
		for (int b = 0; b < StrandNum; b++) {//setting up HorizPointArray
			HorizPointArray[b] = StrandArray[b].PointArray[a];
		}
		al_draw_ribbon((float*)HorizPointArray, sizeof(Point), al_map_rgb(255 - a*10, 0, 0), 10, StrandNum);*/
		
		//al_draw_ribbon((float*)StrandArray[a].PointArray, sizeof(Point), al_map_rgb(255 - a, 0, 0), 10, StrandLength);

		for (int b = 0; b < StrandLength; b++) {
			//al_draw_circle(StrandArray[a].PointArray[b].x, StrandArray[a].PointArray[b].y, 2, al_map_rgb(255, 255, 255), 1);
		}
	}

	for (int a = 0; a < StrandNum; a++) {//retracting cameraposition and z axis
		for (int b = 0; b < StrandLength_int; b++) {
			StrandArray[a].PointArray[b].x -= cameraXPos;
			StrandArray[a].PointArray[b].y -= cameraYPos + StrandArray[a].PointArray[b].z;
		}
	}
}

void Player::PlayerKeyboard(bool UP, bool DOWN, bool LEFT, bool RIGHT, bool SHIFT)
{
	if (UP) {//player movement
		Action = MOVING;
		dirY = -1;
		AnimationHandler();
	}
	else if (DOWN) {
		Action = MOVING;
		dirY = 1;
		AnimationHandler();
	}
	else {
		Action = IDLE;
		dirY = 0;
		AnimationHandler();
	}

	if (LEFT) {
		Action = MOVING;
		dirX = -1;
		AnimationHandler();
	}
	else if (RIGHT) {
		Action = MOVING;
		dirX = 1;
		AnimationHandler();
	}
	else {
		Action = IDLE;
		dirX = 0;
		AnimationHandler();
	}
}

//sets up the various variables that come alongside the Actionstates. called whenever Action is changed
void Player::AnimationHandler()
{
	if (Action == IDLE) {

	}
	else if (Action == MOVING) {

	}
	else if (Action == CHARGE) {

	}
}