#include "../include/app.h"

int main()
{
	App app;
	app.init();
	Snake snake;
	Food food;
	while (app.running)
	{
		app.game_loop(snake, food);
	}
	app.quit();
};
