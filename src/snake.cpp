#include "../include/snake.h"

Snake::Snake() {};

void Snake::set_direction(SDL_Event event) {
  // set direction based off input
  switch (event.key.scancode) {
  case SDL_SCANCODE_W:
  case SDL_SCANCODE_UP:
    if (direction != down) {
      direction = up;
    }
    break;
  case SDL_SCANCODE_A:
  case SDL_SCANCODE_LEFT:
    if (direction != right) {
      direction = left;
    }
    break;
  case SDL_SCANCODE_S:
  case SDL_SCANCODE_DOWN:
    if (direction != up) {
      direction = down;
    }
    break;
  case SDL_SCANCODE_D:
  case SDL_SCANCODE_RIGHT:
    if (direction != left) {
      direction = right;
    }
    break;
  default:
    break;
  }
}

void Snake::move(int rect_size) {
  // move snake according to direction
  switch (direction) {
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
};

bool Snake::ate_food(SDL_Point food_cordinates) {
  // check collision with food
  if (head.x == food_cordinates.x && head.y == food_cordinates.y) {
    return true;
  }
  return false;
};

bool Snake::ate_self() {
  // check collision with self
  for (SDL_FRect snake_segment : body) {
    if (head.x == snake_segment.x && head.y == snake_segment.y) {
      return true;
    }
  }
  return false;
};

bool Snake::out_of_bounds(int window_width, int window_height) {
  // check out of bounds
  for (SDL_FRect snake_segment : body) {
    if (snake_segment.x > window_width || snake_segment.x < 0 ||
        snake_segment.y > window_height || snake_segment.y < 0) {
      return true;
    }
  }
  return false;
};

void Snake::reset(int window_width, int window_height, int rect_size) {
  // reset snake if collides with self
  size = 1;
  create_head(window_width, window_height, rect_size);
  body.clear();
};

void Snake::handle_size() {
  // used to reset snake when reset() is called
  // and allows us to constantly add and draw new heads
  // in main game loop as its constantly "cleaning up"
  body.push_front(head);
  while (body.size() > size) {
    body.pop_back();
  }
};

std::string Snake::get_size_as_str() { return std::to_string(size - 1); };

void Snake::create_head(int window_width, int window_height, int rect_size) {
  head = {.x = window_width / 2.f,
          .y = window_height / 2.f,
          .w = (float)rect_size,
          .h = (float)rect_size};
};
