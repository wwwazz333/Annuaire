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
    while (gauche <= droite) {
        millieu = (droite + gauche) / 2;
        if (strcmp((char*)&tab[millieu].nom, nom) < 0) {
            gauche = millieu + 1;
        } else if (strcmp((char*)&tab[millieu].nom, nom) > 0) {
            droite = millieu - 1;
        } else { // si égale
            do {
                millieu++;
            } while (strcmp((char*)&tab[millieu].nom, nom) == 0);
            return millieu;

            while (strcmp((char*)&tab[millieu + 1].nom, nom) == 0) {
                millieu++;
            }
            return millieu + 1;
        }
    }
    return gauche;
}

int recherche_emplacement_existant(user tab[], int taille, char nom[64])
{
    int millieu;
    int gauche = 0;
    int droite = taille - 1;
    while (gauche <= droite) {
        millieu = (droite + gauche) / 2;
        if (strcmp((char*)&tab[millieu].nom, nom) < 0) {
            gauche = millieu + 1;
        } else if (strcmp((char*)&tab[millieu].nom, nom) > 0) {
            droite = millieu - 1;
        } else { // si égale cherche le dernier
            while (strcmp((char*)&tab[millieu+1].nom, nom) == 0){
                millieu++;
            }
            return millieu;

        }
    }
    return -1;
}
user* recherche_substring(user tab[], int taille, const char* substring, int* taille_tableau_retourner){
    user* tab_substring;
    tab_substring = malloc(taille*sizeof(user));

    for (int i = 0, j = 0; i < taille; i++)
    {
        if(strstr(tab[i].nom, substring)){
            usercpy(&tab_substring[j], &tab[i]);
            j++;
        }
    }
    


    return tab_substring;
}


void usercpy(user* dst, user* src)
{
    if (dst == NULL || src == NULL) {
        return;
    }
    memcpy(dst, src, sizeof(user));
}