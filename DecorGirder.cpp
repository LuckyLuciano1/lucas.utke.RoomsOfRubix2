#include "DecorGirder.h"
#include "DecorBox.h"
#include "DecorFourSidedPolygon.h"

DecorGirder::DecorGirder() {}//DecorGirder is an object with no collision that renders a four sided polygon through the use of two triangles

void DecorGirder::Init(double x, double y, double boundX, double boundY, int GirderSideWidth, int CrossSize, double CrossBoundX, double CrossBoundY, int CrossNum, int CrossR, int CrossG, int CrossB, int FrameR, int FrameG, int FrameB)
{

	Object::Init(x, y, z);
	EnableSorting(boundX, boundY);

	DecorGirder::GirderSideWidth = GirderSideWidth;
	DecorGirder::CrossSize = CrossSize;
	DecorGirder::CrossBoundX = CrossBoundX;
	DecorGirder::CrossBoundY = CrossBoundY;

	DecorGirder::CrossR = CrossR;
	DecorGirder::CrossG = CrossG;
	DecorGirder::CrossB = CrossB;

	DecorGirder::FrameR = FrameR;
	DecorGirder::FrameG = FrameG;
	DecorGirder::FrameB = FrameB;

	//cross (and horizontal bar)generation
	int counter = 0;
	for (int a = 0; a < boundY - CrossBoundY; a += CrossBoundY) {//increments by cross size
		counter++;
		//crosses are two parallelograms, so need to be a foursided polygon class.
		DecorFourSidedPolygon *LeftCross = new DecorFourSidedPolygon();
		DecorFourSidedPolygon *RightCross = new DecorFourSidedPolygon();

		LeftCross->Init(
			x + GirderSideWidth,
			y + a,
			x + GirderSideWidth,
			y + a + CrossSize,
			x + CrossBoundX + GirderSideWidth,
			y + a + CrossBoundY - CrossSize,
			x + CrossBoundX + GirderSideWidth,
			y + a + CrossBoundY,
			CrossR, CrossG, CrossB);
		RightCross->Init(
			x + GirderSideWidth,
			y + a + CrossBoundY - CrossSize,
			x + GirderSideWidth,
			y + a + CrossBoundY,
			x + CrossBoundX + GirderSideWidth,
			y + a,
			x + CrossBoundX + GirderSideWidth,
			y + a + CrossSize,
			CrossR, CrossG, CrossB);
		
		AllObjectsList.push_back(LeftCross);
		AllObjectsList.push_back(RightCross);

		if (counter == CrossNum) {//generating horizontal number when enough Crosses have been generated to match CrossNum
			DecorBox *HorizBar = new DecorBox();
			HorizBar->Init(x + GirderSideWidth, y + a + CrossBoundY, 0, CrossBoundX, GirderSideWidth, FrameR, FrameG, FrameB);
			AllObjectsList.push_back(HorizBar);
			a += GirderSideWidth;
			counter = 0;
		}
	}

	//side generation
	DecorBox *LeftSide = new DecorBox();
	DecorBox *RightSide = new DecorBox();

	LeftSide->Init(x, y, 0, GirderSideWidth, boundY, FrameR, FrameG, FrameB);
	RightSide->Init(x + CrossBoundX + GirderSideWidth, y, 0, GirderSideWidth, boundY, FrameR, FrameG, FrameB);

	AllObjectsList.push_back(LeftSide);
	AllObjectsList.push_back(RightSide);

}

void DecorGirder::Update()
{
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
		(*iter)->Update();
	}
}

void DecorGirder::Render(double cameraXPos, double cameraYPos)
{
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
		(*iter)->Render(cameraXPos, cameraYPos);
	}
}