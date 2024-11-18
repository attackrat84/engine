#include "draw.hpp"

// TODO: replace Line2D with Line1D in Triangle2D
// TODO: cleanup code

// Bersenham's line algorithm (modified for color)
void draw::Line2D(Line &line, Uint32* pixelBuffer)
{
	int x1 = line.p1.x;
	int y1 = line.p1.y;
	int x2 = line.p2.x;
	int y2 = line.p2.y;

	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;
	
	int dist = sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));

	Uint8 r1 = (line.c1 & 0x00ff0000) >> 16;
	Uint8 g1 = (line.c1 & 0x0000ff00) >> 8;
	Uint8 b1 = line.c1 & 0x000000ff;

	Uint8 r2 = (line.c2 & 0x00ff0000) >> 16;
	Uint8 g2 = (line.c2 & 0x0000ff00) >> 8;
	Uint8 b2 = line.c2 & 0x000000ff;

	float dr = ((float)r2 - r1) / dist;
	float dg = ((float)g2 - g1) / dist;
	float db = ((float)b2 - b1) / dist;

	float r = r1, g = g1, b = b1;

	while(true) {
		if (x1 >= 0 && x1 < W_WIDTH && y1 >= 0 && y1 < W_HEIGHT) {
			pixelBuffer[y1 * W_WIDTH + x1] = (Uint32)((int)r << 16 | (int)g << 8 | (int)b);
		}

		r += dr;
		g += dg;
		b += db;
		if (x1 == x2 && y1 == y2) break;

		int e2 = err * 2;

		if (e2 > -dy) {
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y1 += sy;
		}
	}
}

void draw::Triangle2D_w(Triangle triangle, Uint32* pixelBuffer)
{
	Line l1 = Line(triangle.v[0], triangle.v[1], triangle.c[0], triangle.c[1]);
	Line l2 = Line(triangle.v[1], triangle.v[2], triangle.c[1], triangle.c[2]);
	Line l3 = Line(triangle.v[2], triangle.v[0], triangle.c[2], triangle.c[0]);
	Line2D(l1, pixelBuffer);
	Line2D(l2, pixelBuffer);
	Line2D(l3, pixelBuffer);
}

void draw::Triangle2D(Triangle triangle, Uint32* pixelBuffer)
{
	Line l1 = Line(triangle.v[0], triangle.v[1], triangle.c[0], triangle.c[1]);
	Line l2 = Line(triangle.v[1], triangle.v[2], triangle.c[1], triangle.c[2]);
	Line l3 = Line(triangle.v[2], triangle.v[0], triangle.c[2], triangle.c[0]);
	// attempt to get every point (god damn it)
	int dy;
	// get x and y difference
	dy = std::max(std::max(std::max(l1.p1.y, l1.p2.y), l2.p1.y), std::max(std::max(l2.p2.y, l3.p1.y), l3.p2.y)) -
	std::min(std::min(std::min(l1.p1.y, l1.p2.y), l2.p1.y), std::min(std::min(l2.p2.y, l3.p1.y), l3.p2.y));
	// init pointList to store all X coords
	std::vector<std::vector<int>> pointList(dy+1);
	int sty = std::min(std::min(std::min(l1.p1.y, l1.p2.y), l2.p1.y), std::min(std::min(l2.p2.y, l3.p1.y), l3.p2.y));
	// bersenham's line algo, modified to store X coordinates in Y.
	for (int i = 0; i < 3; i++) {
		int k = (i != 2) ? i + 1 : 0;

		int x1 = triangle.v[i].x;
		int y1 = triangle.v[i].y;
		int x2 = triangle.v[k].x;
		int y2 = triangle.v[k].y;

		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);
		int sx = (x1 < x2) ? 1 : -1;
		int sy = (y1 < y2) ? 1 : -1;
		int err = dx - dy;
	
		int dist = sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));

		Uint8 r1,g1,b1,r2,g2,b2,a;

		decomposeColor(triangle.c[i],r1,g1,b1,a);
		decomposeColor(triangle.c[k],r2,g2,b2,a);

		float dr = ((float)r2 - r1) / dist;
		float dg = ((float)g2 - g1) / dist;
		float db = ((float)b2 - b1) / dist;

		float r = r1, g = g1, b = b1;
	
		while(true) {
			if (x1 >= 0 && x1 < W_WIDTH && y1 >= 0 && y1 < W_HEIGHT) {
				pixelBuffer[y1 * W_WIDTH + x1] = (Uint32)((int)r << 16 | (int)g << 8 | (int)b);
				if ((y1-sty) >= 0 && (y1-sty) < (int)pointList.size())
					pointList[y1-sty].push_back(x1);
			}

			r += dr;
			g += dg;
			b += db;
			if (x1 == x2 && y1 == y2) break;

			int e2 = err * 2;

			if (e2 > -dy) {
				err -= dy;
				x1 += sx;
			}
			if (e2 < dx) {
				err += dx;
				y1 += sy;
			}
		}
	}
	// now that pointList is populated, we can find the gaps
	for (int i = 0; i < (int)pointList.size(); i++) {
		int prevVal,curVal;
		for (int k = 1; k < (int)pointList[i].size(); k++) {
			prevVal = pointList[i][k-1];
			if (abs((curVal = pointList[i][k]) - prevVal) != 1 && (int)pointList[i].size() > 1) {
				pointList[i].clear();
				pointList[i][0] = curVal;
				pointList[i][1] = prevVal;
				break;
			}
		}
	}
	// now that pointList is sorted, we can draw Line1Ds from each point
	for (int i = 0; i < (int)pointList.size(); i++) {
		Line line = Line(
			Vector2i(pointList[i][0], i+sty),
			Vector2i(pointList[i][1], i+sty),
			pixelBuffer[(i+sty) * W_WIDTH + pointList[i][1]], // colors arent stored
			pixelBuffer[(i+sty) * W_WIDTH + pointList[i][0]] // WARN: colors are reversed?
		);
		Line1D(line, pixelBuffer);
	}
}

