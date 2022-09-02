#ifndef _KBHIT_HPP
#define _KBHIT_HPP

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int kbhit();
char getch(void);
void resetTermios(void);
void initTermios(int echo);

#endif