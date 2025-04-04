#ifndef FOOD_H
#define FOOD_H
#include <SDL3/SDL.h>

class Food
{
public:
	Food();
	int x;
	int y;

	void create();

	void draw(SDL_Renderer *renderer);

private:
	SDL_FRect rect;
};

#endif
