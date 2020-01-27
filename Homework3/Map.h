#ifndef MAP_H
#define MAP_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

using vertex = std::string;
using key = std::string;
using edge = std::pair<vertex, key>;
using graph = std::unordered_map<vertex, std::vector<edge>>;

// Used for making the game map 
// unordered_map is used for faster searching
// An edge is composed of a zone and a key to pass
// Not every edge needs a key to pass


struct GameMap
{
	GameMap();

	graph map;
};

// Adds a new edge to the map
void addEdge(GameMap&,const vertex&, const vertex&, const key = "no key");
bool hasZone(GameMap& ,const vertex&);

#endif // !MAP_H
