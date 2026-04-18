#pragma once
#include "raylib.h"
#include "Assets.h"
class Door
{
private:
	Vector2 position;
	Vector2 size;
	Rectangle hitbox;

public:
	Door();
	~Door();
	void draw(const Assets& assets);
	Rectangle get_hitbox(); //Para calcular la colisión
};

