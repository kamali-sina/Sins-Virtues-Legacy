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
#include <vector>
#include <sstream>
#include <pthread.h>
#include <sys/stat.h>

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

#define STARTOFCOLORCODE 27
#define NEWGAME "-n"
#define LOADGAME "-l"
#define DEFAULTSAVEPATH "./"
#define SAVEFOLDRNAME "VnSave"
#define SAVEFILENAME  "game.vnsave"
#define PLAYERSAVEFILENAME  "player.vnsave"
#define MAPSAVEFILENAME  "map.vnsave"

float _random();
std::string lower(std::string input);
std::vector<std::string> split_string(std::string input, char delim);
void _error(std::string msg);
void slow(std::string text, float speed);
void dialog(std::string name , std::string text, std::string color, float speed);
void toturialIfNeeded(std::string option);
void helpIfNeeded(std::string option);
std::string handleNewGame(std::string path);
std::string handleLoadGame(std::string path);
void notification(std::string msg);

#endif