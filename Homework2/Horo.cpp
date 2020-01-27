#include "Horo.h"

#include <iostream>

Horo::Horo():top(nullptr),size(0)
{
}

Horo::~Horo()
{
	while (size != 0)
	{
		Data* left = top->left;
		Data* right = top->right;
		delete top;
		top = right;
		top->left = left;
		left->right = top;
		--size;
	}
}

void Horo::add(Data* person , Data * Left, Data * Right)
{
	if (Left->right != Right || Right->left!=Left)
		throw std::invalid_argument("Left and Right are not next to each other");

	Left->right = person;
	person->left = Left;
	person->grabLeft = true;
	Right->left = person;
	person->right = Right;
	person->grabRight = true;
	++size;
}

void Horo::remove(Data * person)
{
		Data* left = person->left;
		Data* right = person->right;

		left->right = right;
		right->left = left;

		delete person;
		--size;
		std::cout << "Free at last!" << std::endl;

	if (size == 2)
	{
		std::cout << "... and the music stops!" << std::endl;
		exit(0);
	}
}

void Horo::grab(Data * person, const Grab &whichOne)
{
	if (whichOne == Grab::left)
	{
		if (person->grabLeft)
			throw std::invalid_argument("They are already holding each other");
		person->grabLeft = true;
	}
	else if (whichOne == Grab::right)
	{
		if (person->grabRight)
			throw std::invalid_argument("They are already holding each other");
		person->grabRight = true;
	}
	else if (whichOne == Grab::both)
	{
		if (person->grabLeft && person->grabRight)
			throw std::invalid_argument("They are already holding each other");
		person->grabLeft = true;
		person->grabRight = true;
	}
}

void Horo::release(Data *person, const Grab &whichOne)
{
	if (whichOne == Grab::left)
	{
		if (!person->grabLeft)
			throw std::invalid_argument("They are already released");
		person->grabLeft = false;
	}
	else if (whichOne == Grab::right)
	{
		if (!person->grabRight)
			throw std::invalid_argument("They are already released");
		person->grabRight = false;
	}
	else if (whichOne == Grab::both)
	{
		if (!person->grabLeft && !person->grabRight)
			throw std::invalid_argument("They are already released");
		person->grabLeft = false;
		person->grabRight = false;
	}
}

void Horo::swap(Data *&PartnerOne, Data *&PartnerTwo)
{
	std::swap(PartnerOne->name, PartnerTwo->name);
}

void Horo::info(Data*& person) const
{
	if (person == nullptr)
		throw std::invalid_argument("Invlaid Person");

	std::cout<<person->left->name;

	if (person->left->grabRight && person->grabLeft)
		std::cout << bothHold;
	else if (!person->left->grabRight && person->grabLeft)
		std::cout << leftHold;
	else if (person->left->grabRight && !person->grabLeft)
		std::cout << rightHold;
	else if (!person->left->grabRight && !person->grabLeft)
		std::cout << nobodyHold;

	std::cout<<person->name;

	if (person->grabRight && person->right->grabLeft)
		std::cout << bothHold;
	else if (!person->grabRight && person->right->grabLeft)
		std::cout << leftHold;
	else if (person->grabRight && !person->right->grabLeft)
		std::cout << rightHold;
	else if (!person->grabRight && !person->right->grabLeft)
		std::cout << nobodyHold;

	std::cout<<person->right->name;

	std::cout << std::endl;
}

void Horo::print() const
{
	Data* temp = top;
	do
	{
		std::cout<<temp->name<<std::endl;
		temp = temp->right;
	} while (temp != top);
}

bool Horo::areNeighbours (const Data* PersonOne, const Data* PersonTwo)
{
	if (PersonOne->left != PersonTwo || PersonTwo->right != PersonOne)
		return false;

	if (PersonOne->right != PersonTwo || PersonTwo->left != PersonOne)
		return false;

	return true;
}

bool Horo::isReleased(const Data *person) const
{
	if(person==nullptr)
		return false;

	if (!person->left->grabRight && !person->right->grabLeft && !person->grabLeft && !person->grabRight)
		return true;
	else
		return false;
}

void Horo::loadFromFile(Horo::Data*& person)
{
	if (top == nullptr)
	{
		top = person;
		top->left = top;
		top->right = top;
		top->grabLeft = true;
		top->grabRight = true;
	}
	else
	{
		Data* last = top->left;
		top->left = person;
		last->right = top->left;
		top->left->left = last;
		top->left->grabLeft = true;
		top->left->right = top;
		top->left->grabRight = true;
	}
	++size;

}
