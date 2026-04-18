#include "Assets.h"
void Assets::load() {
	//========
	//GRÁFICOS
	//========

	//PLAYER
	player_01 = LoadTexture("assets/tile_0000.png");
	player_02 = LoadTexture("assets/tile_0001.png");

	//ENEMIES
	for (int i = 0; i < 8; i++) {
		enemy[i] = LoadTexture(("assets/enemy_" + std::to_string(i) + ".png").c_str());
	}

	//TILES
	for (int i = 0; i < 12; i++) {
		tile[i] = LoadTexture(("assets/tile_" + std::to_string(i) + ".png").c_str());
	}

	//DOOR
	door_1 = LoadTexture("assets/door_1.png");
	door_2 = LoadTexture("assets/door_2.png");

	//BACKGROUND
	background = LoadTexture("assets/background.png");

//	jump_sfx = LoadSound("assets/jump.mp3");
//	correct_sfx = LoadSound("assets/correct.wav");
//	wrong_sfx = LoadSound("assets/wrong.mp3");
}
void Assets::unload() {

	//========
	//GRÁFICOS
	//========

	//PLAYER
	UnloadTexture(player_01);
	UnloadTexture(player_02);

	//ENEMIES
	for (int i = 0; i < 8; i++) {
		UnloadTexture(enemy[i]);
	}

	//TILES
	for (int i = 0; i < 14; i++) {
		UnloadTexture(tile[i]);
	}

	//BACKGROUND
	UnloadTexture(background);

//	UnloadSound(jump_sfx);
//	UnloadSound(correct_sfx);
//	UnloadSound(wrong_sfx);
}