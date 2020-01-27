#ifndef SYSTEM_H
#define SYSTEM_H

#include <fstream>

#include <unordered_set>

#include "KeysInZone.h"
#include "Map.h"

// Includes all the functions required to run the program
// Copy constructor and Assigment operator are disabled because 
// only one unique instance should be running

class System
{
public:
	System();
	System(const System&) = delete;
	System& operator=(const System&) = delete;
	~System()=default;

	// Generates a map of zones and keys based on the given file
	void load(std::ifstream&);
	// Find the unreachable zones and generates a dot based file of the map
	// Uses dfs to search through the map
	void findUnreachable(const vertex&);
private:
	// Used for looking for a specific char during the loading of the file
	bool lookForChar(const char, std::ifstream&);
	// DFS search for finding unreachable zones
	void dfsSearch(const vertex&, std::unordered_set<vertex>&, std::unordered_set<key>, bool = false);
	// Generates a .dot file for the entire map
	// with different labels for each zone depending on 
	// wheather the zone has a key or been visited
	void exportGraph(std::ofstream&, std::unordered_set<vertex>);
	void addLabel(std::ofstream&,const vertex&, const bool, std::vector<key>);
	void outputZones(std::ofstream&, const std::unordered_set<std::string>&);
	std::unordered_set<key> dfsWrapper(const vertex&,std::unordered_set<key>&);
private:
	GameMap map;
	KeysInZone zones;
};


#endif // !SYSTEM_H
