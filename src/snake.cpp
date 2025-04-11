#include "../include/snake.h"

Snake::Snake() {};

void Snake::set_direction(SDL_Event event) {
  switch (event.key.scancode) {
  case SDL_SCANCODE_W:
  case SDL_SCANCODE_UP:
    if (m_direction != down) {
      m_direction = up;
    }
    break;
  case SDL_SCANCODE_A:
  case SDL_SCANCODE_LEFT:

    if (m_direction != right) {
      m_direction = left;
    }

    break;
  case SDL_SCANCODE_S:
  case SDL_SCANCODE_DOWN:

    if (m_direction != up) {
      m_direction = down;
    }
    break;
  case SDL_SCANCODE_D:
  case SDL_SCANCODE_RIGHT:

    if (m_direction != left) {
      m_direction = right;
    }
    break;
  default:
    break;
  }
}

void Snake::move() {
  switch (m_direction) {
  case down:
    m_head.y += k_rect_size;
    break;
  case up:
    m_head.y -= k_rect_size;
    break;
  case left:
    m_head.x -= k_rect_size;
    break;
  case right:
    m_head.x += k_rect_size;
    break;
  }
  out_of_bounds();
};

void Snake::draw(SDL_Renderer *renderer) {
  for (SDL_FRect snake_segment : m_body) {
    SDL_SetRenderDrawColor(renderer, 143, 188, 143, 255);
    SDL_RenderFillRect(renderer, &snake_segment);
  }
  SDL_SetRenderDrawColor(renderer, 0, 255, 127, 255);
  SDL_RenderFillRect(renderer, &m_body[0]);
};

bool Snake::ate_food(SDL_Point food_cordinates) {
  if (m_head.x == food_cordinates.x && m_head.y == food_cordinates.y) {
    m_size++;
    return true;
  }
  return false;
};

bool Snake::ate_self() {
  for (SDL_FRect snake_segment : m_body) {
    if (m_head.x == snake_segment.x && m_head.y == snake_segment.y) {
      return true;
    }
  }
  return false;
};

void Snake::out_of_bounds() {
  if (m_head.x > k_window_width) {
    m_head.x = 0;
  } else if (m_head.x < 0) {
    m_head.x = k_window_width;
  } else if (m_head.y > k_window_height) {
    m_head.y = 0;
  } else if (m_head.y < 0) {
    m_head.y = k_window_height;
  }
};

void Snake::reset() {
  m_size = 1;
  m_head.x = k_window_width / 2;
  m_head.y = k_window_height / 2;
  m_body.clear();
};

void Snake::handle_size() {
  m_body.push_front(m_head);
  while (m_body.size() > m_size) {
    m_body.pop_back();
  }
};
