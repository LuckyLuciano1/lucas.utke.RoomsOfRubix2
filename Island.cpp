#include "Globals.h"
#include "Island.h"
#include "Grass.h"
#include "DecorBox.h"
#include "DecorCircle.h"
#include "DecorFourSidedPolygon.h"
#include "DecorGirder.h"
#include "DecorPath.h"
#include "IslandUnderside.h"
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;

Island::Island() {}

void Island::Destroy() {}

void Island::Init(int ID, double IslandX, double IslandY, int IslandTopBoundX, int IslandTopBoundY)
{
	Island::ID = ID;

	Island::IslandX = IslandX;
	Island::IslandY = IslandY;
	Island::IslandTopBoundX = IslandTopBoundX;
	Island::IslandTopBoundY = IslandTopBoundY;

	bool OnScreen = false;

	int BorderSize = 5;//"rims" of all boxes
	int BrickHeight = 30;//height of bricks that form the underside and front of island (as well as front facing width)

	DecorBox *BaseTop = new DecorBox();//generating top section of island
	BaseTop->Init(IslandX - BorderSize, IslandY - BorderSize, 0, IslandTopBoundX + BorderSize * 2, IslandTopBoundY + BorderSize * 2, 174, 178, 95);

	BaseTop->SetVerticality(HORIZONTAL);
	BaseTop->SetLayer(BASE);
	BaseTop->EnableBorder(BorderSize, 137, 129, 126);
	AllObjectsList.push_back(BaseTop);

	DecorBox *BaseFront = new DecorBox();
	BaseFront->Init(IslandX - BorderSize, IslandY + IslandTopBoundY + BorderSize - BrickHeight, BrickHeight, IslandTopBoundX + BorderSize * 2, BrickHeight, 124, 119, 116);
	BaseFront->SetLayer(BASE);
	BaseFront->EnableBorder(BorderSize, 102, 96, 93);
	AllObjectsList.push_back(BaseFront);

	//underside creation
	IslandUnderside *Underside = new IslandUnderside();
	Underside->Init(IslandX, IslandY, IslandTopBoundX, IslandTopBoundY);
	Underside->SetLayer(CLOUDLINE);
	AllObjectsList.push_back(Underside);
	

	//insert later microenvironment creation here
	
	//grass class needs upgrading!
	for (int a = 0; a < (IslandTopBoundX/20); a++) {
		int GrassBoundX = rand() % 10 + 10;
		int GrassBoundY = rand() % 20 + GrassBoundX;
		//Grass *grass = new Grass();
		//grass->Init((rand() % (IslandTopBoundX - GrassBoundX*2)) + IslandX + GrassBoundX/2, rand() % IslandTopBoundY + IslandY, 0, GrassBoundX, GrassBoundY, 174, 178, 95, 221, 94, 23);
		//AllObjectsList.push_back(grass);
	}

	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)//marks all created objects within island Init with island's ID, for level sorting purposes.
	{
		(*iter)->SetClusterID(ID);
	}
}