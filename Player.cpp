#include "Player.h"
Player::Player() {
	velocity = { 150.0,0 };
	start_position = { 414, 610 };
	position = start_position;
	size = { 48, 48 }; //El sprite es de 24px y lo uso escalado x2.
	hitbox = { position.x, position.y, size.x, size.y }; //Inicializo los valores de acuerdo al tamaño que tendrá el sprite
	previous_position = position;
	is_on_floor = false;
}
Player::~Player() {

}
void Player::draw(const Assets& assets) {
	DrawTextureEx(assets.player_01, position, 0, 2, WHITE);

	////DEBUG
	DrawRectangleLines(
		(int)hitbox.x,
		(int)hitbox.y,
		(int)hitbox.width,
		(int)hitbox.height,
		GREEN
	);
}
//Unifico el movimiento y el salto en una única función update.
void Player::update(const Assets& assets) {
	//TraceLog(LOG_INFO, "is_on_floor: %d ",
	//	is_on_floor
	//);

	jump(assets);
	move();
}
void Player::move() {
	float delta_time = GetFrameTime();

	previous_position = position;

	//Simulación de gravedad si el personaje no está en el suelo
	if (!is_on_floor) {
		velocity.y += GRAVITY * delta_time;
	}
	position.y += velocity.y * delta_time;
	hitbox.y = position.y;

	//Chequea el input en las teclas y los bordes para mover y/o colisionar
	if (IsKeyDown(KEY_RIGHT) && (position.x + size.x < GetScreenWidth()))
	{
		position.x += velocity.x * delta_time;
		hitbox.x = position.x;
	}
	if (IsKeyDown(KEY_LEFT) && position.x > 0)
	{
		position.x -= velocity.x * delta_time;
		hitbox.x = position.x;
	}
}
void Player::jump(const Assets& assets) {
	float jump_buffer = 0.0; //Creo un buffer porque no siempre lee la barra para saltar.

	if (IsKeyPressed(KEY_SPACE)) {
		jump_buffer = 0.1;
	}

	jump_buffer -= GetFrameTime();

	if (is_on_floor && jump_buffer > 0.0f) {
		velocity.y = JUMP_FORCE;
		is_on_floor = false;

		PlaySound(assets.jump_sfx);
	}

}
void Player::restart() {
	position = start_position;
	hitbox = { position.x, position.y, size.x, size.y };
	velocity.y = 0.0;
	is_on_floor = false;
}
void Player::set_is_on_floor(bool _is_on_floor) {
	is_on_floor = _is_on_floor;
}
void Player::set_position(Vector2 _position) {
	position = _position;
	hitbox.x = position.x;
	hitbox.y = position.y;
}
void Player::set_velocity_y(float velocity_y) {
	velocity.y = velocity_y;
}
Vector2 Player::get_position() {
	return position;
}
Vector2 Player::get_velocity() {
	return velocity;
}
Rectangle Player::get_hitbox() {
	return hitbox;
}
Vector2 Player::get_previous_position() {
	return previous_position;
}
bool Player::get_is_on_floor() {
	return is_on_floor;
}
