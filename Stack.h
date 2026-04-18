#pragma once
#include <stack>
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "Assets.h"

class Stack
{
private:
	//Creo dos stacks, para poder guardar a los enemigos de cada lado.
	std::stack<Enemy> stack_1;
	std::stack<Enemy> stack_2;

	Enemy enemy[4]; //Los cuatro enemigos que posee el stack
	Enemy current_enemy; //El enemigo que actualmente se esta moviendo.
	bool active_enemy;
	bool going_right; //Para chequear y alternar la dirección de los enemigos.

	float position_y; //Para colocarlo en los pisos.
	
	//limites hasta los que se mueven los enemigos (troncos).
	float left_limit;
	float right_limit;

public:
	Stack(float _position_y, float _left_limit, float _right_limit, bool _going_right);
	~Stack();
	void init_enemies();
	void loop();
	void draw_stack_1(const Assets& assets);
	void draw_stack_2(const Assets& assets);
	void draw(const Assets& assets);
	bool check_collisions(Player& player); //Sé que no es ideal que Queue/Stack conozcan player, 
											//pero no se me ocurría otra forma de hacerlo sin entrar 
											//en temas que no vimos. 
};

