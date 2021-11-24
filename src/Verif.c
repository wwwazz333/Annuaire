#include "Verif.h"

int is_digit(char c)
{
    return (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9');
}

void input(char* str, int sizeof_str)
{
    int i = 0;
    while ((str[i] = getchar()) != '\n' && i < sizeof_str - 1) { // on attribut str[i] un caractère au clavier tant que se
        // n'est pas "Entrer" et qu'on a pas atteint la fin de la
        // chaine de caractère (-1 car on met '\0' a la fin)
        i++;
    };
    str[i] = '\0'; // pour metre '\0' a la fin de la chaine de caractère
}

char* ask_fichier(char* extension)
{
    char* nom;
    nom = calloc(50, sizeof(char));

    while (nom[0] == '\0' || nom[0] == '\n') {
        setColor(ORANGE);
        printf("Nom fichier: ");
        setColor(AQUA);
        input(nom, 50);
        setDefaultColor();
    }
    if (extension[0] != '\0') {
        strcat(nom, ".");
        strcat(nom, extension);
    }
    return nom;
}

int file_exist(const char* file_path)
{
    if (access(file_path, F_OK) == 0) {
        return 1;
    } else {
        return 0;
    }
}

char* ask_fichier_existant(char* extension)
{
    char* name;
    do {
        name = ask_fichier(extension);
    } while (!file_exist(name));
    return name;
}

void flush()
{
    char c;
    do {
        scanf("%c", &c);
    } while (c != '\n' && c != EOF);
    // char c;
    // while ((c = getc(stdin)) != '\n' && c != EOF) { };
}


int is_del(user u)
{
    if (
        u.nom[0] == '\0' && u.prenom[0] == '\0' && u.ville[0] == '\0' && u.code_postal[0] == '\0' && u.no_telephone[0] == '\0' && u.email[0] == '\0' && u.metier[0] == '\0') {
        return 1;
    }
    return 0;
}