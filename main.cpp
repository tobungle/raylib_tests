#include <raylib.h>
#include "tilemap.hpp"
#include "astar.hpp"
#include "plotline.hpp"
#include "point.hpp"

const int screen_width = 800;
const int screen_height = 600;

Sound sounds[2];

struct NavPoint {
	int x;
	int y;
	bool exists;
};
NavPoint point1;
NavPoint point2;
bool nav_point_toggle = false;

std::vector<Tile> current_astar_path;

void RegenPath() {
	if (point1.exists && point2.exists) {
		current_astar_path = CreateAStarPath(
		grid[point1.x][point1.y], 
		grid[point2.x][point2.y]);
	}
	
}

void DrawAStarPath() {
	for (Tile tile : current_astar_path) {
		DrawRectangle((tile.x * tile_size)+tile_border, (tile.y * tile_size)+tile_border, tile_size-tile_border, tile_size-tile_border, RED);
		DrawRectangle((point1.x * tile_size)+tile_border, (point1.y * tile_size)+tile_border, tile_size-tile_border, tile_size-tile_border, YELLOW);
		DrawRectangle((point2.x * tile_size)+tile_border, (point2.y * tile_size)+tile_border, tile_size-tile_border, tile_size-tile_border, PURPLE);
	}
}

void DrawLinePlot(int x1, int y1, int x2, int y2) {
	Point p1;
	p1.x = x1;
	p1.y = y1;
	Point p2;
	p2.x = x2;
	p2.y = y2;
	std::vector<Point> line = PlotLine(p1, p2);
	for (int i = 0; i < line.size(); i ++) {
		Point p = line[i];
		DrawRectangle((p.x * tile_size)+tile_border, (p.y * tile_size)+tile_border, tile_size-tile_border, tile_size-tile_border, GREEN);
	}
}

void HandleMouseInput() {
	if (IsMouseButtonDown(0)) {
		int x = GetMouseX() / tile_size;
		int y = GetMouseY() / tile_size;
		if (InBounds(x, y)) {
			if (grid[x][y].type == None) {
				StopSound(sounds[0]);
				PlaySound(sounds[0]);
				grid[x][y].type = Wall;
				RegenPath();
			} else {
				grid[x][y].type = Wall;
				RegenPath();
			}
		}
	}
	if (IsMouseButtonPressed(1)) {
		PlaySound(sounds[1]);
		ClearTilemap();
		RegenPath();
	}
	if (IsMouseButtonPressed(2)) {
		
		int x = GetMouseX() / tile_size;
		int y = GetMouseY() / tile_size;
		
		if (nav_point_toggle) {
			point1.exists = true;
			point1.x = x;
			point1.y = y;
		} else {
			point2.exists = true;
			point2.x = x;
			point2.y = y;
		}
		RegenPath();
		nav_point_toggle = !nav_point_toggle;
	}
}

void LoadAssets() {
	sounds[0] = LoadSound("make_wall.wav");
	SetSoundVolume(sounds[0], 0.25f);
	sounds[1] = LoadSound("clear_wall.wav");
}

void UnloadAssets() {
	for (int i = 0; i < sizeof(sounds) / sizeof(sounds[0]); i ++) {
		UnloadSound(sounds[i]);
	}
}

int main(void) {
	InitAudioDevice();
	LoadAssets();
	InitWindow(screen_width, screen_height, "RaylibTest");
	SetTargetFPS(60);
	InitTilemap();
	while (!WindowShouldClose()) {
		HandleMouseInput();
		BeginDrawing();
		ClearBackground(WHITE);
		DrawTilemap();
		DrawAStarPath();
		DrawText("[LMB] Draw tile\n[RMB] Clear tiles\n[MMB] Create navigation point", 10, screen_height - 70, 20, BLACK);
		DrawLinePlot(0, 0, GetMouseX() / tile_size, GetMouseY() / tile_size);
		EndDrawing();
	}
	UnloadAssets();
	CloseAudioDevice();
	CloseWindow();
	return 0;
}
