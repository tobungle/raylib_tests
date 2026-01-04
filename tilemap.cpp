#include "tilemap.hpp"

Tile grid[rows][columns];

bool InBounds(int x, int y) {
	return x < rows && x >= 0 && y < columns && y >= 0;
}

bool CompareTiles(Tile &a, Tile &b) {
	return a.x == b.x && a.y == b.y;
}

void InitTilemap() {
	for (int x = 0; x < rows; x ++) {
		for (int y = 0; y < columns; y ++) {
			grid[x][y].x = x;
			grid[x][y].y = y;
		}
	}
}

void ClearTilemap() {
	for (int x = 0; x < rows; x ++) {
		for (int y = 0; y < columns; y ++) {
			grid[x][y].type = None;
		}
	}
}

void DrawTilemap() {
	for (int x = 0; x < rows; x ++) {
		for (int y = 0; y < columns; y ++) {
			switch (grid[x][y].type) {
				case None:
				DrawRectangle((x * tile_size)+tile_border, (y * tile_size)+tile_border, tile_size-tile_border, tile_size-tile_border, RAYWHITE);
				break;
				case Wall:
				DrawRectangle((x * tile_size)+tile_border, (y * tile_size)+tile_border, tile_size-tile_border, tile_size-tile_border, BLACK);
				break;
			}
		}
	}
}

std::vector<Tile*> GetNeighbours(Tile &tile) {
	std::vector<Tile*> neighbours;
	int neighbour_positions[8][2] = {
		{-1,  0},
		{-1,  1},
		{ 0,  1},
		{ 1,  1},
		{ 1,  0},
		{ 1, -1},
		{ 0, -1},
		{-1, -1},
	};
	for (int i = 0; i < 8; i ++) {
		int x = tile.x + neighbour_positions[i][0];
		int y = tile.y + neighbour_positions[i][1];
		if (InBounds(x, y)) {
			if (grid[x][y].type != Wall) {
				neighbours.push_back(&grid[x][y]);
			}
		}
	}
	return neighbours;
}

std::vector<Tile*> GetNeighboursNoDiagonals(Tile &tile) {
	std::vector<Tile*> neighbours;
	int neighbour_positions[4][2] = {
		{-1,  0},
		{ 0,  1},
		{ 1,  0},
		{ 0, -1},
	};
	for (int i = 0; i < 4; i ++) {
		int x = tile.x + neighbour_positions[i][0];
		int y = tile.y + neighbour_positions[i][1];
		if (InBounds(x, y)) {
			if (grid[x][y].type != Wall) {
				neighbours.push_back(&grid[x][y]);
			}
		}
	}
	return neighbours;
}

int TileAt(std::vector<Tile*> &vector, Tile &tile) {
	for (int i = vector.size() - 1; i >= 0; i --) {
		if (CompareTiles(*vector[i], tile)) {
			return i;
		}
	}
	return -1;
}

bool TileIn(std::vector<Tile*> &vector, Tile &tile) {
	for (int i = vector.size() - 1; i >= 0; i --) {
		if (CompareTiles(*vector[i], tile)) {
			return true;
		}
	}
	return false;
}
