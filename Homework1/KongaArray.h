#ifndef KONGAARRAY_H
#define KONGAARRAY_H

#include "KongaList.h"

class KongaArray
{
public:
	//Big 4
	KongaArray();
	KongaArray(const KongaArray&)=delete; //Copy Constructor is forbidden because only 1 dynamic array is needed at all times
	KongaArray& operator=(const KongaArray&)=delete; //Asignment operator is forbidden because only 1 dynamic array is needed at all times
	~KongaArray();

	void append(const char*,const char*,const int); //Adds new Student ,if valid, to a given List
	void removeLast(const int); //Removes the last Student of a given List
	void removeFirst(const int); //Removes the first Student of a given List
	void removeElem(const char*, const int); //Removes a specified Student from a given List and creates a new List with the other Students after him
	void merge(const int&, const int&);
	void print() const; //Prints all the Students in all of the Lists

	bool isEmpty() const; //Checks if there are any Lists left in the Array
private:
	void newList( KongaList*);  //Adds new List to the Array
	void removeList(const int); //Removes a given List
	void resize(); //Increases the maximum capacity of the Array
private:
	KongaList** lists;
	int size;
	int max;
};

#endif // !KONGAARRAY_H
