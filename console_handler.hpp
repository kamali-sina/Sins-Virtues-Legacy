#ifndef _CONSOLE_HPP
#define _CONSOLE_HPP

#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "termcolor.hpp"

extern std::string HELP_OPTIONS[];
extern std::string TOTURIAL_OPTIONS[];

//TODO: complete functions below

//Incomplete:
void _error(std::string msg);
void slow(std::string text, float speed=13);
void dialog(std::string name , std::string text, std::string color, float speed=13);
//Complete:
void toturial_if_needed(std::string option);
void help_if_needed(std::string option);

#endif