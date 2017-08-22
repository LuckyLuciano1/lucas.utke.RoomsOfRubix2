#include "Camera.h"
#include <math.h>
#include <iostream>

using namespace std;

Camera::Camera()
{
	cameraXDir = 0;
	cameraYDir = 0;

	cameraXPos = 0;
	cameraYPos = 0;

	paused = false;
}

void Camera::Destroy() {}

void Camera::Init(double cameraXPos, double cameraYPos, Object *Target) {
	Camera::cameraXPos = cameraXPos;
	Camera::cameraYPos = cameraYPos;
	Camera::Target = Target;
}

void Camera::Update()
{
	if (!paused) {
		cameraXDir = -((cameraXPos + cameraXDir) + ((Target->GetX() + (Target->GetBoundX() / 2) - (SCREENW / 2)) + Target->GetDirX())) / 25;//velocity of camera is dependent on distance from Target
		cameraYDir = -((cameraYPos + cameraYDir) + ((Target->GetY() + (Target->GetBoundY() / 2) - (SCREENH / 2)) + Target->GetDirY())) / 25;

		cameraXPos += cameraXDir;
		cameraYPos += cameraYDir;
	}

	/*old function for camera movement
	if ((cameraXPos - -(object->GetVelX())*(object->GetX() - (SCREENW / 2)) / 100) > 0 && (cameraXPos + SCREENW - -(object->GetVelX())*(object->GetX() - (SCREENW / 2)) / 100) < LEVELW*TILEW)//to stop camera from exceeding mapsize
	cameraXDir = -(object->GetVelX())*(object->GetX() - (SCREENW / 2)) / 100;//velocity of camera is dependent on distance from object
	else
	cameraXDir = 0;

	if ((cameraYPos - -(object->GetVelY())*(object->GetY() - (SCREENH / 2)) / 100) > 0 && (cameraYPos + SCREENW - -(object->GetVelY())*(object->GetY() - (SCREENH / 2)) / 100) < LEVELH*TILEH)
	cameraYDir = -(object->GetVelY())*(object->GetY() - (SCREENH / 2)) / 100;
	else
	cameraYDir = 0;
	*/
}