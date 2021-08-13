#ifndef _COLOR_HPP
#define _COLOR_HPP

#include <string>
#include <iostream>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define ALTERNATEBLACK   "\033[90m"      /* Black */
#define ALTERNATERED     "\033[91m"      /* Red */
#define ALTERNATEGREEN   "\033[92m"      /* Green */
#define ALTERNATEYELLOW  "\033[93m"      /* Yellow */
#define ALTERNATEBLUE    "\033[94m"      /* Blue */
#define ALTERNATEMAGENTA "\033[95m"      /* Magenta */
#define ALTERNATECYAN    "\033[96m"      /* Cyan */
#define ALTERNATEWHITE   "\033[97m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define NOCOLOR     "\033[29m"             /* No color */

void cprint(std::string string_to_print, std::string color);
std::string colored(std::string string_to_color, std::string color);

#endif