#ifndef KEYHASH_H
#define KEYHASH_H

#include <string>
#include <vector>
#include <unordered_map>

using key = std::string;
using vertex = std::string;

// Used for storing the keys in each zone
// unordered_map is used for faster search and insert

class KeysInZone
{
public:
	KeysInZone() :keys() {}
	KeysInZone(const KeysInZone&) = delete;
	KeysInZone& operator=(const KeysInZone&) = delete;
	~KeysInZone() = default;
	
	// Adds a new key by giving the zone 
	void insert(const vertex&, const key&);
	// Finds and return all the keys in a given zone
	// There may be more than one key in a zone
	std::vector<key> find(const vertex&);
	//Checks if the given zone has any keys
	bool hasKeys(const vertex&) const;

private:
	std::unordered_map<vertex,std::vector<key>> keys;
};
#endif // !KEYHASH_H
