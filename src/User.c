#include "User.h"

#include "Verif.h"
#include "tableau.h"

user input_user()
{
    user u;
    setColor(ORANGE);
    printf("\nEntrez le nom : ");
    setColor(AQUA);
    input(u.nom, SIZE_NOM);

    setColor(ORANGE);
    printf("\nEntrez le prenom : ");
    setColor(AQUA);
    input(u.prenom, SIZE_PRENOM);

    setColor(ORANGE);
    printf("\nEntrez la ville : ");
    setColor(AQUA);
    input(u.ville, SIZE_VILLE);

    setColor(ORANGE);
    printf("\nEntrez le code postal : ");
    setColor(AQUA);
    input(u.code_postal, SIZE_CODE_POSTAL);

    setColor(ORANGE);
    printf("\nEntrez le numero de telephone : ");
    setColor(AQUA);
    input(u.no_telephone, SIZE_NO_TELEPHONE);

    setColor(ORANGE);
    printf("\nEntrez l'email : ");
    setColor(AQUA);
    input(u.email, SIZE_EMAIL);

    setColor(ORANGE);
    printf("\nEntrez le metier : ");
    setColor(AQUA);
    input(u.metier, SIZE_METIER);
    setDefaultColor();

    return u;
}
int del_user(user tableau[], int id, int taille)
{
    if (id < 0 || id >= taille) {
        return -1;
    }
    strcpy(tableau[id].nom, "\0");
    strcpy(tableau[id].prenom, "\0");
    strcpy(tableau[id].ville, "\0");
    strcpy(tableau[id].code_postal, "\0");
    strcpy(tableau[id].no_telephone, "\0");
    strcpy(tableau[id].email, "\0");
    strcpy(tableau[id].metier, "\0");
    return 0;
}

int insert_user(user* tab[], int* taille, user u)
{
    if (is_del(u)) {
        printf("Vous ne pouvez pas ajouté un utilisateur vide.\n");
        return EXIT_FAILURE;
    }
    int index_a_ajouter = recherche_emplacement(*tab, *taille, u.nom);
    if (index_a_ajouter < 0) {
        return EXIT_FAILURE;
    }

    while (index_a_ajouter < *taille && !is_del(u)) {
        permute(&(*tab)[index_a_ajouter], &u);

        index_a_ajouter++;
    }

    if (!is_del(u)) {
        add_space(tab, *taille, *taille + 1);
        permute(&(*tab)[*taille], &u);
        (*taille)++;
    }

    return EXIT_SUCCESS;
}

int recherche_emplacement(user tab[], int taille, char nom[64]) // recherche le dernier
{
    int millieu;
    int gauche = 0;
    int droite = taille - 1;

    char* name_lower = malloc(64 * sizeof(char));
    char* curr_name_lower = malloc(64 * sizeof(char));

    strtolower(name_lower, nom, 64);

    while (gauche <= droite) {
        millieu = (droite + gauche) / 2;
        strtolower(curr_name_lower, tab[millieu].nom, 64);
        if (strcmp(curr_name_lower, name_lower) < 0) {
            gauche = millieu + 1;
        } else if (strcmp(curr_name_lower, name_lower) > 0) {
            droite = millieu - 1;
        } else { // si égale
            do {
                millieu++;
                strtolower(curr_name_lower, tab[millieu].nom, 64);
            } while (strcmp(curr_name_lower, name_lower) == 0);

            free(name_lower);
            free(curr_name_lower);
            return millieu;
        }
    }

    free(name_lower);
    free(curr_name_lower);
    return gauche;
}

int recherche_emplacement_existant(user tab[], int taille, char nom[64])
{
    int millieu;
    int gauche = 0;
    int droite = taille - 1;

    char* name_lower = malloc(64 * sizeof(char));
    char* curr_name_lower = malloc(64 * sizeof(char));

    strtolower(name_lower, nom, 64);

    while (gauche <= droite) {
        millieu = (droite + gauche) / 2;
        strtolower(curr_name_lower, tab[millieu].nom, 64);
        if (strcmp(curr_name_lower, name_lower) < 0) {
            gauche = millieu + 1;
        } else if (strcmp(curr_name_lower, name_lower) > 0) {
            droite = millieu - 1;
        } else { // si égale cherche le dernier
            while (strcmp(curr_name_lower, name_lower) == 0) {
                millieu++;
                strtolower(curr_name_lower, tab[millieu].nom, 64);
            }

            free(name_lower);
            free(curr_name_lower);
            return millieu;
        }
    }

    free(name_lower);
    free(curr_name_lower);
    return -1;
}
void recherche_substring(user tab[], int taille, char* substring)
{

    char* substring_lower = malloc((strlen(substring) + 1) * sizeof(char));
    char* curr_name_lower = malloc((64 + 1) * sizeof(char));

    strtolower(substring_lower, substring, strlen(substring) + 1);

    for (int i = 0, j = 0; i < taille; i++) {
        strtolower(curr_name_lower, tab[i].nom, 64);
        if (strstr(curr_name_lower, substring_lower) != NULL) {
            if (j % 2 == 0) {
                setColor(PURPLE);
            } else {
                setColor(WHITE);
            }
            printf("[%d] %s, %s, %s, %s, %s, %s, %s", i + 1, tab[i].nom, tab[i].prenom, tab[i].ville, tab[i].code_postal, tab[i].no_telephone, tab[i].email, tab[i].metier);
            setDefaultColor();
            printf("\n");
            j++;
        }
    }

    free(substring_lower);
    free(curr_name_lower);
}

void usercpy(user* dst, user* src)
{
    if (dst == NULL || src == NULL) {
        return;
    }
    memcpy(dst, src, sizeof(user));
}

char* get_arg(user* u, int which_one)
{
    switch (which_one) {
    case 0:
        return u->prenom;
        break;
    case 1:
        return u->nom;
        break;
    case 2:
        return u->ville;
        break;
    case 3:
        return u->code_postal;
        break;
    case 4:
        return u->no_telephone;
        break;
    case 5:
        return u->email;
        break;
    case 6:
        return u->metier;
        break;
    }
    return NULL;
}
