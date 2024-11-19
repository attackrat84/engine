#include "engine.hpp"

engine::engine()
{
	xvel = 0;
	yvel = 0;
	x = W_WIDTH/2-1;
	y = W_HEIGHT/2-1;
	this->exitEngine = false;
	this->main_window = new window;
}

engine::~engine()
{
	delete main_window;
}

void engine::start()
{
	while (!exitEngine) {
		engine::input();
		engine::process();
		engine::draw();
		SDL_Delay(16); // about 15 fps
	}
}

void engine::input()
{
	// process EVENTS
	SDL_Event ev;
	while (SDL_PollEvent(&ev) != 0) {
		switch (ev.type) {
		case SDL_QUIT:
			exitEngine = true;
			break;
		case SDL_KEYDOWN:
			switch (ev.key.keysym.sym) {
			case SDLK_w:
				yvel = -5;
				break;
			case SDLK_s:
				yvel = 5;
				break;
			case SDLK_a:
				xvel = -5;
				break;
			case SDLK_d:
				xvel = 5;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (ev.key.keysym.sym) {
			case SDLK_w:
			case SDLK_s:
				yvel = 0;
				break;
			case SDLK_a:
			case SDLK_d:
				xvel = 0;
				break;
			}
			break;
		}
	}
}

void engine::process()
{
	x += xvel;
	y += yvel;
}

void engine::draw()
{
	this->main_window->cleanBuffer(0x00000000);
	Triangle triangle1 = Triangle(
		Vector2i(x,y), Vector2i(99, 50), Vector2i(699,50),
		0x00ff0000, 0x0000ff00, 0x000000ff
	);
	draw::Triangle2D(triangle1, this->main_window->pixels);
	this->main_window->update();
}
