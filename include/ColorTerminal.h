#ifndef _COLOR_H_
#define _COLOR_H_

#include <stdio.h>

#ifdef __unix__         

#elif defined(_WIN32) || defined(WIN32) 

    #include <windows.h>
    #include <conio.h>
    #define OS_Windows

#endif

typedef enum {
    RED,
    BLUE,
    GREEN,
    BLACK,
    WHITE,
    GREY,
    YELLOW,
    DEFAULT_COLOR,
    DEFAULT_BACKGROUND_COLOR
} Color;

#ifndef OS_Windows

#define RGBoutput(r, g, b) printf("\033[38;2;%d;%d;%dm", r, g, b);
#define bRGBoutput(r, g, b) printf("\033[48;2;%d;%d;%dm", r, g, b);
#define RESEToutput() printf("\x1b[0m");

#endif

void setDefaultColor();
void setColor(Color color);
void setBackgroundColor(Color color);


#endif