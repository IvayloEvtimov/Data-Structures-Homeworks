#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>

#include "Horo.h"


//Hash Table used for storing an array of pointers to objects
//for faster search and access
class HashTable
{
public:
	//Copy constructor and assigment operator are disabled because
	//there must be only 1 active object of class HashTable
	//and there is no need for making copies
	HashTable(const int);
	HashTable(const HashTable&) = delete;
	HashTable& operator=(const HashTable&) = delete;
	~HashTable() = default;

	//By providing key, a pointer to Data is stored in a given index in the array
	void insert(const std::string&, Horo::Data*);

	//Removes a pointer from the array by providing the key
	//Only the pointer is removed and the object it points to
	void remove(const std::string&);

	//By providing a key, tries to find a pointer to object Data
	//by using the hashFunc method
	Horo::Data*& find(const std::string&);
private:
	//Used for hashing a given key into a index for the array
	int hashFunc(const std::string&, const int) const;

	//Rehashes the whole Array because too many collisions are made
	void rehash();
private:
	std::vector<std::list<Horo::Data*>> Array;
	int size;
	const int maxChaningSize = 5;
};

#endif // !HASHTABLE_H
