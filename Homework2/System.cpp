#include "System.h"

System::System(const int size):DanceFloor(),Table(size)
{
}

void System::release(const std::string &name, const Grab &whichOne)
{
	//A person pointer is found by the Hash Table
	Horo::Data* person = Table.find(name);

	//If the person isn't found its because the name given is invalid
	//When there isn't such person a nullptr is passed
	if (person==nullptr)
		throw std::invalid_argument("Invalid name given");

	DanceFloor.release(person, whichOne);
}

void System::grab(const std::string &name, const Grab &whichOne)
{
	//A person pointer is found by the Hash Table
	Horo::Data* person = Table.find(name);

	//If the person isn't found its because the name given is invalid
	//When there isn't such person a nullptr is passed	
	if (person==nullptr)
		throw std::invalid_argument("Invalid name given");

	DanceFloor.grab(person, whichOne);
}

void System::info(const std::string &name)
{
	//A person pointer is found by the Hash Table
	Horo::Data* person = Table.find(name);

	//If the person isn't found its because the name given is invalid
	//When there isn't such person a nullptr is passed
	if(person==nullptr)
		throw std::invalid_argument("Invalid name given");

	DanceFloor.info(person);
}

void System::add(const std::string &name, const std::string &leftName, const std::string &rightName)
{
	Horo::Data* left = Table.find(leftName);
	Horo::Data* right = Table.find(rightName);

	//When searching with key name the Hash Table must pass a nullptr
	//Because such person shouldn't exist
	//If he exists he can't be added because he is already in
	if (Table.find(name)!=nullptr || left==nullptr || right==nullptr)
		throw std::invalid_argument("Invalid name given");

	//The new object is created and its pointer is stored in the Hash Table
	//and it's neighbours are sorted out in the Horo class
	Horo::Data* temp = new Horo::Data(name);
	DanceFloor.add(temp, left, right);
	Table.insert(name,temp);
}

void System::remove(const std::string &name)
{
	Horo::Data* person = Table.find(name);

	if (person == nullptr)
		throw std::invalid_argument("Invalid name given");

	//The person must not hold anyone and be release by all of his neighbours
	//in order to be removed
	if (!DanceFloor.isReleased(person))
	{
		std::cout << "This won't be so easy" << std::endl;
		return;
	}


	//Since all checks have passed the pointer to the object is removed from the Hash Table
	//And the object is deleted
	Table.remove(name);
	DanceFloor.remove(person);
}

void System::swap(const std::string &leftName, const std::string &rightName)
{
	Horo::Data*& left= Table.find(leftName);
	Horo::Data*& right = Table.find(rightName);

	if (left == nullptr || right == nullptr)
		throw std::invalid_argument("Invalid name given");

	//The two persons must be neighbours in order to be swapped
	if (DanceFloor.areNeighbours(left, right))
		throw std::invalid_argument("The persons must be together in order to swap places");

	//And they must not be hold on by anyone
	if(left->right==right && (left->left->grabRight || right->right->grabLeft))
		throw std::invalid_argument("They are still holding on");
	if(left->left==right && (left->right->grabLeft || right->left->grabRight))
		throw std::invalid_argument("They are still holding on");

	//Swaps the names of the pointers to the objects
	//Then the pointers are swapped because now the pointer are pointing to object with different name
	//And the when hashing the name of one of the objects the hashFunc passes an index to the pointer of the other object
	DanceFloor.swap(left, right);
	std::swap(left, right);
}

void System::print() const
{
	DanceFloor.print();
}

void System::loadFromFile(std::ifstream &file)
{
	char str[MAX_NAME_LENGTH];

	while (true)
	{
		file.getline(str, MAX_NAME_LENGTH, '\n');
		if (file.eof())
			break;

		if (Table.find(str) == nullptr)
		{

			Horo::Data* temp = new Horo::Data(str);
			DanceFloor.loadFromFile(temp);
			Table.insert(str,temp);
		}
		else
			std::cout << "Name " << str << " is already in included" << std::endl;
	}
}

