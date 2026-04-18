#pragma once
#include "raylib.h"
#include "Assets.h"


enum PlatformType { //Creo un enum para indicar las diferentes clases de tiles que hay
	FLOOR,
	GROUND,
	TREE_STUMP,
	TREE,
	BRANCH,
	TREE_BUSH,
};

class Platform
{
protected:
	PlatformType type;
	Vector2 position;
	int blocks;
	Vector2 size;
	Rectangle hitbox;

public:
	Platform(Vector2 pos_platform, int _blocks, PlatformType _type); //Para instanciarlos por medio de un vector
	~Platform();
	void draw(Assets& assets);
	void assign_platform_hitbox(); //No todas las plataformas tiene el mismo hitbox.
	Rectangle get_hitbox(); //para calcular la colisión.
	PlatformType get_platform_type(); //para saber si la plataforma se puede traspasar desde abajo.

};

