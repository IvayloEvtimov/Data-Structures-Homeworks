#ifndef HORO_H
#define HORO_H

#include <string>
#include <iostream>
#include <fstream>
#include "Constants.h"


//Class Horo resembles a Circular Linked List
//but with the help of Hash Table
//all of the methods in class Horo are O(1)
//except print()
class Horo
{
public:
	//This structure is a participant is the Horo
	//He has a name and pointers to his left and right neighbours
	//and a bool variable for whether he is holding them or not
	struct Data
	{
		Data(const std::string& name) :name(name), left(nullptr), grabLeft(false), right(nullptr), grabRight(false) {}


		std::string name;
		Data* left;
		bool grabLeft;
		Data* right;
		bool grabRight;
	};

	//The assigment operator and copy contructor are disabled because
	//There is only 1 Horo being played at any time
	Horo();
	Horo(const Horo&) = delete;
	Horo& operator=(const Horo&) = delete;
	~Horo();

	//Adds a new participant to the Horo
	//The only validaing being made is whether the left and the right are actually neighbours
	//The other checks are made in the System class
	//Only pointers are passed as arguments because
	//With the help of the Hash Table the object are quickly found
	void add(Data*, Data*, Data*);

	//Removes a Person from the Horo by deleting the object being pointed by the pointer
	//Validation is made in the System class
	void remove(Data*);

	//A person tries to grab either one or two of his neighbours
	//If he is already holding them an exception is thrown 
	void grab(Data*, const Grab&);

	//Same as grab() by here the Person tries to release from his neighbours
	void release(Data*, const Grab&);

	//Swaps two Persons
	//Validating is being made in the System class
	void swap(Data*&, Data*&);

	//Print a small info about the given participant
	void info(Data*&) const;

	//Prints the names of all of the participants
	//Starting with the first one to entered the Horo
	//And ending with the Last one to joind
	void print() const;

	//Checks if whether 2 participants are really neighbours
	//by validating their left and right pointers
	bool areNeighbours(const Data*, const Data*);

	//Validates whether a participant is being hold onto by anyone
	//Or if he is holding anyone
	//by checking grabLeft and grabRight variables
	bool isReleased(const Data*)const;

	//Used when the System is loading the innitial data from a file
	void loadFromFile(Data*&);
private:
	Data* top;
	int size;
};


#endif // !HORO_H
