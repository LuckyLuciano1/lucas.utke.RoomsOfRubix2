#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_color.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include <list>
#include <vector>
#include <string>
#include <algorithm>

#include "Globals.h"
#include "Player.h"
#include "Level.h"
#include "Camera.h"
#include "Map.h"

#define PI 3.14159265
#define DEGREES(x) int((x)/360.0*0xFFFFFF)
#define RADIANS(x) int((x)/2/M_PI*0xFFFFFF)

using namespace std;

vector<Level *> levels;
vector<Level *>::iterator riter;
vector<Level *>::iterator riter2;

void Transition(char LevelMatrix[3][3][3], int CurrentLevel);

bool keys[] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

int main()
{
	//==============================================
	//SHELL VARIABLES
	//==============================================
	bool redraw = true;
	bool doexit = false;
	bool render = false;

	double gameTime = 0;
	double frames = 0;
	double gameFPS = 0;

	double MouseX = 0;
	double MouseY = 0;
	double MouseAngleRadians = 0;

	char CurrentLevel = '_';

	bool DisplayMap = false;//tracks whether or not map needs to be displayed. Used in render section and activated by F_MAP key.

	//matrix for storing coordinates. used to keep track of what's where.
	char LevelMatrix[3][3][3] = {
	'A','B','C',
	'D','E','F',
	'G','H','I',

	'J','K','L',
	'M','_','N',
	'O','P','Q',

	'R','S','T',
	'U','V','W',
	'X','Y','Z'
	};

	//==============================================
	//PROJECT VARIABLES
	//==============================================

	Player *player = new Player();
	Camera *camera = new Camera();
	Map *map = new Map();

	//defining all the levels
	Level *levelA = new Level();
	Level *levelB = new Level();
	Level *levelC = new Level();
	Level *levelD = new Level();
	Level *levelE = new Level();
	Level *levelF = new Level();
	Level *levelG = new Level();
	Level *levelH = new Level();
	Level *levelI = new Level();
	Level *levelJ = new Level();
	Level *levelK = new Level();
	Level *levelL = new Level();
	Level *levelM = new Level();
	Level *level_ = new Level();
	Level *levelN = new Level();
	Level *levelO = new Level();
	Level *levelP = new Level();
	Level *levelQ = new Level();
	Level *levelR = new Level();
	Level *levelS = new Level();
	Level *levelT = new Level();
	Level *levelU = new Level();
	Level *levelV = new Level();
	Level *levelW = new Level();
	Level *levelX = new Level();
	Level *levelY = new Level();
	Level *levelZ = new Level();

	int state = PLAYING;

	//==============================================
	//ALLEGRO VARIABLES
	//==============================================
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_DISPLAY_MODE   disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font18;

	//==============================================
	//ALLEGRO INIT FUNCTIONS
	//==============================================
	if (!al_init())										//initialize Allegro
		return -1;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	//if (SCREENW == disp_data.width && SCREENH == disp_data.height) {
	//	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	//	display = al_create_display(disp_data.width, disp_data.height);
	//}
	//else {
	display = al_create_display(SCREENW - 100, SCREENH - 100);		//create our display object
	//}

	if (!display)//test display object
		return -1;

	//==============================================
	//ADDON INSTALL
	//==============================================
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_install_mouse();

	//==============================================
	//PROJECT INIT
	//==============================================
	//insert font types, images, sounds, state images, etc
	font18 = al_load_font("arial.ttf", 18, 0);
	//al_reserve_samples(100);

	//seeds RNG with computer clock
	srand(time(NULL));

	//creation of all images

	//creation of player and camera
	player->Init(0, 0, 0);
	camera->Init(0, 0, player);
	map->Init(font18);

	//creation of all levels. Init() involves/will involve creation of levels, objects, etc.
	levelA->Init('A', 0, 0, 0, player, camera, font18);
	levelB->Init('B', 1, 0, 0, player, camera, font18);
	levelC->Init('C', 2, 0, 0, player, camera, font18);

	levelD->Init('D', 0, 0, 1, player, camera, font18);
	levelE->Init('E', 1, 0, 1, player, camera, font18);
	levelF->Init('F', 2, 0, 1, player, camera, font18);

	levelG->Init('G', 0, 0, 2, player, camera, font18);
	levelH->Init('H', 1, 0, 2, player, camera, font18);
	levelI->Init('I', 2, 0, 2, player, camera, font18);

	levelJ->Init('J', 0, 1, 0, player, camera, font18);
	levelK->Init('K', 1, 1, 0, player, camera, font18);
	levelL->Init('L', 2, 1, 0, player, camera, font18);

	levelM->Init('M', 0, 1, 1, player, camera, font18);
	level_->Init('_', 1, 1, 1, player, camera, font18);//center of cube
	levelN->Init('N', 2, 1, 1, player, camera, font18);

	levelO->Init('O', 0, 1, 2, player, camera, font18);
	levelP->Init('P', 1, 1, 2, player, camera, font18);
	levelQ->Init('Q', 2, 1, 2, player, camera, font18);

	levelR->Init('R', 0, 2, 0, player, camera, font18);
	levelS->Init('S', 1, 2, 0, player, camera, font18);
	levelT->Init('T', 2, 2, 0, player, camera, font18);

	levelU->Init('U', 0, 2, 1, player, camera, font18);
	levelV->Init('V', 1, 2, 1, player, camera, font18);
	levelW->Init('W', 2, 2, 1, player, camera, font18);

	levelX->Init('X', 0, 2, 2, player, camera, font18);
	levelY->Init('Y', 1, 2, 2, player, camera, font18);
	levelZ->Init('Z', 2, 2, 2, player, camera, font18);

	//adding all levels to 'levels' vector
	levels.push_back(levelA);
	levels.push_back(levelB);
	levels.push_back(levelC);
	levels.push_back(levelD);
	levels.push_back(levelE);
	levels.push_back(levelF);
	levels.push_back(levelG);
	levels.push_back(levelH);
	levels.push_back(levelI);
	levels.push_back(levelJ);
	levels.push_back(levelK);
	levels.push_back(levelL);
	levels.push_back(levelM);
	levels.push_back(level_);
	levels.push_back(levelN);
	levels.push_back(levelO);
	levels.push_back(levelP);
	levels.push_back(levelQ);
	levels.push_back(levelR);
	levels.push_back(levelS);
	levels.push_back(levelT);
	levels.push_back(levelU);
	levels.push_back(levelV);
	levels.push_back(levelW);
	levels.push_back(levelX);
	levels.push_back(levelY);
	levels.push_back(levelZ);

	//==============================================
	//TIMER INIT AND STARTUP
	//==============================================
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.000 / FPS);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);
	gameTime = al_current_time();

	Transition(LevelMatrix, CurrentLevel);//sets up all adjacent levels


	//temporary means of setting correct player position based upon collision matrix
	for (riter = levels.begin(); riter != levels.end(); ++riter)
	{
		if ((*riter)->GetID() == CurrentLevel) {
			player->SetX((*riter)->GetPlayerX());
			player->SetY((*riter)->GetPlayerY());
			//camera->SetCameraXPos((*riter)->GetPlayerX() - SCREENW/2);
			//camera->SetCameraYPos((*riter)->GetPlayerY() - SCREENH/2);
		}
	}


	cout << "GAMELOOP BEGIN" << endl;
	//game loop begin
	while (!doexit)
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//==============================================
		//INPUT
		//==============================================
		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)//update mouse position
		{
			MouseX = ev.mouse.x;
			MouseY = ev.mouse.y;
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			case ALLEGRO_KEY_W:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_F:
				keys[F_MAP] = true;
				break;
			case ALLEGRO_KEY_1:
				keys[NUM_1] = true;
				break;
			case ALLEGRO_KEY_2:
				keys[NUM_2] = true;
				break;
			case ALLEGRO_KEY_3:
				keys[NUM_3] = true;
				break;
			case ALLEGRO_KEY_4:
				keys[NUM_4] = true;
				break;
			case ALLEGRO_KEY_5:
				keys[NUM_5] = true;
				break;
			case ALLEGRO_KEY_6:
				keys[NUM_6] = true;
				break;
			case ALLEGRO_KEY_7:
				keys[NUM_7] = true;
				break;
			case ALLEGRO_KEY_8:
				keys[NUM_8] = true;
				break;
			case ALLEGRO_KEY_9:
				keys[NUM_9] = true;
				break;
			case ALLEGRO_KEY_ENTER:
				keys[ENTER] = true;
				break;
			case ALLEGRO_KEY_LSHIFT:
				keys[SHIFT] = true;
				break;
			}
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			keys[MOUSE_BUTTON] = true;
		}

		if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			case ALLEGRO_KEY_W:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_S:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_F:
				keys[F_MAP] = false;
				break;
			case ALLEGRO_KEY_1:
				keys[NUM_1] = false;
				break;
			case ALLEGRO_KEY_2:
				keys[NUM_2] = false;
				break;
			case ALLEGRO_KEY_3:
				keys[NUM_3] = false;
				break;
			case ALLEGRO_KEY_4:
				keys[NUM_4] = false;
				break;
			case ALLEGRO_KEY_5:
				keys[NUM_5] = false;
				break;
			case ALLEGRO_KEY_6:
				keys[NUM_6] = false;
				break;
			case ALLEGRO_KEY_7:
				keys[NUM_7] = false;
				break;
			case ALLEGRO_KEY_8:
				keys[NUM_8] = false;
				break;
			case ALLEGRO_KEY_9:
				keys[NUM_9] = false;
				break;
			case ALLEGRO_KEY_ENTER:
				keys[ENTER] = false;
				break;
			case ALLEGRO_KEY_LSHIFT:
				keys[SHIFT] = false;
				break;
			}
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			keys[MOUSE_BUTTON] = false;
		}
		//==============================================
		//GAME UPDATE
		//==============================================
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;

			//UPDATE FPS===========
			frames++;
			if (al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}
			//=====================
			if (state == PLAYING)//if playing, receive movement and other stuff
			{
				//calculating MouseAngleRadians
				MouseAngleRadians = atan2(MouseY - (player->GetY() + player->GetBoundY() / 2), MouseX - (player->GetX() + player->GetBoundX() / 2)) * 180 / PI;
				if (MouseAngleRadians < 0)
					MouseAngleRadians *= -1;
				else if (MouseAngleRadians > 0) {	
					MouseAngleRadians = 360 - MouseAngleRadians;
				}
				MouseAngleRadians = MouseAngleRadians / 180 * PI;

				//player movement & attacking
				player->SetMouseAngleRadians(MouseAngleRadians);
				player->PlayerKeyboard(keys[UP], keys[DOWN], keys[LEFT], keys[RIGHT], keys[SHIFT]);
				//number keys (temporary, for testing purposes- do not plan on incorporating into gameplay)

				if (keys[F_MAP])//trigger for displaying map
				{
					if (!DisplayMap) {//opening map/data screen
						for (riter = levels.begin(); riter != levels.end(); ++riter)
						{
							if ((*riter)->GetID() == CurrentLevel)
								(*riter)->Pause();//pausing current level
						}
						camera->Pause();
						DisplayMap = true;
						map->ResetLayers();
						
					}
					else {//closing map/data screen
						for (riter = levels.begin(); riter != levels.end(); ++riter)
						{
							if ((*riter)->GetID() == CurrentLevel)
								(*riter)->Resume();//resuming current level
						}
						camera->Resume();
						DisplayMap = false;
					}
					keys[F_MAP] = false;
				}
				if (keys[MOUSE_BUTTON] && DisplayMap)//trigger for checking if mouse is modifying map screen when displayed
				{
					map->MouseInteraction(MouseX, MouseY);
				}

				if (keys[NUM_1])
				{
					player->SetX(MouseX);
					player->SetY(MouseY);
					keys[NUM_1] = false;
				}
				if (keys[NUM_2])
				{
					keys[NUM_2] = false;
				}
				if (keys[NUM_3])
				{
					keys[NUM_3] = false;
				}
				if (keys[NUM_4])
				{
					keys[NUM_4] = false;
				}
				if (keys[NUM_5])
				{
					keys[NUM_5] = false;
				}
				if (keys[NUM_6])
				{
					keys[NUM_6] = false;
				}
				if (keys[NUM_7])
				{
					keys[NUM_7] = false;
				}
				if (keys[NUM_8])
				{
					keys[NUM_8] = false;
				}
				if (keys[NUM_9])
				{
					keys[NUM_9] = false;
				}

				//collisions
				for (riter = levels.begin(); riter != levels.end(); ++riter)
				{
					if ((*riter)->GetID() == CurrentLevel)
						(*riter)->ObjectCollision();
				}

				//update
				for (riter = levels.begin(); riter != levels.end(); ++riter)
				{
					if ((*riter)->GetID() == CurrentLevel) {
						(*riter)->ObjectUpdate();
						camera->Update();//camera requires bounds of level to function
					}
				}
				if (DisplayMap) {
					map->Update();
				}

			}
			//=====================(PLAYING end)
			//cull the dead
			for (riter = levels.begin(); riter != levels.end(); ++riter)
			{
				if ((*riter)->GetID() == CurrentLevel)
					(*riter)->ObjectDeletion();
			}
		}
		//==============================================
		//RENDER
		//==============================================
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			//sort objects
			if (state == TITLE) {

			}
			else if (state == PLAYING) {
				for (riter = levels.begin(); riter != levels.end(); ++riter)
				{
					//al_draw_textf(font18, al_map_rgb(255, 255, 255), 5, 5, 0, "LEVEL: %c", CurrentLevel);
					if ((*riter)->GetID() == CurrentLevel)
						(*riter)->ObjectRender(camera->GetCameraXPos(), camera->GetCameraYPos());
				}
				if (DisplayMap) {
					map->Render(LevelMatrix, CurrentLevel);
				} 
			}
			//FLIP BUFFERS========================
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}//end gameloop

	 //==============================================
	 //DESTROY PROJECT OBJECTS
	 //==============================================
	//SHELL OBJECTS=================================
	al_destroy_font(font18);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}

