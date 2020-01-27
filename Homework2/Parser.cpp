#include "Parser.h"
#include "System.h"


#include <iostream>
#include <fstream>
#include <string>


void start(char** argv)
{
	if (argv[1] == nullptr)
	{
		std::cout << "No file path entered\n";
		return;
	}

	bool exit = false;

	std::ifstream file;

	file.open(argv[1]);
	if (!file.is_open())
	{
		std::cout << "Wrong filename given. Enter again\n";
		return;
	}

	System S1;
	S1.loadFromFile(file);

	file.close();

	while (!exit)
	{
		try
		{
			std::cout << "Enter command: \n";

			UserCommands command = validateCommand(enterCommand());
			
			if (command == UserCommands::invalid)
			{
				std::cin.ignore(MAX, '\n');
				throw std::invalid_argument("Invalid input");
			}

			//Commands like exit and print don't require extra input

			if (command == UserCommands::exitProgram)
				exit = true;
			else if (command == UserCommands::print)
			{
				if (!checkEndLine())
				{
					std::cin.ignore(MAX, '\n');
					throw std::invalid_argument("Invalid input");
				}
				S1.print();
			}
			else
			{
				std::string firstName;
				std::string secondName;
				std::string thirdName;
				Grab whichOne;

				EnterRest(command, firstName, secondName, thirdName, whichOne);

				if (command == UserCommands::release)
				{
					if (firstName.length() > MAX_NAME_LENGTH)
						throw std::invalid_argument("Name is too long");
					S1.release(firstName, whichOne);
				}
				else if (command == UserCommands::grab)
				{
					if (firstName.length() > MAX_NAME_LENGTH)
						throw std::invalid_argument("Name is too long");
					S1.grab(firstName, whichOne);
				}
				else if (command == UserCommands::info)
				{
					if (firstName.length() > MAX_NAME_LENGTH)
						throw std::invalid_argument("Name is too long");
					S1.info(firstName);
				}
				else if (command == UserCommands::addPerson)
				{
					if (firstName.length() > MAX_NAME_LENGTH || secondName.length()>MAX_NAME_LENGTH || thirdName.length()>MAX_NAME_LENGTH)
						throw std::invalid_argument("Name is too long");
					S1.add(firstName, secondName, thirdName);
				}
				else if (command == UserCommands::removePerson)
				{
					if (firstName.length() > MAX_NAME_LENGTH)
						throw std::invalid_argument("Name is too long");
					S1.remove(firstName);
				}
				else if (command == UserCommands::swapPerson)
				{
					if (firstName.length() > MAX_NAME_LENGTH)
						throw std::invalid_argument("Name is too long");
					S1.swap(firstName, secondName);
				}
			}
		}
		catch (const std::invalid_argument& ia)
		{
			std::cerr << ia.what() << std::endl;
		}
		catch (const std::bad_alloc& ba)
		{
			std::cerr << "Memmory allocation problems"<<std::endl;
			exit = true;
		}
	}
}

std::string enterCommand()
{
	std::string temp;
	
	if (!checkEndLine())
		std::cin >> temp;
	else
		throw std::invalid_argument("Invalid input");

	return temp;
}

UserCommands validateCommand(const std::string& command)
{	//Checks if the entered command is valid

	if (command== "release")
		return UserCommands::release;

	if (command == "grab")
		return UserCommands::grab;

	if (command=="info")
		return UserCommands::info;

	if (command=="add")
		return UserCommands::addPerson;

	if (command == "remove")
		return UserCommands::removePerson;

	if (command == "swap")
		return UserCommands::swapPerson;

	if (command=="print")
		return UserCommands::print;

	if (command == "exit")
		return UserCommands::exitProgram;

	return UserCommands::invalid;
}

void EnterRest(const UserCommands cmd, std::string& firstName,std::string& secondName,std::string& thirdName,Grab& whichOne)
{
	//checkForChar() is used because a persons name starts with a " and ends with a "
	//If a starting " is not found then a exception is thrown

	//At the end a check is made if there are any remaining input not needed for the function

	if (cmd == UserCommands::release || cmd==UserCommands::grab)
	{
		if (!checkForChar('\"'))
			throw std::invalid_argument("Invalid input");

		std::getline(std::cin, firstName,'\"');
	
		if (checkEndLine())
			throw std::invalid_argument("Invalid input");

		std::string toGrab;
		std::cin >> toGrab;

		if (toGrab == "both")
			whichOne = Grab::both;
		else if (toGrab == "left")
			whichOne = Grab::left;
		else if (toGrab == "right")
			whichOne = Grab::right;
		else
		{
			std::cin.ignore(MAX,'\n');
			throw std::invalid_argument("Invalid input");
		}

		if (!checkEndLine)
		{
			std::cin.ignore(MAX, '\n');
			throw std::invalid_argument("Input too long");
		}

		std::cin.ignore(MAX, '\n');
	}

	if (cmd == UserCommands::info || cmd==UserCommands::removePerson)
	{
		if (!checkForChar('\"'))
			throw std::invalid_argument("Invalid input");

		std::getline(std::cin, firstName, '\"');

		if (!checkEndLine())
		{
			std::cin.ignore(MAX, '\n');
			throw std::invalid_argument("Invalid input");
		}

	}

	if (cmd == UserCommands::addPerson)
	{
		if (!checkForChar('\"'))
			throw std::invalid_argument("Invalid input");
		std::getline(std::cin, firstName,'\"');

		if (!checkForChar('\"'))
			throw std::invalid_argument("Invalid input");
		std::getline(std::cin, secondName, '\"');

		if (!checkForChar('\"'))
			throw std::invalid_argument("Invalid input");
		std::getline(std::cin, thirdName, '\"');

		if (!checkEndLine())
		{
			std::cin.ignore(MAX, '\n');
			throw std::invalid_argument("Invalid input");
		}
	}

	if (cmd == UserCommands::swapPerson)
	{
		if (!checkForChar('\"'))
			throw std::invalid_argument("Invalid input");
		std::getline(std::cin, firstName,'\"');

		if (!checkForChar('\"'))
			throw std::invalid_argument("Invalid input");
		std::getline(std::cin, secondName,'\"');

		if (!checkEndLine())
		{
			std::cin.ignore(MAX, '\n');
			throw std::invalid_argument("Invalid input");
		}
//		std::cin.ignore(MAX, '\n');
	}

	if (std::cin.fail())
	{
		std::cin.clear();
		throw std::invalid_argument("Wrong Input");
	}
}

bool checkEndLine()
{	
	char ch=0;
	while (true)
	{
		if (std::cin.peek() == '\n')
		{
			std::cin.get(ch);
			return true;
		}
		else if (std::cin.peek() != ' ' && std::cin.peek() !='\t')
			return false;
		std::cin.get(ch);
	}
}

bool checkForChar(const char delim)
{
	char ch = 0;
	while (true)
	{
		std::cin.get(ch);
		if (ch == delim)
			return true;
		if (ch == '\n' || ch!= ' ')
			return false;
	}
	return false;
}


