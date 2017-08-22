#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"
#include <vector>
using namespace std;

class Object
{
protected:
	bool Collidable;//whether an object is supposed to collide with other objects (for example, being hit grants the player a second or two immunity from colliding with enemy weapons).
	bool MatrixCollidable;//whether an objects is supposed to collide with the CollisionMatrix within Level (for example, the player uses a grapple hook, passing through the collidable gap between islands).

	bool sortable;//whether an object is capable of being sorted in a vector/list
	int verticality;//basic grouping that object is in (TILE, UNIT, DECOR, etc.)
	bool valid;//determines whether object should be deleted or not.
	int Layer;//necessary for rendering/sorting within the Level class. Layer on which the object in question is.

	double x;
	double y;
	double z;//z coordinate adds/subtracts from y coordinate. used for synthetic depth (game isn't actually 3D!)

	double velX;
	double velY;
	double velZ;

	double dirX;
	double dirY;
	double dirZ;

	double boundX;//width and height of object within game.
	double boundY;

	int ClusterID;//bit complicated. essentially, levels are arranged by Island (and a few other things), and each are assigned a number to keep track of what's what. Objects require this number to be stored, to make it easier to remove objects from lists based on their respective island.

public:

	Object();
	void virtual Destroy();
	void Init(double x, double y, double z);

	void EnableSorting(double boundX, double boundY) { Object::boundX = boundX, Object::boundY = boundY, Object::sortable = true; }
	bool GetSortable() { return sortable; }

	//==============================================
	//CLASS MANAGEMENT
	//==============================================
	void virtual Update();
	void virtual Render(double cameraXPos, double cameraYPos);

	//==============================================
	//COORDINATE ACCESS/MODIFICATION
	//==============================================
	double GetX() { return x; }
	double GetY() { return y; }
	double GetZ() { return z; }

	void SetX(double x) { Object::x = x; }
	void SetY(double y) { Object::y = y; }
	void SetZ(double z) { Object::z = z; }

	double GetDirX() { return dirX; }
	double GetDirY() { return dirY; }
	double GetDirZ() { return dirZ; }

	void SetDirX(double dirX) { Object::dirX = dirX; }
	void SetDirY(double dirY) { Object::dirY = dirY; }
	void SetDirZ(double dirZ) { Object::dirZ = dirZ; }

	double GetVelX() { return velX; }
	double GetVelY() { return velY; }
	double GetVelZ() { return velZ; }

	void SetVelX(double velX) { Object::velX = velX; }
	void SetVelY(double velY) { Object::velY = velY; }
	void SetVelZ(double velZ) { Object::velZ = velZ; }

	//==============================================
	//SIZE ACCESS
	//==============================================
	double GetBoundX() { return boundX; }
	double GetBoundY() { return boundY; }

	void SetBoundX(double boundX) { Object::boundX = boundX; }
	void SetBoundY(double boundY) { Object::boundY = boundY; }

	//==============================================
	//DELETION ACCESS/MODIFICATION
	//==============================================
	bool GetValid() { return valid; }
	void SetValid(bool valid) { Object::valid = valid; }

	//==============================================
	//OTHER
	//==============================================
	int GetVerticality() { return verticality; }//for sorting purposes, so that objects are rendered in the correct order.
	void SetVerticality(int verticality) { Object::verticality = verticality; }

	int GetClusterID() { return ClusterID; }
	void SetClusterID(int ClusterID) { Object::ClusterID = ClusterID; }

	int GetLayer() { return Layer; }
	void SetLayer(int Layer) { Object::Layer = Layer; }

	int GetCollidable() { return Collidable; }
	void SetCollidable(int Collidable) { Object::Collidable = Collidable; }

	int GetMatrixCollidable() { return MatrixCollidable; }
	void SetMatrixCollidable(int MatrixCollidable) { Object::MatrixCollidable = MatrixCollidable; }
};