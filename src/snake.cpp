#include "../include/snake.h"

Snake::Snake() {
};

void Snake::set_direction(SDL_Event event)
{
	switch (event.key.scancode)
	{
	case SDL_SCANCODE_W:
	case SDL_SCANCODE_UP:
		if (direction != down)
		{
			direction = up;
		}
		break;
	case SDL_SCANCODE_A:
	case SDL_SCANCODE_LEFT:

		if (direction != right)
		{
			direction = left;
		}

		break;
	case SDL_SCANCODE_S:
	case SDL_SCANCODE_DOWN:

		if (direction != up)
		{
			direction = down;
		}
		break;
	case SDL_SCANCODE_D:
	case SDL_SCANCODE_RIGHT:

		if (direction != left)
		{
			direction = right;
		}
		break;
	default:
		break;
	}
}

void Snake::move()
{
	switch (direction)
	{
	case down:
		head.y += rect_size;
		break;
	case up:
		head.y -= rect_size;
		break;
	case left:
		head.x -= rect_size;
		break;
	case right:
		head.x += rect_size;
		break;
	}
	out_of_bounds();
};

void Snake::draw(SDL_Renderer *renderer)
{
	for (SDL_FRect snake_segment : body)
	{
		SDL_SetRenderDrawColor(renderer, 143, 188, 143, 255);
		SDL_RenderFillRect(renderer, &snake_segment);
	}
	SDL_SetRenderDrawColor(renderer, 0, 255, 127, 255);
	SDL_RenderFillRect(renderer, &body[0]);
};

bool Snake::ate_food(int food_x, int food_y)
{
	if (head.x == food_x && head.y == food_y)
	{
		return true;
	}
	return false;
};

bool Snake::ate_self()
{
	for (SDL_FRect snake_segment : body)
	{
		if (head.x == snake_segment.x && head.y == snake_segment.y)
		{
			return true;
		}
	}
	return false;
};

void Snake::out_of_bounds()
{
	if (head.x > screen_width)
	{
		head.x = 0;
	}
	else if (head.x < 0)
	{
		head.x = screen_width;
	}
	if (head.y > screen_height)
	{
		head.y = 0;
	}
	else if (head.y < 0)
	{
		head.y = screen_height;
	}
};

void Snake::reset()
{
	size = 1;
	head.x = screen_width / 2;
	head.y = screen_height / 2;
	body.clear();
};
