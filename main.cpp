#include "engine.hpp"

#define DEBUG

int main()
{
	std::cout << "Starting Engine" << std::endl;
	engine app;
	std::cout << "Created Engine" << std::endl;
	app.start();
	std::cout << "Exitting Engine" << std::endl;
	return 0;
}
