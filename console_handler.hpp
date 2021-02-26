#ifndef _CONSOLE_HPP
#define _CONSOLE_HPP

#include <string>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>

#include "termcolor.hpp"

#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include "kbhit.hpp"
#endif

extern std::string HELP_OPTIONS[];
extern std::string TOTURIAL_OPTIONS[];

void _error(std::string msg);
void slow(std::string text, float speed);
void dialog(std::string name , std::string text, std::string color, float speed);
void toturial_if_needed(std::string option);
void help_if_needed(std::string option);

#endif