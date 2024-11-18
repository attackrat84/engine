#include "types.hpp"

Vector2i::Vector2i(int x, int y)
{
	this->x = x;
	this->y = y;
}

Line::Line(Vector2i p1, Vector2i p2, Uint32 c1, Uint32 c2)
	: p1(p1), p2(p2), c1(c1), c2(c2)
{
	this->p1 = p1;
	this->p2 = p2;
	this->c1 = c1;
	this->c2 = c2;
}

Triangle::Triangle(Vector2i v1, Vector2i v2, Vector2i v3, Uint32 c1, Uint32 c2, Uint32 c3)
	: v{v1,v2,v3}, c{c1,c2,c3}
{
	this->v[0] = v1;
	this->v[1] = v2;
	this->v[2] = v3;
	this->c[0] = c1;
	this->c[1] = c2;
	this->c[2] = c3;
}
