#include "Globals.h"
#include "IslandUnderside.h"
#include "DecorBox.h"
#include "DecorGirder.h"
#include "DecorFourSidedPolygon.h"
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;

IslandUnderside::IslandUnderside() {}

void IslandUnderside::Destroy() {}

void IslandUnderside::Init(double IslandX, double IslandY, double IslandBoundX, double IslandBoundY)
{
	int UndersideDepth = 600;//height/depth of tower that island is atop
	int BrickHeight = 30;//these are the same values/variable names used in the Island class within Init(). no reason to pass them over as parameters, though, as I don't plan on changing the values.
	Object::Init(IslandX, IslandY+IslandBoundY - UndersideDepth - BrickHeight, UndersideDepth);
	EnableSorting(IslandBoundX, UndersideDepth + BrickHeight);

	int BorderSize = 5;

	
	int BrickNum = IslandBoundX/BrickHeight - 1;//number of bricks that form each layer of tower

	int BrickLength = BrickHeight*BrickNum;//longways of brick

	int CenteringX = (IslandBoundX - BrickLength) / 2;//little bit added on to center the "jenga" tower underneath the base
	int CenteringY = (IslandBoundX - BrickLength) / 2;//(its a copy of above, but good for consistency's sake)

	bool counter = true;//tracking previous brick arrangement in order to swap properly
	for (int z = UndersideDepth; z > BrickHeight; z -= BrickHeight) {
		//CenteringX += (rand() % (BrickHeight * 2) - BrickHeight);

		if (counter) {//front facing bricks
			for (int x = 0; x < BrickNum*BrickHeight; x += BrickHeight) {

				int DispY = rand() % 40 - 20;

				DecorBox *BrickTop = new DecorBox();
				DecorBox *BrickFront = new DecorBox();

				BrickTop->Init(IslandX + x + CenteringX, IslandY + CenteringY + DispY, z, BrickHeight, BrickLength, 163 - (z / (BrickHeight / 4)), 153 - (z / (BrickHeight / 4)), 149 - (z / (BrickHeight / 4)));
				BrickFront->Init(IslandX + x + CenteringX, IslandY + BrickLength + CenteringY + DispY, z, BrickHeight, BrickHeight, 124 - (z / (BrickHeight / 4)), 119 - (z / (BrickHeight / 4)), 116 - (z / (BrickHeight / 4)));

				BrickTop->EnableBorder(BorderSize, 137 - (z / (BrickHeight / 4)), 129 - (z / (BrickHeight / 4)), 126 - (z / (BrickHeight / 4)));
				BrickFront->EnableBorder(BorderSize, 102 - (z / (BrickHeight / 4)), 96 - (z / (BrickHeight / 4)), 93 - (z / (BrickHeight / 4)));

				AllObjectsList.push_back(BrickTop);
				AllObjectsList.push_back(BrickFront);

				counter = false;
			}
		}
		else if (!counter) {//side facing bricks
			for (int y = 0; y < BrickNum*BrickHeight; y += BrickHeight) {

				int DispX = rand() % 40 - 20;

				DecorBox *BrickTop = new DecorBox();
				DecorBox *BrickFront = new DecorBox();

				BrickTop->Init(IslandX + CenteringX + DispX, IslandY + y + CenteringY, z, BrickLength, BrickHeight, 163 - (z / (BrickHeight / 4)), 153 - (z / (BrickHeight / 4)), 149 - (z / (BrickHeight / 4)));
				BrickFront->Init(IslandX + CenteringX + DispX, IslandY + y + CenteringY + BrickHeight, z, BrickLength, BrickHeight, 124 - (z / (BrickHeight / 4)), 119 - (z / (BrickHeight / 4)), 116 - (z / (BrickHeight / 4)));

				BrickTop->EnableBorder(BorderSize, 137 - (z / (BrickHeight / 4)), 129 - (z / (BrickHeight / 4)), 126 - (z / (BrickHeight / 4)));
				BrickFront->EnableBorder(BorderSize, 102 - (z / (BrickHeight / 4)), 96 - (z / (BrickHeight / 4)), 93 - (z / (BrickHeight / 4)));

				AllObjectsList.push_back(BrickTop);
				AllObjectsList.push_back(BrickFront);

				counter = true;
			}
		}
	}
}

//===========================================================================================================================================================================================================================
//OBJECT LIST MANAGEMENT
//===========================================================================================================================================================================================================================

void IslandUnderside::Update()
{
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
		(*iter)->Update();
	}
}

void IslandUnderside::Render(double cameraXPos, double cameraYPos)
{
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
		(*iter)->Render(cameraXPos, cameraYPos);
	}
}

void IslandUnderside::ObjectDeletion()
{
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end();)
	{
		if (!(*iter)->GetValid())
		{
			delete (*iter);
			iter = AllObjectsList.erase(iter);
		}
		else
			iter++;
	}
}