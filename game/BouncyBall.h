//
// Created by Rabin Gaire on 2019-06-25.
//

#ifndef BOUNCY_BALL_BOUNCYBALL_H
#define BOUNCY_BALL_BOUNCYBALL_H

#include "SDL.h"

struct BouncyBall
{
    SDL_Texture *texture;
    float x, y;
    float dy;
    float elasticity;
    float gravity;
};

void init(struct BouncyBall *b);
void setTexture(struct BouncyBall *b, SDL_Texture *tex);
void draw(struct BouncyBall *b, SDL_Renderer *renderer, int BALL_SIZE);
void update(struct BouncyBall *b, int WINDOW_HEIGHT, int BALL_SIZE);
void setPosition(struct BouncyBall *b, float x, float y);
void setElasticity(struct BouncyBall *b, float e);


#endif //BOUNCY_BALL_BOUNCYBALL_H
