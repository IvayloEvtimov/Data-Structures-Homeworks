#include "Map.h"

GameMap::GameMap():map()
{
}

void addEdge(GameMap& obj,const vertex &startZone, const vertex &endZone, const key keyName)
{
	edge temp(endZone, keyName);
	obj.map[startZone].push_back(temp);
}

bool hasZone(GameMap& obj,const vertex &zone)
{
	if (obj.map.count(zone) == 0)
		return false;
	else
		return true;
}
