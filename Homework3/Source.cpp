#include <iostream>
#include <fstream>
#include "System.h"

void start(char** argv)
{
	std::ifstream input(argv[1]);
	if (!input.is_open())
		return;

	System sys;
	sys.load(input);
	sys.findUnreachable(argv[2]);
}

int main(int argc,char** argv)
{
	start(argv);

	return 0;
}