void Transition(char LevelMatrix[3][3][3], int CurrentLevel) {

	//int shuffle = rand() % 12 + 1;
	//Shuffling levels like a Rubix Cube
	//for (riter = levels.begin(); riter != levels.end(); ++riter)
	//{
	//	(*riter)->Shuffle(shuffle);
	//}
	//realigning LevelMatrix according to shuffle



	
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					for (int z = 0; z < 3; z++) {
				for (riter = levels.begin(); riter != levels.end(); ++riter)
				{
					if ((*riter)->GetX() == x && (*riter)->GetY() == y && (*riter)->GetZ() == z)
						LevelMatrix[x][y][z] = (*riter)->GetID();
				}
			}
		}
	}



	


			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					for (int z = 0; z < 3; z++) {
				for (riter = levels.begin(); riter != levels.end(); ++riter) {
					if (LevelMatrix[x][y][z] == (*riter)->GetID()) {
						if (x + 1 < 3)
							(*riter)->SetXAdj(LevelMatrix[x + 1][y][z]);
						else
							(*riter)->SetXAdj('/');

						if (x - 1 > -1)
							(*riter)->SetNegXAdj(LevelMatrix[x - 1][y][z]);
						else
							(*riter)->SetNegXAdj('/');

						if (y + 1 < 3)
							(*riter)->SetYAdj(LevelMatrix[x][y + 1][z]);
						else
							(*riter)->SetYAdj('/');

						if (y - 1 > -1)
							(*riter)->SetNegYAdj(LevelMatrix[x][y - 1][z]);
						else
							(*riter)->SetNegYAdj('/');

						if (z + 1 < 3)
							(*riter)->SetZAdj(LevelMatrix[x][y][z + 1]);
						else
							(*riter)->SetZAdj('/');

						if (z - 1 > -1)
							(*riter)->SetNegZAdj(LevelMatrix[x][y][z - 1]);
						else
							(*riter)->SetNegZAdj('/');
					}
				}
			}
		}
	}
	for (riter = levels.begin(); riter != levels.end(); ++riter)
	{
		if ((*riter)->GetID() == CurrentLevel) {
			cout << "CURRENT LEVEL: " << (*riter)->GetID() << endl << endl;
			cout << "XAdj = " << (*riter)->GetXAdj() << endl;
			cout << "NegXAdj = " << (*riter)->GetNegXAdj() << endl;
			cout << "YAdj = " << (*riter)->GetYAdj() << endl;
			cout << "NegYAdj = " << (*riter)->GetNegYAdj() << endl;
			cout << "ZAdj = " << (*riter)->GetZAdj() << endl;
			cout << "NegZAdj = " << (*riter)->GetNegZAdj() << endl;
		}
	}


	
	for (int y = 0; y < 3; y++) {
		for (int z = 0; z < 3; z++) {
			for (int x = 0; x < 3; x++) {
				cout << LevelMatrix[x][y][z] << ", ";
			}
			cout << endl;
		}
		cout << endl;
	}
}