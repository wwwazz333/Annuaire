#ifndef _USER_H_
#define _USER_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>




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
    char prenom[SIZE_PRENOM];
    char nom[SIZE_NOM];
    //! la ville où habite habite l'utilisateur
    char ville[SIZE_VILLE];
    //! le code postal de la ville avec 5 chiffres (ex : "69100")
    char code_postal[SIZE_CODE_POSTAL];
    //! numéro de téléphone de l'utilisateur au format 06.01.02.03.04 et
    //! possiblement au format +2296.01.02.03.04
    char no_telephone[SIZE_NO_TELEPHONE];
    //! l'email de l'utilisateur
    char email[SIZE_EMAIL];
    //! le métier de l'utilisateur (ex : "exemple.exemple@mail.ex")
    char metier[SIZE_METIER];
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
 * @brief suprime l'utilisateur a l'index id
 * 
 * @pre id un index de tableau
 * @post le user a l'index id est supprimer (toutes les valeurs à ""), 0 est retourné ssi il a pu être supprimer
 * 
 * @param tab le tableau
 * @param id l'index a supprimer
 * @param taille taille du tableau
 * @return int 0 ssi il a pu etre supprimer
 */
int del_user(user tab[], int id, int taille);

/**
 * @brief insert u dans tab au bonne emplacement et agrandi si nécessaire
 * 
 * @pre aucune
 * @post u est dans le tableau au bonne endroit
 * 
 * @param tab 
 * @param taille 
 * @param u 
 * @return int 
 */
int insert_user(user* tab[], int* taille, user u, int which);

/**
 * @brief modifie l'utilisateur a l'index ligne
 * 
 * @pre ligne un index de tableau
 * @post on modifie user par son id, si la case est vide, on garde l'ancienne valeur.
 * 
 * @param tab le tableau
 * @param id l'id de l'utilisateur à modifié
 * @param taille taille du tableau
 * @return int 0 ssi il a pu etre modifier
 */
int modif_user(user tab[], int id, int taille);

/**
 * @brief retourne l'emplacement où ajouté l'utilisateur avec pour nom "nom"
 * 
 * @pre acune
 * @post retourne l'index où doit être l'utilisateur qui a pour nom "nom"
 * 
 * @param tab 
 * @param taille 
 * @param nom 
 * @return int 
 */
int recherche_emplacement(user tab[], int taille, char* information, int which);

int recherche_emplacement_existant(user tab[], int taille, char* information, int which);

void recherche_substring(user tab[], int taille, char* substring, int which);
void recherche_string(user tab[], int taille, char* string, int which);
void recherche_element_manquant(user tab[], int taille, int which);
void recherche_tous_manquante(user tab[], int taille);


user* recherche_by_id(user tab[], int taille, int id);


char* get_arg(user* u, int which_one);
int get_size_arg(int which_one);


void print_user(user u, int id);
#endif
