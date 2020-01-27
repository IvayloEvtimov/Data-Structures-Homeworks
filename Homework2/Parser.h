#ifndef PARSER_H
#define PARSER_H

#include <string>

#include "Constants.h"

void start(char**); 
std::string enterCommand(); 
UserCommands validateCommand(const std::string&); //Validates a given command 
void EnterRest(const UserCommands, std::string& ,std::string&,std::string&, Grab&); //Enter the rest of the required input
bool checkEndLine(); //Checks if there is endl after an input
bool checkForChar(const char);

#endif // !PARSER_H
