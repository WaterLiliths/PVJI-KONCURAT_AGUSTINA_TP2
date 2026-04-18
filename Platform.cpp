#include "Platform.h"

Platform::Platform(Vector2 pos_platform, int _blocks, PlatformType _type) {
	type = _type;
	position = pos_platform;
	blocks = _blocks;
	size = { 0, 0 };
	hitbox = { position.x, position.y, size.x, size.y };
}
Platform::~Platform() {

}
void Platform::draw(Assets& assets) {

    for (int i = 0; i < blocks; i++) {

        Vector2 blocks_position; //Creo esta variable para asignar la posición correcta en cada caso (vertical/horizontal)

        if (type == FLOOR) {
            blocks_position = { position.x + (i * 36), position.y };

            int tileIndex; //Creo esta variable para indicar qué bloque hay que dibujar del arreglo de assets.

            if (i == 0) //Primero
                tileIndex = 0;
            else if (i == blocks - 1) //Último
                tileIndex = 2;
            else //Medio
                tileIndex = 1;

            DrawTextureEx(assets.tile[tileIndex], blocks_position, 0, 2, WHITE);
        }

        else if (type == GROUND) {
            blocks_position = { position.x + (i * 36), position.y };

            int tileIndex; //Creo esta variable para indicar qué bloque hay que dibujar del arreglo de assets.

            if (i == 0) //Primero
                tileIndex = 3;
            else if (i == blocks - 1) //Último
                tileIndex = 5;
            else //Medio
                tileIndex = 4;

            DrawTextureEx(assets.tile[tileIndex], blocks_position, 0, 2, WHITE);
        }

        else if (type == TREE_BUSH) {
            blocks_position = { position.x + (i * 36), position.y };

            int tileIndex; //Creo esta variable para indicar qué bloque hay que dibujar del arreglo de assets.

            if (i == 0) //Primero
                tileIndex = 9;
            else if (i == blocks - 1) //Último
                tileIndex = 11;
            else //Medio
                tileIndex = 10;

            DrawTextureEx(assets.tile[tileIndex], blocks_position, 0, 2, WHITE);
        }

        else if (type == TREE) {
            blocks_position = { position.x, position.y - (i * 36) };
            DrawTextureEx(assets.tile[7], blocks_position, 0, 2, WHITE);
        }

        else if (type == BRANCH) {
            blocks_position = { position.x + (i * 36), position.y };
            DrawTextureEx(assets.tile[8], blocks_position, 0, 2, WHITE);
        }

    }

    //Tiles que no usan loop

    if (type == TREE_STUMP) {
        DrawTextureEx(assets.tile[6], position, 0, 2, WHITE);
    }


	//DEBUG 
	DrawRectangleLines(
		(int)hitbox.x,
		(int)hitbox.y,
		(int)hitbox.width,
		(int)hitbox.height,
		RED
	);

}
void Platform::assign_platform_hitbox() {
    if (type == BRANCH) {
        size = { 36, 16 };
        hitbox = { position.x, position.y, (size.x * blocks), size.y };
    }
    else if (type == TREE) {
        size = { 36, 36 };
        hitbox = { position.x, (position.y - (size.y * (blocks - 1))), size.x, (size.y * blocks) };
    }
    else {
        size = { 36, 36 };
        hitbox = { position.x, position.y, (size.x * blocks), size.y };
    }

}
Rectangle Platform::get_hitbox() {
	return hitbox;
}
PlatformType Platform::get_platform_type() {
    return type;
}