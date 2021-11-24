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

int insert_user(user* tab[], int taille, user u)
{
    int index_a_ajouter = recherche_emplacement(*tab, taille, u.nom);
    if(index_a_ajouter < 0){
        return EXIT_FAILURE;
    }
    permute(&(*tab)[index_a_ajouter], &u);
    index_a_ajouter++;
    while (index_a_ajouter < taille && is_del(u) != 1) {
        permute(&(*tab)[index_a_ajouter], &u);

        index_a_ajouter++;
    }
    if (!is_del(u)) {
        printf("il n'y avais pas assez de place dans le tableau\n");
        add_space(tab, taille, taille+1);
        permute(&(*tab)[taille], &u);
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
        } else {
            while (strcmp((char*)&tab[millieu + 1].nom, nom) == 0) {
                gauche++;
            }
            return gauche;
        }
    }
    return gauche;
}
void usercpy(user* dst, user* src)
{
    if (dst == NULL || src == NULL) {
        return;
    }
    strcpy(dst->prenom, src->prenom);
    strcpy(dst->nom, src->nom);
    strcpy(dst->ville, src->ville);
    strcpy(dst->code_postal, src->code_postal);
    strcpy(dst->no_telephone, src->no_telephone);
    strcpy(dst->email, src->email);
    strcpy(dst->metier, src->metier);
}