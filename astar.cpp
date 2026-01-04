#include "astar.hpp"

float HeuristicDistance(Tile &from, Tile &to) {
	float x = (float) (fabs(from.x - to.x));
	float y = (float) (fabs(from.y - to.y));
	return x + y;
}

int GetLowestFCost(std::vector<Tile*> &tiles) {
	int lowest_f = 0;
	for (int i = 0; i < tiles.size(); i ++) {
		if (tiles[i]->f_cost < tiles[lowest_f]->f_cost) {
			lowest_f = i;
		}
	}
	return lowest_f;
}

std::vector<Tile> ReconstructPath(Tile end) {
	std::cout << "Final tile came from: " << end.came_from << std::endl;
	Tile current = end;
	std::vector<Tile> path;
	while (current.came_from != nullptr) {
		path.push_back(current);
		current = *current.came_from;
	}
	return path;
}

std::vector<Tile> CreateAStarPath(Tile &start, Tile &end) {
	// Initialise lists
	std::vector<Tile*> open_list = { &start };
	std::vector<Tile*> closed_list;
	// Initialise starting tile properties
	start.g_cost = 0;
	start.h_cost = HeuristicDistance(start, end);
	start.f_cost = start.g_cost + start.f_cost;
	start.came_from = nullptr;
	
	while (!open_list.empty()) {
		// Get tile with lowest f_cost
		Tile* current = open_list[GetLowestFCost(open_list)];
		std::cout << "A*: Evaluating tile " << current->x << " " << current->y << std::endl;
		// Check if we've reached the goal
		if (CompareTiles(*current, end)) {
			std::cout << "Found A* path!" << std::endl;
			return ReconstructPath(*current);
		}
		// Move current node from open_list to closed_list
		open_list.erase(open_list.begin() + TileAt(open_list, *current));
		closed_list.push_back(current);
		// Check all neighbouring tiles
		std::vector<Tile*> cur_neighbours = GetNeighboursNoDiagonals(*current);
		for (Tile* neighbour : cur_neighbours) {
			std::cout << "A*: Evaluating neighbour " << neighbour->x << " " << neighbour->y << std::endl;
			// Skip neighbour if it's in closed list
			if (TileIn(closed_list, *neighbour)) {
				std::cout << "A*: Skipping neighbour " << neighbour->x << " " << neighbour->y << " in closed list" << std::endl;
				continue;
			}
			// Calculate g_cost
			int tentative_g_cost = current->g_cost + 1;	// Tentative is a lovely word
			
			if (!TileIn(open_list, *neighbour)) {
				open_list.push_back(neighbour);
				std::cout << "A*: Adding neighbour " << neighbour->x << " " << neighbour->y << " to open list" << std::endl;
			}
			else if (tentative_g_cost >= neighbour->g_cost) {
				continue;	// This path is not better
			}
			std::cout << "A*: Best neighbour found " << neighbour->x << " " << neighbour->y << std::endl;
			// This is the best neighbour path so far, record it.
			neighbour->came_from = current;
			neighbour->g_cost = tentative_g_cost;
			neighbour->h_cost = HeuristicDistance(*neighbour, end);
			neighbour->f_cost = neighbour->g_cost + neighbour->h_cost;
		}
	}
	std::cout << "Could not find A* path. Sad!" << std::endl;
	return std::vector<Tile> {};
}

