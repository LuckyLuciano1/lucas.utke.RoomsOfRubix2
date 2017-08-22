#pragma once

#include <iostream>
#include "Globals.h"
#include "Object.h"
#include <vector>

using namespace std;

class Camera
{
protected:
	double cameraXDir;
	double cameraYDir;

	double cameraXPos;
	double cameraYPos;

	bool paused;

	Object *Target = new Object;

public:
	Camera();
	void virtual Destroy();
	void Init(double cameraXPos, double cameraYPos, Object *Target);

	void Update();//the mins and maxes are ways of stopping the camera from exceeding the boundaries of the level the player is currently on.
	void SetTarget(Object *newTarget) { Target = newTarget; }

	double GetCameraXPos() { return cameraXPos; }
	double GetCameraYPos() { return cameraYPos; }
	double GetCameraXDir() { return cameraXDir; }
	double GetCameraYDir() { return cameraYDir; }

	void SetCameraXPos(double cameraXPos) { Camera::cameraXPos = cameraXPos; }
	void SetCameraYPos(double cameraYPos) { Camera::cameraYPos = cameraYPos; }
	void SetCameraXDir(double cameraXDir) { Camera::cameraXDir = cameraXDir; }
	void SetCameraYDir(double cameraYDir) { Camera::cameraYDir = cameraYDir; }

	void Pause() { paused = true; }
	void Resume() { paused = false; }
};
