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
    //! la ville où habite l'utilisateur
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
 * @brief demande d'entrer tous les attribues d'un user (nom, prenom, ville, etc...)
 *
 * @pre aucune
 * @post retourne le "user" avec les information donnée sans virgule
 *
 * @return la variable u
 */
user input_user();

/**
 * @brief copie l'usr "src" dans "dst"
 *
 * @pre aucune
 * @post pour tous les attribue de "src" et "dst" => dst.atr = src.atr
 *
 * @param dst le "user" destination
 * @param src le "user" source
 */
void usercpy(user* dst, user* src);

/**
 * @brief supprime l'utilisateur a l'index "id"
 *
 * @pre aucune
 * @post le "user" a l'index "id" est supprimer (toutes les valeurs à ""), 0 est retourné ssi il a pu être supprimer
 *
 * @param tab le tableau
 * @param id l'index a supprimer (véritable index du tableau)
 * @param taille la taille de "tab"
 */
int del_user(user tab[], int id, int taille);

/**
 * @brief insert "u" dans "tab" au bonne emplacement et agrandi si nécessaire
 *
 * @pre aucune
 * @post "u" est dans "tab" au bonne endroit et retourne EXIT_SUCCESS ssi aucune erreur
 *
 * @param tab le tableau
 * @param taille la taille de "tab"
 * @param u le "user" à ajouter
 * @param which sur quelle paramètre est trié "tab"
 */
int insert_user(user* tab[], int* taille, user u, int which);

/**
 * @brief modifie l'utilisateur "replace_by"
 *
 * @pre ligne un index de tableau
 * @post on modifie "replace_by" par de nouvelle donnée entrer. Si la case est vide, on garde l'ancienne valeur. Retourne EXIT_SUCCESS ssi aucune erreur
 *
 */
int modif_user(user* replace_by);


/**
 * @brief affiche selon certaine condition.
 * 
 * @pre "func_compare" retourne un int et prend en paramètre 2 const char* (les chaine de caractère à comparer)
 * @post affiche les "user" qui réponde à la condition de "func_compare" entre la valeur de sont paramètre "which" et de "string". Si il y a une erreur ne fait rien.
 * 
 * @param tab le tableau
 * @param taille la taille de "tab"
 * @param string la chaine de caractères à rechercher
 * @param which quelle paramètre rechercher
 * @param size_wanted_for_which la taille du paramètre "which"
 * @param func_compare la fonction qui servira de condition pour l'affichage
 */
void recherche_in_tab(user tab[], int taille, char* string, int which, int size_wanted_for_which, int (*func_compare)(const char*, const char*));

/**
 * @brief affiche tous les "user" qui on pour sous-chaine "substring" au paramètre "which".
 * 
 * @pre aucune
 * @post affiche tous les "user" qui on pour sous-chaine "substring" au paramètre "which". Si il y a une erreur ne fait rien.
 * 
 * @param tab le tableau
 * @param taille la taille de "tab"
 * @param substring la sous-chaine de caractère à rechercher
 * @param which quelle paramètre rechercher
 */
void recherche_substring(user tab[], int taille, char* substring, int which);

/**
 * @brief affiche tous les "user" qui commencent par la chaine "string" au paramètre "which".
 * 
 * @pre aucune
 * @post affiche tous les "user" qui commencent par la chaine "string" au paramètre "which". Si il y a une erreur ne fait rien.
 * 
 * @param tab le tableau
 * @param taille la taille de "tab"
 * @param string la sous-chaine de caractère à rechercher
 * @param which quelle paramètre rechercher
 */
void recherche_string(user tab[], int taille, char* string, int which);

/**
 * @brief affiche tous les "user" qui on la chaine "string" au paramètre "which".
 * 
 * @pre aucune
 * @post affiche tous les "user" qui on la chaine "string" au paramètre "which". Si il y a une erreur ne fait rien.
 * 
 * @param tab le tableau
 * @param taille la taille de "tab"
 * @param string la sous-chaine de caractère à rechercher
 * @param which quelle paramètre rechercher
 */
void recherche_exacte(user tab[], int taille, char* string, int which);

/**
 * @brief affiche tous les "user" à qui il manque le paramètre which.
 * 
 * @pre aucune
 * @post affiche tous les "user" qui on la chaine vide au paramètre "which". Si il y a une erreur ne fait rien.
 * 
 * @param tab le tableau
 * @param taille la taille de "tab"
 * @param which quelle paramètre rechercher
 */
void recherche_element_manquant(user tab[], int taille, int which);


/**
 * @brief affiche tous les "user" à qui il manque un paramètre.
 * 
 * @pre aucune
 * @post affiche tous les "user" qui on au moins une chaine vide a un des paramètres. Si il y a une erreur ne fait rien.
 * 
 * @param tab le tableau
 * @param taille la taille de "tab"
 * @param which quelle paramètre rechercher
 */
void recherche_tous_manquante(user tab[], int taille);

/**
 * @brief retourne le paramètre "which_one" de "u".
 * 
 * @pre aucune
 * @post retourne la chaine de caractère qui correspond à la valeur du paramètre "which_one" de "u".
 * 
 * @param u pointeur sur le "user" voulu
 * @param which_one quelle paramètre retourner
 * @return la chaine de caractère
 */
char* get_arg(user* u, int which_one);

/**
 * @brief retourne la taille du paramètre "which_one".
 * 
 * @pre aucune
 * @post retourne la taille du paramètre "which_one".
 * 
 * @param which_one quelle paramètre
 * @return taille du paramètre "which_one"
 */
int get_size_arg(int which_one);

/**
 * @brief Affiche le "user" s'il n'est pas supprimé.
 * 
 * @pre aucune
 * @post Affiche le "user" s'il n'est pas supprimé avec l'index donnée (au format classique donc index+1). 
 * 
 * @param u le "user" à afficher.
 * @param id l'index de "user" serre uniquement à l'affichage
 */
void print_user(user u, int id);

/**
 * @brief u1 == u2
 * 
 * @pre aucune
 * @post retrourne 1 ssi u1 == u2
 */
int userEqual(user* u1, user* u2);

/**
 * @brief Detecte des doublons dans tab
 * 
 * @pre aucune
 * @post Detecte des doublons dans tab
 * 
 * @param tab le tableau
 * @param taille la taille de "tab"
 * @param which_trier sur quelle paramètre tab est tirer
 * 
 * @return 0 si aucun doublon et 1 si il y en a un au moins 1
 */
int exist_doublon(user tab[], int taille, int which_trier);

/**
 * @brief affiche les user qui sont présent plusieur fois
 * 
 * @pre aucune
 * @post affiche les user qui sont présent plusieur fois dans "tab"
 * 
 * @param tab le tableau
 * @param taille la taille de "tab"
 * @param which_trier sur quelle paramètre tab est tirer
 */
void recherche_doublon(user tab[], int taille, int which_trier);

#endif