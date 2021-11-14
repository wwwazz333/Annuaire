#include "Save.h"

//TODO : nb_carcactère max d'une ligne : sizeof(user)/sizeof(char) + '\n'

int readUntil(FILE* fp, char* str, int taille_str, char fin)
{
    if (fp == NULL) {
        return 1;
    }
    int i = 0;
    while ((str[i] = getc(fp)) != fin && i < taille_str - 1) { // on lit un caractèrer et on verifie qu'il y a assez de place dans str (en comptant '\0') et que se n'est pas le caractère de fin
        if (str[i] == EOF) {
            return EOF;
        }
        i++;
    }
    str[i] = '\0';
    return 0;
}
char* readU(char* depart, char* dst, int taille_max_dst, char fin)
{
    int i = 0;

    while (*(depart + i) != fin && i < taille_max_dst - 1) {
        dst[i] = *(depart + i);
        i++;
    }
    dst[i] = '\0';
    return (depart + i + 1);
}
char* readU2(char* depart, char* dst, int taille_max_dst, char fin)
{
    long int distance_char_fin = strchr(depart, fin) - depart;

    if (distance_char_fin >= taille_max_dst) { // trop grand
        distance_char_fin = taille_max_dst - 1;
    }
    memcpy(dst, depart, distance_char_fin);
    dst[distance_char_fin] = '\0';

    return (depart + distance_char_fin + 1);
}
/*
char* readU3(char* depart, char* dst, int taille_max_dst, char* fin)
{
    long int distance_char_fin;
    long int temp;
    for (int i = 0; fin[i] != '\0'; i++) {
        if ((temp = strchr(depart, fin[i]) - depart) != NULL) {
            if (temp < distance_char_fin) {
                distance_char_fin = temp;
            }
        }
    }

    if (distance_char_fin >= taille_max_dst) { // trop grand
        distance_char_fin = taille_max_dst - 1;
    }
    memcpy(dst, depart, distance_char_fin);
    dst[distance_char_fin] = '\0';

    return (depart + distance_char_fin + 1);
}
*/
int readUser(FILE* fp, user* u)
{
    if (fp == NULL) {
        return 1;
    }
    char ligne[TAILLE_MAX_LIGNE];
    if (fgets(ligne, TAILLE_MAX_LIGNE, fp) == NULL) {
        return EOF;
    }

    char* first = &ligne[0]; // pareille que first = ligne;

    first = readU2(first, u->nom, SIZE_NOM, ',');
    first = readU2(first, u->prenom, SIZE_PRENOM, ',');
    first = readU2(first, u->ville, SIZE_VILLE, ',');
    first = readU2(first, u->code_postal, SIZE_CODE_POSTAL, ',');
    first = readU2(first, u->no_telephone, SIZE_NO_TELEPHONE, ',');
    first = readU2(first, u->email, SIZE_EMAIL, ',');
    first = readU2(first, u->metier, SIZE_METIER, '\n');

    return 0;
    /*
        readUntil(fp, u->nom, SIZE_NOM, ',');
        readUntil(fp, u->prenom, SIZE_PRENOM, ',');
        readUntil(fp, u->ville, SIZE_VILLE, ',');
        readUntil(fp, u->code_postal, SIZE_CODE_POSTAL, ',');
        readUntil(fp, u->no_telephone, SIZE_NO_TELEPHONE, ',');
        readUntil(fp, u->email, SIZE_EMAIL, ',');
        return readUntil(fp, u->metier, SIZE_METIER, '\n'); // car readUntil retourne EOF donc fin du fichier si c'est la fin du fichier
        // return fscanf(fp, "%s,%s,%s,%s,%s,%s,%s\n", u->nom, u->prenom, u->ville, u->code_postal, u->no_telephone, u->email, u->metier);
    */
}
int load(FILE* fp, user* users, int taille_user)
{
    if (fp == NULL) {
        return 1;
    }
    int nb = nombre_utilisateurs(fp);
    if (nb > taille_user) {
        return 2;
    }
    fseek(fp, 0, SEEK_SET);
    int i = 0;
    while (i < nb) {
        readUser(fp, &users[i]);
        if (users[i].nom[0] != '\0' || users[i].prenom[0] != '\0' || users[i].ville[0] != '\0' || users[i].code_postal[0] != '\0' || users[i].no_telephone[0] != '\0' || users[i].email[0] != '\0' || users[i].metier[0] != '\0') {
            i++;
        }
    }

    return 0;
}

int writeUser(FILE* fp, user* u)
{
    if (fp == NULL) {
        return 1;
    }

    // plus lent
    // fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", u->nom, u->prenom, u->ville, u->code_postal, u->no_telephone, u->email, u->metier);

    fputs(u->nom, fp);
    fputc(',', fp);

    fputs(u->prenom, fp);
    fputc(',', fp);

    fputs(u->ville, fp);
    fputc(',', fp);

    fputs(u->code_postal, fp);
    fputc(',', fp);

    fputs(u->no_telephone, fp);
    fputc(',', fp);

    fputs(u->email, fp);
    fputc(',', fp);

    fputs(u->metier, fp);
    fputc('\n', fp);

    return 0;
}
int save(FILE* fp, user* users, int nombre_user)
{
    fseek(fp, 0, SEEK_SET);
    for (int i = 0; i < nombre_user; i++) {
        if (users[i].nom[0] != '\0' || users[i].prenom[0] != '\0' || users[i].ville[0] != '\0' || users[i].code_postal[0] != '\0' || users[i].no_telephone[0] != '\0' || users[i].email[0] != '\0' || users[i].metier[0] != '\0') {
            writeUser(fp, &users[i]);
        }
    }

    return 0;
}

int nombre_utilisateurs(FILE* fp)
{
    if (fp == NULL) {
        return -2;
    }
    fseek(fp, 0, SEEK_SET);
    int nb_ligne = 0;

    char str[TAILLE_MAX_LIGNE]; // sizeof(user)/sizeof(char) = 536
    while (fgets(str, TAILLE_MAX_LIGNE, fp) != NULL) {
        if (str[6] != '\n') {
            nb_ligne++;
        }
    }

    return nb_ligne;
}
