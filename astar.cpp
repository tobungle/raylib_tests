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
	Tile current = end;
	std::vector<Tile> path;
	while (current.came_from != nullptr) {
		path.push_back(current);
		current = *current.came_from;
	}
	return path;
}

std::vector<Tile> CreateAStarPath(Tile &start, Tile &end) {
	std::vector<Tile*> open_list = { &start };	// Initialise open & closed lists
	std::vector<Tile*> closed_list;
	start.g_cost = 0;	// Initialise starting tile properties
	start.h_cost = HeuristicDistance(start, end);
	start.f_cost = start.g_cost + start.f_cost;
	start.came_from = nullptr;
	while (!open_list.empty()) {
		Tile* current = open_list[GetLowestFCost(open_list)];	// Evaluate tile with lowest f_cost in open_list
		if (CompareTiles(*current, end)) {	// Check if we're at the goal, if so then we're done
			std::cout << "A*: Found path!" << std::endl;
			return ReconstructPath(*current);
		}
		open_list.erase(open_list.begin() + TileAt(open_list, *current));	// Move current node from open_list to closed_list
		closed_list.push_back(current);
		std::vector<Tile*> cur_neighbours = GetNeighboursNoDiagonals(*current);
		for (Tile* neighbour : cur_neighbours) {	// Checking all neighbouring tiles
			if (TileIn(closed_list, *neighbour)) {	// Skip neighbour if it's in closed list
				continue;
			}
			int tentative_g_cost = current->g_cost + 1;	// Calculate g_cost
			if (!TileIn(open_list, *neighbour)) {	// Add neighbour to open list
				open_list.push_back(neighbour);
			}
			else if (tentative_g_cost >= neighbour->g_cost) {
				continue;	// This path is not better, skip!
			}
			neighbour->came_from = current;	// This is the best path so far
			neighbour->g_cost = tentative_g_cost;
			neighbour->h_cost = HeuristicDistance(*neighbour, end);
			neighbour->f_cost = neighbour->g_cost + neighbour->h_cost;
		}
	}
	std::cout << "A*: Could not find path." << std::endl;
	return std::vector<Tile> {};
}

