#pragma once
const int SCREENW = 1920, SCREENH = 1080;//console size
const int LEVELW = 13, LEVELH = 13;//level size (unused)
const int TILEW = 100, TILEH = 100;//standard tile size for terrain
const int FPS = 60;
enum STATE { TITLE, PLAYING, LOST };
enum KEYS { UP, DOWN, LEFT, RIGHT, MOUSE_BUTTON, F_MAP, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, ENTER, SHIFT };

enum RENDERINGVERTICALITY { VERTICAL, HORIZONTAL };//whether the generated image is horizontal or vertical (varies sorting)
enum RENDERINGLAYER {CLOUDLINE, FOUNDATION, BASE, DECOR, NONE};//basic layers in height of level 
						//(necessary despite z axis for when objects are on same z and y axis, but still need one to be atop another (path in the grass). 
						//also necessary in situations where a smaller object is inside a larger object, and is on same z plane (grass bloack atop rock layer of island, for example).
						//CLOUDLINE is the layer underneath the islands, composed of vertical objects like clouds and girders reaching up to the islands. 
						//FOUNDATION  is the layer underneath the grass, that makes up the horizontal outline of the rocky cliffsides of the islands.
						//BASE is the layer of green grass that the player walks on, and forms the non-decorational matrix grid on which players and enemies can walk.
						//DECOR is where stone paths, trees, grass, emeies, and the player reside atop the BASE layer.
						//NONE is to exempt the object from the layer comparison (though I'm not sure if it will work).

enum DIRECTION {NORTH, SOUTH, EAST, WEST};//four directions for various coding purposes