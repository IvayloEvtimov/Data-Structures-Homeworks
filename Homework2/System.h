#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <fstream>

#include "Constants.h"
#include "HashTable.h"
#include "Horo.h"

#include <fstream>


//System class which handles the processing of commands
//and validating the inputed data
class System
{
public:
	//Copy constructor and assigment operator are disabled because
	//there must be only 1 active object of class System
	//and there is no need for making copies
	System(const int=20);
	System(const System&) = delete;
	System& operator=(const System&) = delete;
	~System() = default;


	//By giving a name of a person and with the help of the Hash Table
	//an object with the same name should be found 
	//and if it is not an exception will be fired
	//And after being found he will release the left, right or both of his neighbours
	//It depends on the second argument 
	void release(const std::string&,const Grab&);

	//Same of release but the person will grab his neighbours 
	void grab(const std::string & , const Grab&);

	//Print a short info about a person, if the given name is valid, and whether or not
	//he is not his neighbours
	void info(const std::string & );

	//Adds a new Person to the Horo but first he must be checked if he is already in 
	//If he is then an exception is thrown
	//Also his neighbours are also be checked whether they really are neighbours
	void add(const std::string&, const std::string&, const std::string&);

	//Removes a Person from the Horo, but first he is checked whether
	//he is part of it and whether he has released his neighbours
	//and his neighbours have released him
	//If there are less than 3 person, the program stops
	void remove(const std::string&);

	//By giving two names the are validated if they are correct
	//and if those two persons are really neighbours and nobody is holding them
	//they swap places
	void swap(const std::string& , const std::string&);

	//Print all the participants in the Horo
	//Starts with the first one who joined
	//and ends with the last one to enter
	void print() const;

	//Begins the Horo by extracting the names of the participants
	//If the participants are less than 3
	//The program stops
	void loadFromFile(std::ifstream&);
private:
	//This object is the Horo
	//Its structure is like a Circular Linked List
	//Because the First Person is next to the Last
	Horo DanceFloor;

	//A hash table used for storing the pointers to the participants
	//for quick search and access
	HashTable Table;
};

#endif // !SYSTEM_H
