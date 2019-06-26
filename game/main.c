#include <stdio.h>
#include "SDL.h"
#include "SDL_Image.h"
#include "BouncyBall.h"
#include "math.h"
#include "emscripten.h"

static const int nBalls = 10;
static struct BouncyBall balls[nBalls];
static int WINDOW_WIDTH = 640, WINDOW_HEIGHT = 480;
static int BALL_SIZE = 32;

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Event event;

void doRender(SDL_Renderer *renderer)
{
  SDL_SetRenderDrawColor(renderer, 240, 240, 255, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  for (int i = 0; i < nBalls; i++)
  {
    draw(&balls[i], renderer, BALL_SIZE);
  }
  SDL_RenderPresent(renderer);
}

void mainloop()
{
  int quit = 0;

  const Uint8 *state = SDL_GetKeyboardState(NULL);

  if (state[SDL_SCANCODE_ESCAPE])
  {
    quit = 1;
  }

  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      break;
    }
  }

  for (int i = 0; i < nBalls; i++)
  {
    update(&balls[i], WINDOW_HEIGHT, BALL_SIZE);
  }

  doRender(renderer);

  if (quit == 1)
  {
    emscripten_cancel_main_loop();
    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();
  }
}

int main()
{
  SDL_Texture *texture;

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow(
      "Test",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WINDOW_WIDTH,
      WINDOW_HEIGHT,
      SDL_WINDOW_OPENGL);

  if (window == NULL)
  {
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Surface *image;

  image = IMG_Load("./game/assets/ball.png");
  if (!image)
  {
    printf("IMG_Load: %s\n", IMG_GetError());
    return 1;
  }
  texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);

  for (int i = 0; i < nBalls; i++)
  {
    init(&balls[i]);
    setTexture(&balls[i], texture);
    setPosition(&balls[i], 50 + i * BALL_SIZE, 100);
    setElasticity(&balls[i], (float)i / nBalls);
  }

  emscripten_set_main_loop(mainloop, 0, 1);

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(texture);
  SDL_Quit();
  return 0;
}