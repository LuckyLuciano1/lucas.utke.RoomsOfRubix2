#include "DecorPath.h"
#include "DecorCircle.h"
#include "DecorFourSidedPolygon.h"

DecorPath::DecorPath() {}//DecorPath is an object with no collision that renders a four sided polygon through the use of two triangles

void DecorPath::Init(double IslandX, double IslandY, int IslandBoundX, int IslandBoundY, int PathFrequency, int PathWideness, int MinimumCircleSize, int CircleSizeRange, int MinimumCircleColor, int CircleColorRange, int CircleAmount, int PathDirection)
{

	

	if(PathDirection == NORTH) {
		Object::Init(IslandX+IslandBoundX/2 - PathWideness, IslandY, 0);
		int counter = PathFrequency - 1;
		for (int a = 0; a < IslandBoundY / 2; a++) {
			counter++;
			if (counter == PathFrequency) {//chance of spawning a circle path
				counter = 0;
				for (int b = 0; b < CircleAmount; b++) {
					int CircleRadius = rand() % CircleSizeRange + MinimumCircleSize;

					if (IslandY + IslandBoundY / 2 - a - CircleRadius > IslandY) {//checking whether circle will be beyond bounds of island
						int CircleColor = rand() % CircleColorRange + MinimumCircleColor;

						DecorCircle *PathPiece = new DecorCircle();
						PathPiece->Init(IslandX + IslandBoundX / 2 + (rand() % PathWideness * 2 - PathWideness), IslandY + IslandBoundY / 2 - a, 0, CircleRadius, CircleColor, CircleColor, CircleColor, false);
						AllObjectsList.push_back(PathPiece);
					}
				}
			}
		}
	}
	else if (PathDirection == SOUTH) {
		Object::Init(IslandX + IslandBoundX / 2 - PathWideness, IslandY + IslandBoundY/2, 0);
		int counter = PathFrequency - 1;
		for (int a = 0; a < IslandBoundY / 2; a++) {
			counter++;
			if (counter == PathFrequency) {
				counter = 0;
				for (int b = 0; b<CircleAmount; b++) {
					int CircleRadius = rand() % CircleSizeRange + MinimumCircleSize;

					if (IslandY + IslandBoundY / 2 + a + CircleRadius < IslandY + IslandBoundY) {//checking whether circle will be beyond bounds of island
						int CircleColor = rand() % CircleColorRange + MinimumCircleColor;

						DecorCircle *PathPiece = new DecorCircle();
						PathPiece->Init(IslandX + IslandBoundX / 2 + (rand() % PathWideness * 2 - PathWideness), IslandY + IslandBoundY / 2 + a, 0, CircleRadius, CircleColor, CircleColor, CircleColor, false);
						AllObjectsList.push_back(PathPiece);
					}
				}
			}
		}
	}
	else if (PathDirection == WEST) {
		Object::Init(IslandX, IslandY+IslandBoundY/2 - PathWideness, 0);
		int counter = PathFrequency - 1;
		for (int a = 0; a < IslandBoundX / 2; a++) {
			counter++;
			if (counter == PathFrequency) {
				counter = 0;
				for (int b = 0; b<CircleAmount; b++) {
					int CircleRadius = rand() % CircleSizeRange + MinimumCircleSize;

					if (IslandX + IslandBoundX / 2 - a - CircleRadius > IslandX) {//checking whether circle will be beyond bounds of island
						int CircleColor = rand() % CircleColorRange + MinimumCircleColor;

						DecorCircle *PathPiece = new DecorCircle();
						PathPiece->Init(IslandX + IslandBoundX / 2 - a, IslandY + IslandBoundY / 2 + (rand() % PathWideness * 2 - PathWideness), 0, CircleRadius, CircleColor, CircleColor, CircleColor, false);
						AllObjectsList.push_back(PathPiece);
					}
				}
			}
		}
	}
	else if (PathDirection == EAST) {
		Object::Init(IslandX + IslandBoundX / 2 - PathWideness, IslandY + IslandBoundY / 2 - PathWideness, 0);
		int counter = PathFrequency - 1;
		for (int a = 0; a < IslandBoundX / 2; a++) {
			counter++;
			if (counter == PathFrequency) {
				counter = 0;
				for (int b = 0; b<CircleAmount; b++) {
					int CircleRadius = rand() % CircleSizeRange + MinimumCircleSize;

					if (IslandX + IslandBoundX / 2 + a + CircleRadius < IslandX + IslandBoundX) {//checking whether circle will be beyond bounds of island
						int CircleColor = rand() % CircleColorRange + MinimumCircleColor;

						DecorCircle *PathPiece = new DecorCircle();
						PathPiece->Init(IslandX + IslandBoundX / 2 + a, IslandY + IslandBoundY / 2 + (rand() % PathWideness * 2 - PathWideness), 0, CircleRadius, CircleColor, CircleColor, CircleColor, false);
						AllObjectsList.push_back(PathPiece);
					}
				}
			}
		}
	}

}

void DecorPath::Update()
{
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
		(*iter)->Update();
	}
}

void DecorPath::Render(double cameraXPos, double cameraYPos)
{
	for (iter = AllObjectsList.begin(); iter != AllObjectsList.end(); ++iter)
	{
		(*iter)->Render(cameraXPos, cameraYPos);
	}
}