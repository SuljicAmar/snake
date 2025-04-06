#include "../include/app.h"

void App::init()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Failed initializing SDL: %s", SDL_GetError());
		running = false;
	}

	if (!SDL_CreateWindowAndRenderer("Snake", screen_width, screen_height, 0, &window, &renderer))
	{
		SDL_Log("Failed creating window/renderer: %s", SDL_GetError());
		running = false;
	}
}

void App::game_loop(Snake &snake, Food &food)
{
	Uint64 frame_start{SDL_GetTicksNS()};

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)
		{
			running = false;
		}
		if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat)
		{
			snake.set_direction(event);
		}
	}
	snake.move();

	if (snake.ate_food(food.x, food.y))
	{
		snake.size++;
		bool keep_creating{true};

		while (keep_creating)
		{
			keep_creating = false;
			food.create();
			for (SDL_FRect snake_segment : snake.body)
			{
				if (snake_segment.x == food.x && snake_segment.y == food.y)
				{
					keep_creating = true;
					break;
				}
			}
		}
	}

	if (snake.ate_self())
	{
		snake.reset();
	}

	snake.body.push_front(snake.head);
	while (snake.body.size() > snake.size)
	{
		snake.body.pop_back();
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	food.draw(renderer);
	snake.draw(renderer);

	SDL_RenderPresent(renderer);
	frame_time = SDL_GetTicksNS() - frame_start;

	if (frame_time < ns_per_frame)
	{
		SDL_DelayNS(ns_per_frame - frame_time);
	}
};

void App::quit()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
};
