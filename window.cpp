#include "window.hpp"

window::window()
{
	SDL_Init( SDL_INIT_EVERYTHING );

	this->pixels = new Uint32[W_WIDTH * W_HEIGHT];

	this->sdl_window = SDL_CreateWindow("sdl window", 100, 100, W_WIDTH, W_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!sdl_window)
		std::cout << "Failed to create a window. " << SDL_GetError() << std::endl;
	this->sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_SOFTWARE);
	if (!sdl_renderer)
		std::cout << "Failed to create a window. " << SDL_GetError() << std::endl;
}

window::~window()
{
	delete this->pixels;
	SDL_DestroyWindow(this->sdl_window);
	SDL_DestroyRenderer(this->sdl_renderer);
}

void window::update()
{
	SDL_RenderClear(this->sdl_renderer);
	SDL_Texture* texture = SDL_CreateTexture(
		this->sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, W_WIDTH, W_HEIGHT);
	SDL_UpdateTexture(texture, NULL, pixels, W_WIDTH * sizeof(Uint32));
	SDL_RenderCopy(this->sdl_renderer, texture, NULL, NULL);
	SDL_RenderPresent(this->sdl_renderer);
	SDL_DestroyTexture(texture);
}

void window::setPixel(int x, int y, Uint32 color)
{
	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
		pixels[y * W_WIDTH + x] = color;
}

void window::cleanBuffer(Uint32 color)
{
	int pixelCount = W_WIDTH * W_HEIGHT;
	for (int i = 0; i < pixelCount; this->pixels[i++] = color);
}

bool window::withinBounds(Box bounds)
{
	return (
		bounds.x >= 0 && 
		bounds.y >= 0 && 
		bounds.x+bounds.w < W_WIDTH && 
		bounds.y+bounds.h < W_HEIGHT
	);
}

