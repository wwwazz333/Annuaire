#include "User.h"
#include "tri.h"

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
        return 1;
    }
    tableau[id].nom[0] = '\0';
    tableau[id].prenom[0] = '\0';
    tableau[id].ville[0] = '\0';
    tableau[id].code_postal[0] = '\0';
    tableau[id].no_telephone[0] = '\0';
    tableau[id].email[0] = '\0';
    tableau[id].metier[0] = '\0';
    return 0;
}

int is_del(user u)
{
    if (
        u.nom[0] == '\0' && u.prenom[0] == '\0' && u.ville[0] == '\0' && u.code_postal[0] == '\0' && u.no_telephone[0] == '\0' && u.email[0] == '\0' && u.metier[0] == '\0') {
        return 1;
    }
    return 0;
}

int insert_user(user tab[], int taille, user u)
{
    int gauche, droite, index_a_ajouter, millieu;
    gauche = 0;
    droite = taille - 1;
    while (gauche < droite) {
        millieu = (gauche + droite) / 2;
        if (strcmp(&u.nom, &tab[millieu].nom) < 0) {
            droite = millieu - 1;
        } else if (strcmp(&u.nom, &tab[millieu].nom) > 0) {
            gauche = millieu + 1;
        } else {
            index_a_ajouter = millieu + 1;
        }
    }
    printf("on ajoute à %d\n", index_a_ajouter);

    permute(&tab[index_a_ajouter], &u);
    int i = 1;
    while (i < taille && is_del(u) != 1) {
        permute(&tab[index_a_ajouter + i], &u);

        i++;
    }
    if (is_del(u) != 1) {
        printf("il n'y avais pas assez de place dans le tableau et on a pas encore prévue\n");
    }

    return 0;
}

int recherche(user tab[], int taille, char nom[64])
{
    int i;
    int gauche = 0;
    int droite = taille - 1;
    while (gauche < droite) {
        i = (droite + gauche) / 2;
        if (strcmp(&tab[i].nom, nom) < 0) {
            printf("décale gauche\n");
            gauche = i + 1;
        } else if (strcmp(&tab[i].nom, nom) > 0) {
            printf("décale droite\n");
            droite = i - 1;
        } else {
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