// drawing 'Spans'
void draw::Line1D(Line &line, Uint32* pixelBuffer)
{
	if ((line.p1.x != line.p2.x) && (line.p1.y != line.p2.y)) // not 1 Dimensional
		return;
	int p1;
	int p2;
	int x;
	int y;
	int dir;

	if (line.p1.x != line.p2.x) { // direction
		x = p1 = std::min(line.p1.x, line.p2.x);
		p2 = std::max(line.p1.x, line.p2.x);
		y = line.p1.y;
		dir = 0;
	} else {
		y = p1 = std::min(line.p1.y, line.p2.y);
		p2 = std::max(line.p1.y, line.p2.y);
		x = line.p1.x;
		dir = 1;
	}
	Uint8	r1,g1,b1,a,
		r2,g2,b2;
	int dist = abs(p2-p1);

	decomposeColor(line.c1, r1,g1,b1,a); // populate rgb values, alpha doesnt matter
	decomposeColor(line.c2, r2,g2,b2,a);

	float dr = ((float)r2 - r1) / dist;
	float dg = ((float)g2 - g1) / dist;
	float db = ((float)b2 - b1) / dist;

	float r = r1, g = g1, b = b1;

	for (int i = p1; i < p2; i++) {
		pixelBuffer[y * W_WIDTH + x] = (Uint32)((Uint8)r << 16 | (Uint8)g << 8 | (Uint8)b);
		r += dr;
		g += dg;
		b += db;
		if (dir == 0)
			x++;
		else
			y++;
	}
}

void draw::decomposeColor(Uint32 argb, Uint8 &r, Uint8 &g, Uint8 &b, Uint8 &a)
{
	a = (argb >> 24) & 0xff;
	r = (argb >> 16) & 0xff;
	g = (argb >> 8) & 0xff;
	b = argb & 0xff;
}

/*
 * In memory of old line algorithm:
 *
	int dx, dy, b, by, bx, c;
	float m;
	dx = (p1.x > p2.x)? (bx = p1.x) - (c = p2.x) : (bx = p2.x) - (c = p1.x);
	dy = (p1.y > p2.y)? (by = p1.y) - (b = p2.y) : (by = p2.y) - (b = p1.y);
	// y=mx+b
	m = (float)dy/(float)dx;
	float y;
	for (int i = c; i < bx; i++) {
		y = m * (i-c) + b;
		pixelBuffer[(int)y * W_WIDTH + i] = color;
		std::cout << "\t{" << i << ", " << (int)y << "}" << std::endl;
	}
	std::cout << "{" << p1.x << ", " << p1.y << "}, {" << p2.x << ", " << p2.y << "}" << std::endl;
*/
