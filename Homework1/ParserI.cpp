#include "Parser.h"
#include "KongaArray.h"
#include <iostream>

void start()
{
	char command[MAX];
	bool exit = false;

	KongaArray System;

	while (!exit)
	{
		printf("Enter command: \n");
		try
		{	
			char name[MAX],
				uni[MAX];

			int index1 = 0,
				index2 = 0;

			strcpy_s(command, MAX, enterCommand());
			UserCommands choice = validateCommand(command);

			switch (choice)
			{
			case UserCommands::append:
				EnterRest(choice, index1, index2, name, uni);
				System.append(name, uni, index1);
				break;
			case UserCommands::removeLast:
				EnterRest(choice, index1, index2);
				System.removeLast(index1);
				if (System.isEmpty())
					std::cout << "There are no people left. Only option now is to quit" << std::endl;
				break;
			case UserCommands::removeFirst:
				EnterRest(choice, index1, index2);
				System.removeFirst(index1);
				if (System.isEmpty())
					std::cout << "There are no people left. Only option now is to quit" << std::endl;
				break;
			case UserCommands::removeElem:
				EnterRest(choice, index1, index2, name);
				System.removeElem(name, index1);
				if (System.isEmpty())
					std::cout << "There are no people left. Only option now is to quit" << std::endl;
				break;
			case UserCommands::merge:
				EnterRest(choice, index1, index2);
				System.merge(index1, index2);
				break;
			case UserCommands::print:
				System.print();
				break;
			case UserCommands::quit:
				exit = true;
				break;
			case UserCommands::invalid:
				throw std::invalid_argument("No such command");
				break;
			}
			

		}
		catch (const std::invalid_argument& ia)
		{
			std::cerr << ia.what() << std::endl;
		}
		catch (const std::bad_alloc& ba)
		{
			std::cerr << "Memory allocation failure" << std::endl;
			return;
		}
		catch (const std::logic_error& le)
		{
			std::cerr << le.what() << std::endl;
		}
		catch (const std::out_of_range& oor)
		{
			std::cerr << oor.what() << std::endl;
		}
		std::cin.ignore(MAX, '\n');
	}
}

char * enterCommand()
{
	char temp[MAX];
	
	if (!checkEndLine())
		std::cin >> temp;

	return temp;
}

UserCommands validateCommand(const char *command)
{	//Checks if the entered command is valid

	if (strcmp(command, "append") == 0)
		return UserCommands::append;

	if (strcmp(command, "merge") == 0)
		return UserCommands::merge;

	if (strcmp(command, "print") == 0)
		return UserCommands::print;

	if (strcmp(command, "quit") == 0)
		return UserCommands::quit;

	if (strcmp(command, "remove") == 0)
		return UserCommands::removeElem;

	if (strcmp(command, "removeFirst") == 0)
		return UserCommands::removeFirst;

	if (strcmp(command, "removeLast") == 0)
		return UserCommands::removeLast;

	return UserCommands::invalid;
}

void EnterRest(const UserCommands cmd, int &index1, int &index2, char *name, char* uni)
{
	//For the command append name,university and index are required  
	if (cmd == UserCommands::append)
	{
		strcpy_s(name, MAX, enterCommand());
		strcpy_s(uni, MAX, enterCommand());
		if(!checkEndLine())
			std::cin >> index1;
		else
			throw std::invalid_argument("Number input is required");
	}

	//For the command removeElem name and index are required
	if (cmd == UserCommands::removeElem)
	{
		strcpy_s(name, MAX, enterCommand());
		if (!checkEndLine())
			std::cin >> index1;
		else
			throw std::invalid_argument("Number input is required");
	}

	//For the command removeLast index are required
	if (cmd == UserCommands::removeLast)
	{
		if (!checkEndLine())
			std::cin >> index1;
		else
			throw std::invalid_argument("Number input is required");
	}

	//For the command rmeoveFirst index is required
	if (cmd == UserCommands::removeFirst)
	{
		if (!checkEndLine())
			std::cin >> index1;
		else
			throw std::invalid_argument("Number input is required");
	}

	//For the command merge 2 indexes are required
	if (cmd == UserCommands::merge)
	{
		if (!checkEndLine())
			std::cin >> index1;
		else
			throw std::invalid_argument("Number input is required");

		if (std::cin.fail())
		{
			std::cin.clear();
			throw std::invalid_argument("Wrong Input");
		}

		if (!checkEndLine())
			std::cin >> index2;
		else
			throw std::invalid_argument("Number input is required");
	}

	if (std::cin.fail())
	{
		std::cin.clear();
		throw std::invalid_argument("Wrong Input");
	}

	if (!checkEndLine()) //Checks if the rest of the line is empty so that 1 line is equal to 1 command
	{
		std::cin.ignore(MAX, '\n');
		throw std::invalid_argument("Input too long");
	}
}

bool checkEndLine()
{	
	char ch=0;
	while (true)
	{
		if (std::cin.peek() == '\n')
			return true;
		if (std::cin.peek() != ' ')
			return false;
		std::cin.get(ch);
	}
}


