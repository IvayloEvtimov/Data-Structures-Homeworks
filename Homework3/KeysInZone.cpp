#include "KeysInZone.h"

void KeysInZone::insert(const vertex &zone, const key &newKey)
{
	keys[zone].push_back(newKey);
}

std::vector<key> KeysInZone::find(const vertex &zone)
{
	if (keys.count(zone) != 0)
		return keys[zone];

	std::vector<key> temp;
	return temp;
}

bool KeysInZone::hasKeys(const vertex &zone) const
{
	return keys.count(zone);
}
