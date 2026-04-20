#pragma once
#include "raylib.h"
#include "Player.h"
#include "Assets.h"
#include "Platform.h"
#include "Enemy.h"
#include "Door.h"
#include "Stack.h"
#include "Queue.h"
#include "Timer.h"
#include "Utilities.h"
#include <vector>

class Game
{
protected: 
	bool game_won;
	bool game_over;

	Player player;
	Assets assets;
	Door door;
	Timer timer;
	Utilities utilities;

	//Creo vectores para inicializar las plataformas, las pilas y las colas
	std::vector <Platform> platforms;
	std::vector <Queue> queues;
	std::vector <Stack> stacks;


public:
	Game();
	~Game();
	void init();
	void update();
	void draw();
	void check_collisions();
	void check_platform_collisions();
	void check_enemies_collisions();
	void check_door_collision();
	void win_game();
	void lose_game();
	void restart_game();
	void unload();
};


