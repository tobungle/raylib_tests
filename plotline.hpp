#pragma once
#include <vector>
#include <cstdlib>	// For abs?
#include "point.hpp"

std::vector<Point> PlotLine(Point from, Point to);
std::vector<Point> PlotLineH(Point from, Point to);
std::vector<Point> PlotLineV(Point from, Point to);
