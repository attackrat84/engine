#pragma once
#include "window.hpp"
#include "draw.hpp"

class engine {
	int x, y, xvel, yvel;
	bool exitEngine;
	window* main_window;
	void input();	// process input
	void process();	// modify buffer
	void draw();	// render the buffer
public:
	void start(); // this function needs to be called in main.cpp

	engine();
	~engine();
};
