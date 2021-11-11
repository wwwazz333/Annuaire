#ifndef _USER_H_
#define _USER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Verif.h"

#define SIZE_PRENOM 64
#define SIZE_NOM 64
#define SIZE_VILLE 128
#define SIZE_CODE_POSTAL 6
#define SIZE_NO_TELEPHONE 18
#define SIZE_EMAIL 128
#define SIZE_METIER 128
/**
 * @brief Un "user" est une personne qui sera stocker dans l'annuaire
 *
 */
typedef struct {
    char prenom[64];
    char nom[64];
    //! la ville où habite habite l'utilisateur
    char ville[128];
    //! le code postal de la ville avec 5 chiffres (ex : "69100")
    char code_postal[6];
    //! numéro de téléphone de l'utilisateur au format 06.01.02.03.04 et
    //! possiblement au format +2296.01.02.03.04
    char no_telephone[18];
    //! l'email de l'utilisateur
    char email[128];
    //! le métier de l'utilisateur (ex : "exemple.exemple@mail.ex")
    char metier[128];
} user;



/**
 * @brief demande d'entrer tous les attribu d'un user (nom, prenom, ville,
 * etc...)
 * 
 * @pre aucune
 * @post retourne le "user" avec les information rendu
 *
 * @return le "user" avec les information rendu
 */
user input_user();
/**
 * @brief copie l'usr src dans dst
 * 
 * @pre dst et src non NULL
 * @post pour tous les attribue de src et dst => dst.atr = src.atr
 * 
 * @param dst la destination
 * @param src la source
 */
void usercpy(user* dst, user* src);

/**
 * @brief suprime l'utilisateur a l'index ligne
 * 
 * @pre ligne un index de tableau
 * @post le user a l'index ligne est supprimer (toutes les valeurs à ""), 0 est retourné ssi il a pu être supprimer
 * 
 * @param tableau le tableau
 * @param ligne l'index a supprimer
 * @param taille taille du tableau
 * @return int 0 ssi il a pu etre supprimer
 */
int del_user(user tableau[], int ligne, int taille);

#endif
