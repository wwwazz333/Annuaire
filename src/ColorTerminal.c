#include "ColorTerminal.h"

#ifdef OS_Windows
int currTextColor = 15;
int currBackgroundColor = 0;

void setColor(Color color)
{

    switch (color) {
    case RED:
        currTextColor = 4;
        break;
    case BLUE:
        currTextColor = 9;
        break;
    case GREEN:
        currTextColor = 2;
        break;
    case BLACK:
        currTextColor = 0;
        break;
    case WHITE:
        currTextColor = 15;
        break;
    case GREY:
        currTextColor = 8;
        break;
    case YELLOW:
        currTextColor = 14;
        break;
    case PINK:
        currTextColor = 13;
        break;
    case PURPLE:
        currTextColor = 5;
        break;
    case ORANGE:
        currTextColor = 6;
        break;
    case AQUA:
        currTextColor = 3;
        break;
    default:
        break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), currTextColor + 16 * currBackgroundColor);
}

void setBackgroundColor(Color color)
{
    switch (color) {
    case RED:
        currBackgroundColor = 4;
        break;
    case BLUE:
        currBackgroundColor = 1;
        break;
    case GREEN:
        currBackgroundColor = 2;
        break;
    case BLACK:
        currBackgroundColor = 0;
        break;
    case WHITE:
        currBackgroundColor = 15;
        break;
    case GREY:
        currBackgroundColor = 8;
        break;
    case YELLOW:
        currBackgroundColor = 14;
        break;
    case PINK:
        currBackgroundColor = 13;
        break;
    case PURPLE:
        currBackgroundColor = 5;
        break;
    case ORANGE:
        currBackgroundColor = 6;
        break;
    case AQUA:
        currBackgroundColor = 6;
        break;
    default:
        break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), currTextColor + 16 * currBackgroundColor);
}
void setDefaultColor()
{
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
        RGBoutput(197, 15, 31);
        break;
    case BLUE:
        RGBoutput(59, 120, 255);
        break;
    case GREEN:
        RGBoutput(19, 161, 14);
        break;
    case BLACK:
        RGBoutput(12, 12, 12);
        break;
    case WHITE:
        RGBoutput(204, 204, 204);
        break;
    case GREY:
        RGBoutput(118, 118, 118);
        break;
    case YELLOW:
        RGBoutput(193, 156, 0);
        break;
    case PINK:
        RGBoutput(180, 0, 158);
        break;
    case PURPLE:
        RGBoutput(136, 23, 152);
        break;
    case ORANGE:
        RGBoutput(247, 179, 91);
        break;
    case AQUA:
        RGBoutput(58, 150, 221);
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