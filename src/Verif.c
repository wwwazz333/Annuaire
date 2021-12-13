#include "Verif.h"

void input(char* str, int sizeof_str)
{
    int i = 0;
    while ((str[i] = getchar()) != '\n' && i < sizeof_str - 1) { // on attribut str[i] un caractère au clavier tant que se
        // n'est pas "Entrer" et qu'on a pas atteint la fin de la
        // chaine de caractère (-1 car on met '\0' a la fin)
        if (str[i] == ',') {
            i--;
        }
        i++;
    }
    if (str[i] != '\n') {
        while (getchar() != '\n') { // on lit les caractère pour ne pas les mettre dans le prochain champ input
        }
    }
    str[i] = '\0';
    // pour metre '\0' a la fin de la chaine de caractère
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
    if (file_path == NULL) {
        return -1;
    }
    if (access(file_path, F_OK) == 0) {
        return 1;
    } else {
        print("Fichier inexistant", RED, DEFAULT_BACKGROUND_COLOR);
        printf(" - ");
        print("Pensez peut etre a ne pas preciser l'extension de fichier\n", GREY, DEFAULT_BACKGROUND_COLOR);
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
    return u.nom[0] == '\0' && u.prenom[0] == '\0' && u.ville[0] == '\0' && u.code_postal[0] == '\0' && u.no_telephone[0] == '\0' && u.email[0] == '\0' && u.metier[0] == '\0';
}

void strtolower(char* dst, char* src, int size)
{
    int i = 0;
    for (; i < size - 1 && src[i] != '\0'; i++) {
        dst[i] = tolower(src[i]);
    }
    dst[i] = '\0';
}

int string_cmp(const char* p1, const char* p2) // code source récuperer ici : https://code.woboq.org/userspace/glibc/string/strcmp.c.html et modifier pour nos besoin
{
    const unsigned char* s1 = (const unsigned char*)p1;
    const unsigned char* s2 = (const unsigned char*)p2;
    unsigned char c1, c2;
    c1 = tolower((unsigned char)*s1++);
    c2 = tolower((unsigned char)*s2++);
    if (c1 == '\0') {
        return 1;
    } else if (c2 == '\0') {
        return -1;
    }
    while (c1 == c2) {
        c1 = tolower((unsigned char)*s1++);
        c2 = tolower((unsigned char)*s2++);
        if (c1 == '\0')
            return c1 - c2;
    }
    return c1 - c2;
}
// int string_cmp(const char* s1, const char* s2)
// {
//     if (s1[0] == '\0' || s2[0] == '\0') {
//         return -1 * strcmp(s1, s2);
//     } else {
//         return strcmp(s1, s2);
//     }
// }

int is_in_tab(int index, int size_max)
{
    return (index >= 0 && index < size_max);
}

int stringstring(const char* haystack, const char* needle) //inspirer de strstr trouver ici : https://code.woboq.org/userspace/glibc/string/strstr.c.html
{
    if (needle[0] == '\0')
        return haystack != NULL;
    haystack = stringchr(haystack, *needle);
    if (needle[1] == '\0') {
        return haystack != NULL;
    }
    if (haystack == NULL) {
        return 0;
    }
    while (tolower(*haystack) == tolower(*needle) && *haystack != '\0' && *needle != '\0') {
        haystack++;
        needle++;
    }
    if (*needle == '\0') {
        return 1;
    } else if (*haystack == '\0') {
        return 0;
    } else {
        return stringstring(haystack, needle);
    }
}
char* stringchr(register const char* s, int c) // https://code.woboq.org/gcc/libiberty/strchr.c.html et modifier
{
    do {
        if (tolower(*s) == tolower(c)) {
            return (char*)s;
        }
    } while (*s++);
    return (0);
}