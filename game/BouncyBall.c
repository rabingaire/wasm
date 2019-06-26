//
// Created by Rabin Gaire on 2019-06-25.
//

#include "BouncyBall.h"
#include "math.h"

void init(struct BouncyBall *b)
{
  b->texture = NULL;
  b->x = 0;
  b->y = 0;
  b->dy = 0;
  b->elasticity = 0.5;
  b->gravity = 0.04;
}

void setTexture(struct BouncyBall *b, SDL_Texture *tex)
{
    b->texture = tex;
}

void draw(struct BouncyBall *b, SDL_Renderer *renderer, int BALL_SIZE)
{
  SDL_Rect rect = {b->x, b->y, BALL_SIZE, BALL_SIZE};
  SDL_RenderCopy(renderer, b->texture, NULL, &rect);
}

void update(struct BouncyBall *b, int WINDOW_HEIGHT, int BALL_SIZE)
{
  if(b->y + BALL_SIZE < WINDOW_HEIGHT)
  {
    b->y += b->dy;
    b->dy += b->gravity;
  }
  else
  {
    b->dy *= -b->elasticity;
    b->y += b->dy * 2;

    if(fabsf(b->dy) < 0.1)
    {
      b->dy = 0;
    }
  }
}

void setPosition(struct BouncyBall *b, float x, float y)
{
  b->x = x;
  b->y = y;
}

void setElasticity(struct BouncyBall *b, float e)
{
  b->elasticity = e;
}