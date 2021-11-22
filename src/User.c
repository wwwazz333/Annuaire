#include "User.h"

user input_user()
{
    user u;
    setColor(ORANGE);
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

int insert_user(user tab[], int taille, user u)
{
    return 0;
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