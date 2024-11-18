#pragma once
#include <SDL2/SDL_stdinc.h>
struct Vector2i {
	Vector2i(int x, int y);
	int x;
	int y;
};
struct Vector3i {
	int x;
	int y;
	int z;
};
struct Box {
	int x;
	int y;
	int w;
	int h;
};
struct Triangle {
	Triangle(Vector2i v1, Vector2i v2, Vector2i v3, Uint32 c1, Uint32 c2, Uint32 c3);
	Vector2i v[3];
	Uint32 c[3];
};
struct Line {
	Line(Vector2i p1, Vector2i p2, Uint32 c1, Uint32 c2);
	Vector2i p1;
	Vector2i p2;
	Uint32 c1;
	Uint32 c2;
};
