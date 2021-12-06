#ifndef _COLOR_H_
#define _COLOR_H_

#include <stdio.h>

#ifdef __unix__

#elif defined(_WIN32) || defined(WIN32)

#include <conio.h>
#include <windows.h>
#define OS_Windows
#define show_e "\x82"

#endif

typedef enum {
    RED,
    BLUE,
    GREEN,
    BLACK,
    WHITE,
    GREY,
    YELLOW,
    PINK,
    PURPLE,
    ORANGE,
    AQUA,
    DEFAULT_COLOR,
    DEFAULT_BACKGROUND_COLOR
} Color;

#ifndef OS_Windows

#define RGBoutput(r, g, b) printf("\033[38;2;%d;%d;%dm", r, g, b);
#define bRGBoutput(r, g, b) printf("\033[48;2;%d;%d;%dm", r, g, b);
#define RESEToutput() printf("\x1b[0m");

#define show_e "\u00e9"

#endif

void setDefaultColor();
void setColor(Color color);
void setBackgroundColor(Color color);

void print(const char* str, Color color, Color background_color);


#endif