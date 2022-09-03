#include "kbhit.hpp"

#include <termios.h>
#include <stdio.h>

static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    current = old; /* make new settings same as old settings */
    current.c_lflag &= ~ICANON; /* disable buffered i/o */
    if (echo) {
        current.c_lflag |= ECHO; /* set echo mode */
    } else {
        current.c_lflag &= ~ECHO; /* set no echo mode */ 
    }
    tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

void restoreTermios() {
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    current = old; /* make new settings same as old settings */
    current.c_lflag |= ICANON; /* enable buffered i/o */
    current.c_lflag |= ECHO; /* set echo mode */
    tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void)
{
    return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
    return getch_(1);
}

int kbhit(){
    int ch;
    int oldf;
    
    // fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    initTermios(0);

    ch = getchar();

    // fcntl(STDIN_FILENO, F_SETFL, 0);
    resetTermios();

    if(ch != EOF){
        return 1;
    }

    return 0;
}