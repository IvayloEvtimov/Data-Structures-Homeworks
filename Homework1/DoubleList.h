#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <string>

class DoubleList
{
public:
	DoubleList();
	DoubleList(const DoubleList&);
	DoubleList& operator=(const DoubleList&);
	~DoubleList();

	void append(const std::string&,const std::string&); //Adds new Student at the end of the List O(1)
	void removeLast(); //Removes the last Student in the List O(1)
	void removeFirst(); //Removes the first Student in the List O(1)
	DoubleList* removeElem(const char*);  //Removes a Selected Student and Creates a new List with the remaining Students O(n)
	void merge(DoubleList*); //Combines two Lists into one O(1)

	void print() const;  //Prints all the contents of the List
	bool isEmpty() const; //Checks if the List is Empty
private:
	struct Student 
	{
	public:
		Student(const std::string&, const std::string&);

		void print() const;
	public:
		std::string name;
		std::string uni;

		Student* next;
		Student* prev;
	};
private:
	bool validList(const std::string) const; //Checks if adding a new Student will break the List compatability
	void copyFrom(const DoubleList&);  //Copies the content another List O(n)
	void clear(); //Removes all the Students from the list
private:
	Student* head; //The first Student
	Student* tail; //The last Student

	int size; //Number of all Students in the List
};

#endif // !KONGOLIST_H
