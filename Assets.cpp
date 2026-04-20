#include "Assets.h"
void Assets::load() {
	//========
	//GRÁFICOS
	//========

	//PLAYER
	player_0 = LoadTexture("assets/tile_0000.png");
	player_1 = LoadTexture("assets/tile_0001.png");

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

	//======
	//SONIDO
	//======

	jump_sfx = LoadSound("assets/jump.mp3");
	win_sfx = LoadSound("assets/win.wav");
	fall_sfx = LoadSound("assets/fall.mp3");
}
void Assets::unload() {

	//========
	//GRÁFICOS
	//========

	//PLAYER
	UnloadTexture(player_0);
	UnloadTexture(player_1);

	//ENEMIES
	for (int i = 0; i < 8; i++) {
		UnloadTexture(enemy[i]);
	}

	//TILES
	for (int i = 0; i < 12; i++) {
		UnloadTexture(tile[i]);
	}

	//BACKGROUND
	UnloadTexture(background);

	//======
	//SONIDO
	//======

	UnloadSound(jump_sfx);
	UnloadSound(win_sfx);
	UnloadSound(fall_sfx);

}