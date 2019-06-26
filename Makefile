build:
	emcc ./game/*.c -o ./index.html -Wall -g -lm -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file ./game/assets/ball.png


