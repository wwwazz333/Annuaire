#ifndef _COLOR_H_
#define _COLOR_H_

#include <stdio.h>
#include <stdarg.h>


/* 
Ce fichier permet de gérer les différent affichage entre Linux et Windows
*/

#ifdef __unix__

#elif defined(_WIN32) || defined(WIN32)
//Pour Windows

#include <conio.h>
#include <windows.h>
#define OS_Windows
#define E L"\u00E9"

#endif
#ifndef OS_Windows
//Pour Linux
#define RGBoutput(r, g, b) printf("\033[38;2;%d;%d;%dm", r, g, b);
#define bRGBoutput(r, g, b) printf("\033[48;2;%d;%d;%dm", r, g, b);
#define RESEToutput() printf("\x1b[0m");
#define E "é"

#endif
//Pour les 2

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


/**
 * @pre aucune
 * @post les couleurs qui seront afficher quand on écrira seraon blanche pour le texte et noir pour le fond (normalement les couleur de base)
 */
void setDefaultColor();
/**
 * @pre aucune
 * @post met la couleur du texte à color
 */
void setColor(Color color);
/**
 * @pre aucune
 * @post met la couleur du fond de texte (background) à color
 */
void setBackgroundColor(Color color);

/**
 * @pre str ne contien pas de "\n" sauf si background_color==DEFAULT_BACKGROUND_COLOR
 * @post met la couleur du fond de texte (background) à background_color et la couleur du texte à color puis affiche str
 */
void print(Color color, Color background_color, const char* str, ...);


#endif