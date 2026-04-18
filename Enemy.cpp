#include "Enemy.h"
Enemy::Enemy() {
	type = ENEMY_0;
	position = { 0,0 };
	size = { 48, 48 }; //Los asstes tienen 24px y lo escalo por 2.
	hitbox = { position.x, position.y, size.x, size.y };
	speed = 150.0;
	direction = 1; //Hacia la derecha
	is_moving = false;
}
Enemy::~Enemy() {

}
void Enemy::update() {
	if (!is_moving) return;

	float delta_time = GetFrameTime();

	position.x += speed * direction * delta_time;
	hitbox.x = position.x;
	hitbox.y = position.y;

}
void Enemy::draw(const Assets& assets) {
	
	int sprite_index = type * 2; //multiplico el tipo * 2. Por el arreglo de sprites va a asignar el correcto.

	DrawTextureEx(assets.enemy[sprite_index], position, 0, 2, WHITE);

	//DEBUG
	DrawRectangleLines(position.x, position.y, size.x, size.y, RED);

}
void Enemy::start() {
	is_moving = true;
}
void Enemy::stop() {
	is_moving = false;
}
Rectangle Enemy::get_hitbox() {
	return hitbox;
}
bool Enemy::get_is_moving() {
	return is_moving;
}
Vector2 Enemy::get_position() {
	return position;
}
int Enemy::get_direction() {
	return direction;
}
void Enemy::set_position(Vector2 _position) {
	position = _position;
	hitbox.x = position.x;
	hitbox.y = position.y;
}
void Enemy::set_is_moving(bool _is_moving) {
	is_moving = _is_moving;
}
void Enemy::set_direction(int _direction) {
	direction = _direction;
}
void Enemy::set_type(EnemyType _type) {
	type = _type;
}