#include "Stack.h"
Stack::Stack(float _position_y, float _left_limit, float _right_limit, bool _going_right) {
	position_y = _position_y;
	left_limit = _left_limit;
	right_limit = _right_limit;
	active_enemy = false;
	going_right = _going_right;
}
Stack::~Stack() {

}
void Stack::init_enemies() {
	for (int i = 0; i < 4; i++) {
		enemy[i].set_type((EnemyType)i);
		enemy[i].set_position({ 0, position_y }); //la posición x se actualiza en el loop/draw;
	}

	if (going_right) {
		for (int i = 0; i < 4; i++) stack_1.push(enemy[i]);
	}
	else
	{
		for (int i = 0; i < 4; i++) stack_2.push(enemy[i]);
	}

}
void Stack::loop(){

	//posición que se actualiza con cada enemigo que entra al stack.
	float right_position = right_limit - (stack_2.size() * 40); //"40" como offset para separar a los enemigos.
	float left_position = left_limit + (stack_1.size() * 40);

	if (active_enemy) { //Primero chequeo que no haya enemigos activos (moviéndose) para evitar rebote constante.

		current_enemy.update();

		//Si el enemigo va hacia la derecha (hacia el stack_2)
		if (going_right && current_enemy.get_position().x >= right_position) {

			current_enemy.stop();
			stack_2.push(current_enemy);

			active_enemy = false;

			//cambio de dirección al vaciar el stack 1.
			if (stack_1.empty()) {
				going_right = false;
			}
		}

		//Si el enemigo va hacia la izquierda (hacia el stack_1)
		else if (!going_right && current_enemy.get_position().x <= left_position) {

			current_enemy.stop();
			stack_1.push(current_enemy);

			active_enemy = false;

			//cambio de dirección al vaciar el stack_2.
			if (stack_2.empty()) {
				going_right = true;
			}
		}
	}

	else {

		//Se define de qué stack se sacan los enemigos
		if (going_right && !stack_1.empty()) {

			current_enemy = stack_1.top();
			stack_1.pop();

			current_enemy.set_position({ left_position, position_y });
			current_enemy.set_direction(1);
			current_enemy.start();

			active_enemy = true;
		}

		else if (!going_right && !stack_2.empty()) {

			current_enemy = stack_2.top();
			stack_2.pop();

			current_enemy.set_position({ right_position, position_y });
			current_enemy.set_direction(-1);
			current_enemy.start();

			active_enemy = true;
		}
	}
}
void Stack::draw_stack_1(const Assets& assets) {

	float offset = 40; //Separación entre los enemigos
	float position_x = left_limit;

	std::stack<Enemy> temp_1 = stack_1; //Creo un stack temporal para destruirlo mientras dibujo.
	std::vector<Enemy> stack_1_ordered; //Creo un vector para ordenar los enemigos simulando la pila.

	//Paso los enemigos al vector
	while (!temp_1.empty()) {
		stack_1_ordered.push_back(temp_1.top());
		temp_1.pop();
	}

	//Ordeno los enemigos al revés
	for (int i = stack_1_ordered.size() - 1; i >= 0; i--) {
		stack_1_ordered[i].set_position({ position_x, position_y });
		stack_1_ordered[i].draw(assets);

		position_x += offset;
	}

}
void Stack::draw_stack_2(const Assets& assets) {
	float offset = 40; //Separación entre los enemigos
	float position_x = right_limit;

	std::stack<Enemy> temp_2 = stack_2; //Creo un stack temporal para destruirlo mientras dibujo.
	std::vector<Enemy> stac_2_ordered; //Creo un vector para ordenar los enemigos simulando la pila.

	//Paso los enemigos al vector
	while (!temp_2.empty()) {
		stac_2_ordered.push_back(temp_2.top());
		temp_2.pop();
	}

	//Ordeno los enemigos al revés
	for (int i = stac_2_ordered.size() - 1; i >= 0; i--) {
		stac_2_ordered[i].set_position({ position_x, position_y });
		stac_2_ordered[i].draw(assets);

		position_x -= offset;
	}
}
void Stack::draw(const Assets& assets) {
	//ENEMIGO ACTIVO
	if (active_enemy) {
		current_enemy.draw(assets);
	}

	draw_stack_1(assets);
	draw_stack_2(assets);
}
bool Stack::check_collisions(Player& player) {
	float position_x_right = right_limit;
	float position_x_left = left_limit;
	float offset = 40;

	//ENEMIGO ACTIVO
	if (active_enemy) {
		if (CheckCollisionRecs(current_enemy.get_hitbox(), player.get_hitbox())) {
			return true;
		}
	}

	//STACK 1
	{
		std::stack<Enemy> temp_1 = stack_1; //Creo una pila temporal para checkear y destruirla.
		std::vector<Enemy> ordered; //Para poder iterar y rodenar los enemigos

		while (!temp_1.empty()) {
			ordered.push_back(temp_1.top());
			temp_1.pop();
		}


		for (int i = ordered.size() - 1; i >= 0; i--) {
			ordered[i].set_position({ position_x_left, position_y });

			if (CheckCollisionRecs(ordered[i].get_hitbox(), player.get_hitbox())) {
				return true;
			}

			position_x_left += offset;
		}
	}

	//STACK 2

	{
		std::stack<Enemy> temp_2 = stack_2; //Creo una pila temporal para checkear y destruirla.
		std::vector<Enemy> ordered; //Para poder iterar y rodenar los enemigos

		while (!temp_2.empty()) {
			ordered.push_back(temp_2.top());
			temp_2.pop();
		}

		for (int i = ordered.size() - 1; i >= 0; i--) {
			ordered[i].set_position({ position_x_right, position_y });

			if (CheckCollisionRecs(ordered[i].get_hitbox(), player.get_hitbox())) {
				return true;
			}

			position_x_right -= offset;
		}
	}

	return false;
}