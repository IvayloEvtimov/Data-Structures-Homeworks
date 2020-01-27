#include "DoubleList.h"

#include <iostream>
#include <string>

DoubleList::DoubleList():head(nullptr), tail(nullptr),size(0)
{

}

DoubleList::DoubleList(const DoubleList &other):head(nullptr),tail(nullptr),size(0)
{
	try
	{
		copyFrom(other);
	}
	catch (const std::bad_alloc& ba)
	{
		clear();
		throw;
	}
}

DoubleList & DoubleList::operator=(const DoubleList &other)
{
	if (this != &other)
	{
		try {
			clear();
			copyFrom(other);
		}
		catch (const std::bad_alloc& ba)
		{
			clear();
			throw;
		}
	}
	return *this;
}

DoubleList::~DoubleList()
{
	clear();
}

void DoubleList::append(const std::string& name, const std::string& uni)
{
	if (head == nullptr) //When the List is Empty
	{
		Student* temp = new Student(name, uni);
		head = temp;
		tail = temp;
		++size;
	}
	else //When the List has at least 1 Student in it
	{
		if (!validList(uni)) //Checks if new Student would be compatibe with the List
			throw std::invalid_argument("Incompatible people");

		Student* temp = tail;
		Student* newStudent = nullptr;

		try
		{	//If when creating a New Student an exception is called the allocated memory is deleted and the exception is rethrown
			newStudent = new Student(name, uni);
		}
		catch (const std::invalid_argument& ia)
		{
			delete newStudent;
			throw;
		}

		tail = newStudent;  //The new Student becomes the new tail
		temp->next = newStudent;  //The old tail now point to the new tail
		newStudent->prev = temp;
		++size;
	}
}

void DoubleList::removeLast()
{
	if (head == tail) //When the head and tail are the same there is only one Student
	{
		delete tail; //Since the are no more Students in the List the head and tail pointer are nullptr
		tail = nullptr;
		head = nullptr;
		size = 0;
	}
	else
	{
		Student* temp = tail->prev; //Save the pointer to the Student behind the tail
		delete tail; //Removes the current tail 
		tail = temp; //The Student behind becomes the new Tail
		tail->next = nullptr;
		--size;
	}
}

void DoubleList::removeFirst()
{
	if (head == tail) //When the head and tail are the same there is only one Student
	{
		delete head;  //Since the are no more Students in the List the head and tail pointer are nullptr
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	else
	{
		Student* next = head->next; //Save the pointer to the Student after the head
		delete head; //Removes the current h
		head = next; //The Student behind becomes the new Tail
		--size;
	}	
}

DoubleList* DoubleList::removeElem(const char* name)
{	
	//If the desired Student is the head or tail, removes it from the list
	//and returns Empty list because no new List is required
	if (head->name == name)
	{
		removeFirst();
		return nullptr;
	}

	Student* current = head->next;

	//Cycle through the List until a valid Student is found
	//If current reaches tail->prev then the wanted Student mus be either the tail or it doesn't exist
	//Complexity O(n)

	for(int count=1;count<size;++count)
	{
		//++count;
		if (current->name==name) 
		{
			Student* temp = current->next;
			
			//For the remaining Students a new List is created
			DoubleList* newList = new DoubleList;
			newList->head = temp;
			newList->head->prev = nullptr;
			newList->tail = tail;
			newList->tail->next = nullptr;
			newList->size = size - count-1;
			//Since the head and tail are known and newList is empty, there is no need to create new Students	

			size = count;
			tail = current->prev; //After removing the desired Student, the one before him becomes the tail of the current List
			tail->next = nullptr;
			delete current;

			return newList; //Return the new List so that it can be added to the array
		}
		current = current->next;
	}

	if (tail->name == name)
	{
		removeLast();
		return nullptr;
	}

	throw std::invalid_argument("Invalid name given"); //If it goes here, it means that there isn't such Student
}

void DoubleList::merge(DoubleList* other) //Combines 2 lists into 1 
{
	if (!validList(other->head->uni))
		throw std::invalid_argument("Can not merge. Incompatible people");

	//Since all the Students are created there is no need to allocate any more memory
	//Only the tail pointer needs to be realigned
	tail->next = other->head;
	tail->next->prev = tail;
	tail = other->tail;
	other->head = nullptr;
	other->tail = nullptr;
}

void DoubleList::print() const //Print all the Student in the List
{
	Student* temp = head;
	while (temp != nullptr)
	{
		std::cout << ' ';
		temp->print();
		if(temp->next!=nullptr)
			std::cout << " -";

		temp = temp->next;
	}
	std::cout << std::endl;
}

bool DoubleList::isEmpty() const //Checks if the List is empty
{
	if (size == 0)
		return true;
	return false;
}

bool DoubleList::validList(const std::string uni) const
{
	//Validates if the List would be valid if a Student from a given uni is added
	if (uni== "tu") 
		if (tail->uni== "fmi")
			return false;

	if (uni=="fmi") 
		if (tail->uni=="unss")
			return false;

	if (uni == "unss") 
		if (tail->uni== "tu")
			return false;

	return true;
}

void DoubleList::copyFrom(const DoubleList &other) //Copies the contents of a List by creating new elements
//Compexity O(n)
{
	Student* temp = other.head;
	while (temp!=other.tail->next)
	{
		append(temp->name, temp->uni);
		temp = temp->next;
	}
}

void DoubleList::clear() //Deletes elements until there are none
{
	while (!isEmpty())
		removeLast();
}

DoubleList::Student::Student(const std::string& name, const std::string& uni):name(name),uni(uni),next(nullptr),prev(nullptr)
{
	if (uni != "tu" && uni != "fmi" && uni != "unss")
		throw std::invalid_argument("Wrong university");
}

void DoubleList::Student::print() const
{
	std::cout << '(' << name << ", " << uni << ')';
}

