#include "Save.h"

#include "Verif.h"

// TODO : nb_carcactère max d'une ligne : sizeof(user)/sizeof(char) + '\n'

char* readUntil(char* depart, char* dst, int taille_max_dst, char fin)
{
    long int distance_char_fin = strchr(depart, fin) - depart;

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

    char* first = &ligne[0]; // pareille que first = ligne;

    first = readUntil(first, u->nom, SIZE_NOM, ',');
    first = readUntil(first, u->prenom, SIZE_PRENOM, ',');
    first = readUntil(first, u->ville, SIZE_VILLE, ',');
    first = readUntil(first, u->code_postal, SIZE_CODE_POSTAL, ',');
    first = readUntil(first, u->no_telephone, SIZE_NO_TELEPHONE, ',');
    first = readUntil(first, u->email, SIZE_EMAIL, ',');
    first = readUntil(first, u->metier, SIZE_METIER, '\n');

    return EXIT_SUCCESS;
}
int load(FILE* fp, user* users, int taille_user)
{
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    int nb = nombre_utilisateurs(fp);
    if (nb > taille_user) {
        return 2; // autre type d'erreur
    }
    fseek(fp, 0, SEEK_SET);
    int i = 0;
    while (i < nb) {
        readUser(fp, &users[i]);
        if (!is_del(users[i])) {
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

    return EXIT_SUCCESS;
}
int save(FILE* fp, user* users, int nombre_user)
{
    fseek(fp, 0, SEEK_SET);
    int i;
    for (i = 0; i < nombre_user; i++) {
        if (!is_del(users[i])) {
            writeUser(fp, &users[i]);
        }
    }

    return EXIT_SUCCESS;
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
