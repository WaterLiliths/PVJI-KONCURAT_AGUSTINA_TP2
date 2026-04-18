#pragma once
#include <queue>
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "Assets.h"


class Queue
{
private:
	std::queue<Enemy> queue;

	Enemy enemy[4]; //Los cuatro enemigos que tiene el stack
	Enemy current_enemy; //El enemigo que se está moviendo
	bool active_enemy;
	bool starts_right; //Para chequear y alternar la dirección de los enemigos.

	float position_y; //Para colocarlo en los pisos.

	//limites hasta los que se mueven los enemigos (troncos).
	float left_limit;
	float right_limit;
	float offset; //Para calcular la distancia entre enemigos

public:
	Queue(float _position_y, float _left_limit, float _right_limit, bool _starts_right);
	~Queue();
	void init_enemies();
	void loop();
	void draw(const Assets& assets);
	bool check_collisions(Player& player); //Sé que no es ideal que Queue/Stack conozcan player, 
												//pero no se me ocurría otra forma de hacerlo sin entrar 
												//en temas que no vimos. 
	Vector2 get_front_position();
};

