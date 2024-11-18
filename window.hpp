#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include "types.hpp"

#define W_HEIGHT 600
#define W_WIDTH 800

class window {
//private:
public:
	SDL_Window* sdl_window;
	SDL_Renderer* sdl_renderer;
	window();
	~window();
	uint32_t* pixels;
//public:
	void update();
	void setPixel(int x, int y, Uint32 color);
	void cleanBuffer(Uint32 color);
	bool withinBounds(Box bounds);
};
