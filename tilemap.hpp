#pragma once
#include <vector>
#include <math.h>
#include <iostream>
#include <raylib.h>

enum TileType {
	None,
	Wall
};

struct Tile {
	int x;	// Tile info
	int y;
	TileType type;
	float g_cost;	// Pathfinding helper stuff
	float h_cost;
	float f_cost;
	Tile* came_from;
};

const int tile_size = 16;
const int tile_border = 2;
const int rows = 49;
const int columns = 37;

extern Tile grid[rows][columns];

bool InBounds(int x, int y);

bool CompareTiles(Tile &a, Tile &b);

void InitTilemap();

void ClearTilemap();

void DrawTilemap();

std::vector<Tile*> GetNeighbours(Tile &tile);	// Get neighbouring tiles

std::vector<Tile*> GetNeighboursNoDiagonals(Tile &tile);

int TileAt(std::vector<Tile*> &vector, Tile &tile);	// What is the index of the given tile in the given vector

bool TileIn(std::vector<Tile*> &vector, Tile &tile);	// Does the given vector contain the given tile
