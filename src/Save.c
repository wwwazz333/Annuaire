#include "Save.h"

#include "Verif.h"

char* readUntil(char* depart, char* dst, int taille_max_dst, char fin)
{
    if(depart == NULL || dst == NULL){
        return NULL;
    }
    char* emplacement_char_fin = strchr(depart, fin);
    if (emplacement_char_fin == NULL){
        return NULL;
    }
    long int distance_char_fin = emplacement_char_fin - depart;
    if (distance_char_fin >= taille_max_dst) { // trop grand
        distance_char_fin = taille_max_dst - 1;
    }
    memcpy(dst, depart, distance_char_fin);
    dst[distance_char_fin] = '\0';

    return (depart + distance_char_fin + 1);
}

int readUser(FILE* fp, user* u)
{
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    char ligne[TAILLE_MAX_LIGNE];
    if (fgets(ligne, TAILLE_MAX_LIGNE, fp) == NULL) {
        return EOF;
    }
    if (strlen(ligne) < 7) {//si il le fichier csv a des erreurs ou que le "user" a tous ses paramètre vide
        return EXIT_FAILURE;
    }
    char* first = &ligne[0]; // pareille que first = ligne;

    first = readUntil(first, u->prenom, SIZE_PRENOM, ',');
    first = readUntil(first, u->nom, SIZE_NOM, ',');
    first = readUntil(first, u->ville, SIZE_VILLE, ',');
    first = readUntil(first, u->code_postal, SIZE_CODE_POSTAL, ',');
    first = readUntil(first, u->no_telephone, SIZE_NO_TELEPHONE, ',');
    first = readUntil(first, u->email, SIZE_EMAIL, ',');
    readUntil(first, u->metier, SIZE_METIER, '\n');

    return EXIT_SUCCESS;
}
int load(FILE* fp, user tab[])
{
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    int nb = nombre_utilisateurs(fp);
    fseek(fp, 0, SEEK_SET);
    int i = 0;
    while (i < nb) {
        if (readUser(fp, &tab[i]) == EXIT_SUCCESS) {
            i++;
        }
    }

    return EXIT_SUCCESS;
}

int writeUser(FILE* fp, user* u)
{
    if (fp == NULL) {
        return EXIT_FAILURE;
    }

    fputs(u->prenom, fp);
    fputc(',', fp);

    fputs(u->nom, fp);
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

    return EXIT_SUCCESS;
}
void save(FILE* fp, user tab[], int nombre_users)
{
    fseek(fp, 0, SEEK_SET);
    int i;
    for (i = 0; i < nombre_users; i++) {
        if (!is_del(tab[i])) {
            writeUser(fp, &tab[i]);
        }
    }
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
        if (/*str[6] != '\n'*/ strlen(str) > 6) { //pour être sur qu'il y a le moins d'erreur possible dans le csv
            nb_ligne++;
        }
    }

    return nb_ligne;
}