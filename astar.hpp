#pragma once
#include <vector>
#include <math.h>
#include <map>
#include "tilemap.hpp"

float HeuristicDistance(Tile &from, Tile &to);

float GetLowestFCost(std::vector<Tile> *tiles);

std::vector<Tile> ReconstructPath(Tile end);

std::vector<Tile> CreateAStarPath(Tile &start, Tile &end);
