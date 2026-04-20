#pragma once
#include "raylib.h"
#include "Assets.h"

enum  EnemyType { //Creo un enum para los cuatro tipos de enemigos
	ENEMY_0,
	ENEMY_1,
	ENEMY_2,
	ENEMY_3
};

class Enemy
{
protected:
	EnemyType type;
	Vector2 position;
	Vector2 size;
	Rectangle hitbox;
	float speed;
	int direction;
	bool is_moving;
	int anim_frame; //para las animaciones
	float anim_timer; //para el tiempo de las animaciones

public:
	Enemy();
	~Enemy();
	void update();
	void draw(const Assets& assets);
	void start();
	void stop();
	Rectangle get_hitbox(); //Para calcular las colisiones.
	bool get_is_moving();
	Vector2 get_position();
	int get_direction();
	void set_position(Vector2 _position);
	void set_is_moving(bool _is_moving);
	void set_direction(int _direction);
	void set_type(EnemyType _type);
};

