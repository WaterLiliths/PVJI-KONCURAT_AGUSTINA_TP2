#include "Door.h"
Door::Door(){
	position = { 696, 58 };
	size = { 36, 36 }; //El sprite tiene 18px y lo uso escalado x2.
	hitbox = { position.x, position.y, size.x, size.y };

}
Door::~Door(){

}
void Door::draw(const Assets& assets) {
	DrawTextureEx(assets.door_2, position, 0, 2, WHITE); //Base de la puerta
	DrawTextureEx(assets.door_1, {position.x, position.y - size.y}, 0, 2, WHITE); //Marco superior de la puerta

	//DEBUG 
	//DrawRectangleLines(
	//	(int)hitbox.x,
	//	(int)hitbox.y,
	//	(int)hitbox.width,
	//	(int)hitbox.height,
	//	RED
	//);

}
Rectangle Door::get_hitbox() {
	return hitbox;
}