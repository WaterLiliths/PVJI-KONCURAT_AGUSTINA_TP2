#include "Timer.h"
Timer::Timer() {
	time_left = 30.0f;
	time_over = false;
	color = GRAY;
}
Timer::~Timer() {

}
void Timer::advance(float delta_time) {
	time_left -= delta_time;

	if (time_left < 0.0f) {
		time_left = 0.0f;
		time_over = true;
	}
}
void Timer::restart() {
	color = GRAY;
	time_left = 30.0f;
	time_over = false;
}
void Timer::draw(Utilities& utilities) {
	

	//Cambio de color a rojo cuando quedan 10 segundos o menos.
	if (time_left < 11) color = RED;
	utilities.draw_centerd_text(TextFormat("Tiempo restante: %d", (int)time_left), GetScreenWidth(), 20, 20, color);
}
bool Timer::get_time_over() {
	return time_over;
}