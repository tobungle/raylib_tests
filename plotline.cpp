#include "plotline.hpp"

std::vector<Point> PlotLine(Point from, Point to) {
	if (abs(to.x - from.x) > abs(to.y - from.y)) {
		return PlotLineH(from, to);
	}
	return PlotLineV(from, to);
}

std::vector<Point> PlotLineH(Point from, Point to) {
	std::vector<Point> result;
	if (from.x > to.x) {
		int x0 = from.x;
		int x1 = to.x;
		int y0 = from.y;
		int y1 = to.y;
		from.x = x1;
		to.x = x0;
		from.y = y1;
		to.y = y0;
	}
	int dx = to.x - from.x;
	int dy = to.y - from.y;
	int dir = -1;
	if (dy >= 0) {
		dir = 1;
	}
	dy *= dir;
	if (dx != 0) {
		int y = from.y;
		int p = 2 * dy - dx;
		for (int i = 0; i <= dx; i ++) {
			Point new_point;
			new_point.x = from.x + i;
			new_point.y = y;
			result.push_back(new_point);
			if (p >= 0) {
				y += dir;
				p = p - 2 * dx;
			}
			p = p + 2 * dy;
		}
	}
	return result;
}

std::vector<Point> PlotLineV(Point from, Point to) {
	std::vector<Point> result;
	if (from.y > to.y) {
		int x0 = from.x;
		int x1 = to.x;
		int y0 = from.y;
		int y1 = to.y;
		from.x = x1;
		to.x = x0;
		from.y = y1;
		to.y = y0;
	}
	int dx = to.x - from.x;
	int dy = to.y - from.y;
	int dir = -1;
	if (dy >= 0) {
		dir = 1;
	}
	dx *= dir;
	if (dy != 0) {
		int x = from.x;
		int p = 2 * dx - dy;
		for (int i = 0; i <= dy; i ++) {
			Point new_point;
			new_point.x = x;
			new_point.y = from.y + i;
			result.push_back(new_point);
			if (p >= 0) {
				x += dir;
				p = p - 2 * dy;
			}
			p = p + 2 * dx;
		}
	}
	return result;
}
