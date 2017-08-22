#pragma once

#include <iostream>
#include "Globals.h"
#include "Object.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>

using namespace std;

class IslandUnderside : public Object
{
private:
	vector<Object*> AllObjectsList;//list that keeps track of all objects within each IslandUnderside. Used for render, updating, collision, etc.
	vector<Object*>::iterator iter;

public:

	IslandUnderside();
	void virtual Destroy();
	void Init(double IslandX, double IslandY, double IslandBoundX, double IslandBoundY);

	//==============================================
	//OBJECT LIST MANAGEMENT
	//==============================================
	void Update();
	void Render(double cameraXPos, double cameraYPos);
	void ObjectDeletion();

	//==============================================
	//MISC
	//==============================================
};
