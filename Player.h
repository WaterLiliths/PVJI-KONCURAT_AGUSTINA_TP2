#pragma once
#include "raylib.h"
#include "Assets.h"

class Player
{
protected:
	const float GRAVITY = 500.0;
	const float JUMP_FORCE = -270.0;
	
	Vector2 start_position;
	Vector2 position;
	Vector2 size;
	Vector2 velocity;
	Rectangle hitbox;
	Vector2 previous_position; //Para guardar el valor de la posición y colisionar con las plataformas que se traspasan desde abajo.
	int anim_frame; //para las animaciones
	float anim_timer; //para el tiempo de las animaciones
	bool is_moving;

	bool is_on_floor;

public:
	Player();
	~Player();
	void update(const Assets& assets);
	void move();
	void jump(const Assets& assets);
	void draw(const Assets& assets);
	void restart();
	void set_position(Vector2 _position);
	void set_velocity_y(float velocity_y);
	void set_is_on_floor(bool _is_on_floor);
	Vector2 get_position();
	Vector2 get_velocity();
	Rectangle get_hitbox(); //para calcular las colisiones.
	Vector2 get_previous_position(); //para calcular las colisiones.
	bool get_is_on_floor(); //para debuggear.
};
