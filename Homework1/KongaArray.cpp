#include "KongaArray.h"

#include <iostream>

KongaArray::KongaArray():lists(nullptr),size(0),max(4)
{
	lists = new KongaList*[max];
	lists[size++] = new KongaList();
	lists[0]->append("Integralcho", "fmi");
}

KongaArray::~KongaArray()
{
	for (int count = 0; count < size; ++count)
		delete lists[count];
	delete[] lists;
}

void KongaArray::newList( KongaList* toAdd) //Adds new List to the Array
{
	if (size == max) 
		resize();
	lists[size++] = toAdd;
}

void KongaArray::append(const char *name, const char *uni, const int index) //Adds new Student to a existing List
{
	if (index >= size || index < 0) //Checks if the given index is valid
		throw std::out_of_range("Invalid index");

	lists[index]->append(name, uni);
}

void KongaArray::removeLast(const int index) //Removes the last Student from a given List
{
	if (index >= size || index < 0) //Checks if the given index is valid
		throw std::out_of_range("Invalid index");

	lists[index]->removeLast();

	if (lists[index]->isEmpty()) //Checks if the List becomes empty after removal of a Student
		removeList(index);
}

void KongaArray::removeFirst(const int index) //Removes the first Student form a given List
{
	if (index >= size || index < 0) //Checks if the given index is valid
		throw std::out_of_range("Invalid index");

	lists[index]->removeFirst();

	if (lists[index]->isEmpty())//Checks if the List becomes empty after removal of a Student
		removeList(index);
}

void KongaArray::removeElem(const char *name, const int index) //Searches a given List for a Student and then deletes it from said List
{
	if (index >= size || index < 0) //Checks if the given index is valid
		throw std::out_of_range("Invalid index");

	//The removeElem func should give an already configured List and only needs to be added to the rest
	KongaList* temp=lists[index]->removeElem(name);

	//If the wanted Student is First or Last no new List is needed, only if the Student is between these two a new List is created
	if (temp!=nullptr)
		newList(temp);

	//If it happens that the wanted Student is the only one remaining, the entire List is deleted
	if (lists[index]->isEmpty())
		removeList(index);
}

void KongaArray::merge(const int &index1, const int &index2) //Combines 2 Lists into 1
{
	if (index1 >= size || index2 >= size || index1 < 0 || index2 < 0) //Checks if the given indexes are valid
		throw std::invalid_argument("One or two indexes are invalid");

	lists[index1]->merge(lists[index2]);
	removeList(index2); //After the 2 Lists are combined, the second one is deleted, after its head and tail pointers are asigned nullptr 
}

void KongaArray::print() const //Prints the contents of all of the Lists
{
	if (size == 0)
		std::cout << "There is nothing to print" << std::endl;
	else
		for (int count = 0; count < size; ++count)
		{
			printf("Line%d :", count);
			lists[count]->print();
		}
}

bool KongaArray::isEmpty() const
{
	if (size == 0)
		return true;
	return false;
}

void KongaArray::removeList(const int index) 
{
	if (index >= size || index < 0) //Checks if the given index is valid
		throw std::invalid_argument("Invalid index");

	for (int count = index; count < size-1; ++count)
		std::swap(lists[count], lists[count + 1]);
	delete lists[--size];
}

void KongaArray::resize() //Resizes the array so that more Elements could be inserted
{
	KongaList** temp = new KongaList*[max * 2];

	for (int count = 0; count < size; ++count)
		temp[count] = lists[count];

	delete[] lists;
	lists = temp;
	max *= 2;
}
