#include "ColorTerminal.h"

#ifdef OS_Windows

void setColor(Color color)
{

    switch (color) {
    case RED:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4| FOREGROUND_INTENSITY);
        break;
    case BLUE:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1| FOREGROUND_INTENSITY);
        break;
    case GREEN:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2| FOREGROUND_INTENSITY);
        break;
    case BLACK:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0| FOREGROUND_INTENSITY);
        break;
    case WHITE:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15| FOREGROUND_INTENSITY);
        break;
    case GREY:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0| FOREGROUND_INTENSITY);
        break;
    case YELLOW:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6 | FOREGROUND_INTENSITY);
        break;
    default:
        break;
    }
}

void setBackgroundColor(Color color)
{
    switch (color) {
    case RED:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | 4);
        break;
    case BLUE:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | 1);
        break;
    case GREEN:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | 1);
        break;
    case BLACK:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | 0);
        break;
    case WHITE:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | 15);
        break;
    case GREY:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | 0);
        break;
    case YELLOW:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | 6);
        break;
    default:
        break;
    }
}
void setDefaultColor(){
    setColor(WHITE);
	setBackgroundColor(BLACK);
}
#else
void setDefaultColor()
{
    RESEToutput();
}

void setColor(Color color)
{
    switch (color) {
    case RED:
        RGBoutput(255, 0, 0);
        break;
    case BLUE:
        RGBoutput(0, 0, 255);
        break;
    case GREEN:
        RGBoutput(0, 255, 0);
        break;
    case BLACK:
        RGBoutput(0, 0, 0);
        break;
    case WHITE:
        RGBoutput(255, 255, 255);
        break;
    case GREY:
        RGBoutput(128, 128, 128);
        break;
    case YELLOW:
        RGBoutput(255, 255, 0);
        break;
    default:
        break;
    }
}

void setBackgroundColor(Color color)
{
    switch (color) {
    case RED:
        bRGBoutput(255, 0, 0);
        break;
    case BLUE:
        bRGBoutput(0, 0, 255);
        break;
    case GREEN:
        bRGBoutput(0, 255, 0);
        break;
    case BLACK:
        bRGBoutput(0, 0, 0);
        break;
    case WHITE:
        bRGBoutput(255, 255, 255);
        break;
    case GREY:
        bRGBoutput(128, 128, 128);
        break;
    case YELLOW:
        bRGBoutput(255, 255, 0);
        break;
    default:
        break;
    }
}

#endif