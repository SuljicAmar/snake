#ifndef SNAKE_H
#define SNAKE_H

#include <SDL3/SDL.h>
#include <deque>
#include "defs.h"

class Snake
{
public:
	int size{1};
	enum Direction
	{
		down,
		left,
		right,
		up
	};

	SDL_FRect head{.x = screen_width / 2, .y = screen_height / 2, .w = rect_size, .h = rect_size};
	std::deque<SDL_FRect> body;

	Snake();

	void set_direction(SDL_Event event);

	void move();

	void draw(SDL_Renderer *renderer);

	bool ate_food(int food_x, int food_y);

	bool ate_self();

	void out_of_bounds();

	void reset();

private:
	Direction direction{right};
};

#endif
