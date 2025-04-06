#ifndef APP_H
#define APP_H

#include <SDL3/SDL.h>
#include "snake.h"
#include "food.h"

class App
{
public:
	SDL_Window *window{nullptr};
	SDL_Renderer *renderer{nullptr};

	int frame_time;
	SDL_Event event;
	bool running{true};

	App() {};

	void init();

	void game_loop(Snake &snake, Food &food);

	void quit();
};

#endif
