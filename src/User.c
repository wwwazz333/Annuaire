#include "User.h"
#include "tri.h"
#include "Verif.h"

user input_user()
{
    user u;
    printf("\nEntrez le nom : ");
    input(u.nom, SIZE_NOM);

    printf("\nEntrez le prenom : ");
    input(u.prenom, SIZE_PRENOM);

    printf("\nEntrez la ville : ");
    input(u.ville, SIZE_VILLE);

    printf("\nEntrez le code postal : ");
    input(u.code_postal, SIZE_CODE_POSTAL);

    printf("\nEntrez le numero de telephone : ");
    input(u.no_telephone, SIZE_NO_TELEPHONE);

    printf("\nEntrez l'email : ");
    input(u.email, SIZE_EMAIL);

    printf("\nEntrez le metier : ");
    input(u.metier, SIZE_METIER);

    return u;
}




int insert_user(user tab[], int taille, user u)
{
    int index_a_ajouter = recherche_emplacement(tab, taille, u.nom);
    printf("on ajoute à %d\n", ++index_a_ajouter);

    permute(&tab[index_a_ajouter], &u);
    int i = 1;
    while (i < taille && is_del(u) != 1) {
        permute(&tab[index_a_ajouter + i], &u);

        i++;
    }
    if (is_del(u) != 1 || index_a_ajouter >= taille) {
        printf("il n'y avais pas assez de place dans le tableau et on a pas encore prévue\n");
    }

    return 0;
}

int recherche_emplacement(user tab[], int taille, char nom[64]) // recherche le dernier
{
    int i = -1;
    int gauche = 0;
    int droite = taille - 1;
    while (gauche <= droite) {
        i = (droite + gauche) / 2;
        if (strcmp((char*)&tab[i].nom, nom) < 0) {
            gauche = i + 1;
        } else if (strcmp((char*)&tab[i].nom, nom) > 0) {
            droite = i - 1;
        } else {
            while (strcmp((char*)&tab[i + 1].nom, nom) == 0) {
                i++;
            }
            return i;
        }
    }
    return i;
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