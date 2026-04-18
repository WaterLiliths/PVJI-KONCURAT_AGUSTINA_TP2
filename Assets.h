#pragma once
#include "raylib.h"
#include <string>

//Creo un struct para los assets, puesto que todas las clases van a acceder a ellos.
struct Assets
{
	//========
	//GRÁFICOS
	//========

	//PLAYER
	Texture2D player_01;
	Texture2D player_02;
	
	//ENEMIES
	Texture2D enemy[8];

	//TILES
	Texture2D tile[12];

	//DOOR
	Texture2D door_1;
	Texture2D door_2;

	//BACKGROUND
	Texture2D background;

	//======
	//SONIDO
	//======
	Sound jump_sfx;
	Sound win_sfx;
	Sound fall_sfx;

	//===================

	void load();
	void unload();
};

