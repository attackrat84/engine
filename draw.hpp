#pragma once
#include "window.hpp"
#include "types.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

namespace draw {
	void Line2D(Line &line, Uint32* pixelBuffer);
	void Triangle2D_w(Triangle triangle, Uint32* pixelBuffer);
	void Triangle2D(Triangle triangle, Uint32* pixelBuffer);
	
	void Line1D(Line &line, Uint32* pixelBuffer);
	
	void decomposeColor(Uint32 argb, Uint8 &r, Uint8 &g, Uint8 &b, Uint8 &a);
};
