#pragma once
#include "raylib.h"
#include "Utilities.h"

class Timer
{
private:
	float time_left;
	bool time_over;
	Color color;

public:
	Timer();
	~Timer();
	void advance(float delta_time);
	void restart();
	void draw(Utilities& utilities);
	bool get_time_over();
};

