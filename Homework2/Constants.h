#ifndef CONSTANTS_H
#define CONSTANTS_H

const int MAX_NAME_LENGTH = 30;
const int MAX = 256;

const enum UserCommands
{
	release,
	grab,
	info,
	addPerson,
	removePerson,
	swapPerson,
	print,
	exitProgram,
	invalid
};

const enum Grab
{
	left,
	right,
	both
};

const char rightHold[] = " ---> ";
const char leftHold[] = " <--- ";
const char bothHold[] = " <--> ";
const char nobodyHold[] = " ---- ";

#endif // !CONSTANTS_H
