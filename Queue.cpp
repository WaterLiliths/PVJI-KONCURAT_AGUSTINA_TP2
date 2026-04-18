#include "Queue.h"
Queue::Queue(float _position_y, float _left_limit, float _right_limit, bool _starts_right) {
	position_y = _position_y;
	left_limit = _left_limit;
	right_limit = _right_limit;
	active_enemy = false;
	starts_right = _starts_right;
	offset = 40.0;

}
Queue::~Queue() {

}
void Queue::init_enemies(){
	for (int i = 0; i < 4; i++) {
		enemy[i].set_type((EnemyType)i);
		enemy[i].set_position({ 0, position_y }); //la posición x se actualiza en el loop/draw;
		if (starts_right) {
			enemy[i].set_direction(-1);
		}
		queue.push(enemy[i]);
	}

	active_enemy = false;
}
void Queue::loop() {

	if (active_enemy) { //Primero chequeo si hay enemigos activos
		current_enemy.update();

		if (starts_right) {
			if (current_enemy.get_position().x <= left_limit) { //lega al tope izquierdo
				current_enemy.stop();
				current_enemy.set_position(get_front_position()); //Vuelve a la posición final de la cola
				queue.push(current_enemy); //Lo devuelvo a la cola.

				active_enemy = false;
			}

		}
		else{
			if (current_enemy.get_position().x >= right_limit) { //Si llega al tope derecho

				current_enemy.stop();
				current_enemy.set_position(get_front_position()); //Vuelve a la posición final de la cola
				queue.push(current_enemy); //Lo devuelvo a la cola.

				active_enemy = false;
			}
		}
	}
	else
	{
		if (!queue.empty()) {
			current_enemy = queue.front();
			queue.pop();

			current_enemy.set_position(get_front_position());
			current_enemy.start();

			active_enemy = true;
		}
	}

}
void Queue::draw(const Assets& assets) {

	float position_in_queue = left_limit;
	if (starts_right) position_in_queue = right_limit;

	//ENEMIGO ACTIVO
	if (active_enemy) current_enemy.draw(assets);

	std::queue<Enemy> temp = queue; //Creo un queue temporal para destruirlo mientras dibujo
	std::vector<Enemy> ordered; //creo un vector para iterar y reordenar visualmente los assets

	while (!temp.empty()) {
		ordered.push_back(temp.front());
		temp.pop();
	}

	for (int i = ordered.size() - 1; i >= 0; i--) {
		ordered[i].set_position({ position_in_queue, position_y });
		ordered[i].draw(assets);

		if (starts_right) {
			position_in_queue -= offset;
		}
		else {
			position_in_queue += offset;
		}

	}

}Vector2 Queue::get_front_position() {
	int size = queue.size();
	float position_x = 0;
	
	if (starts_right) {
		position_x = right_limit - (size) * offset;
	}
	else
	{
		position_x = left_limit + (size)*offset;
	}
	return {position_x , position_y };
}
bool Queue::check_collisions(Player& player) {
	
	//ENEMIGO ACTIVO
	if (active_enemy) {
		if (CheckCollisionRecs(current_enemy.get_hitbox(), player.get_hitbox())) {
			return true;
		}
	}

	//ENEMIGOS EN COLA
	std::queue<Enemy> temp = queue; //Creo una cola temporal para checkear y destruirla.

	float position_in_queue = starts_right ? right_limit : left_limit; //Chequea la posición incial

	while (!temp.empty()) {
		Enemy _enemy = temp.front();
		temp.pop();

		_enemy.set_position({ position_in_queue, position_y });

		if (CheckCollisionRecs(_enemy.get_hitbox(), player.get_hitbox())) {
			return true;
		}

		if (starts_right) position_in_queue -= offset;
		else position_in_queue += offset;
	}

	return false;
}