#include "ColorTerminal.h"

#ifdef OS_Windows

void setColor(Color color)
{

    switch (color) {
    case RED:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        break;
    case BLUE:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
        break;
    case GREEN:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        break;
    case BLACK:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        break;
    case WHITE:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        break;
    case GREY:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        break;
    case YELLOW:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        break;
    default:
        break;
    }
}

void setBackgroundColor(Color color)
{
    switch (color) {
    case RED:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 154);
        break;
    case BLUE:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 151);
        break;
    case GREEN:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 152);
        break;
    case BLACK:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 150);
        break;
    case WHITE:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1515);
        break;
    case GREY:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 158);
        break;
    case YELLOW:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 156);
        break;
    default:
        break;
    }
}
void setDefaultColor()
{
    setColor(WHITE);
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