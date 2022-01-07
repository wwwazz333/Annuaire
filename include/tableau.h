#ifndef _tri_h_
#define _tri_h_

#include "User.h"

typedef enum {
    TRIE_PRENOM,
    TRIE_NOM,
    TRIE_VILLE,
    TRIE_CODE_POSTAL,
    TRIE_NO_TELEPHONE,
    TRIE_EMAIL,
    TRIE_METIER,
    TIRE_TOUS,
    TRIE_NULL
} TrierSur;
/**
 * @brief tri le tableau
 *
 * @pre tab non NULL
 * @post le tableau tab est trié par l'attribut indiqué par which
 *
 * @param tab le tableau a trié
 * @param taille len-1
 * @param which sur quelle attribut trié
 */
void oyelami(user* tab, int taille, TrierSur which);

/**
 * @brief tire le tableau tab de l'indice first à last
 *
 * @pre first et last des index de tab et tab non NULL
 * @post le tableau tab est trié par l'attribut indiqué par which
 *
 * @param tab le tableau a trié
 * @param first où commencer
 * @param last recommander : len-1
 * @param which sur quelle attribut trié
 */
void quick_sort(user* tab, int first, int last, TrierSur which);

/**
 * @brief permute user a et b
 *
 * @pre aucune
 * @post a et b sont permuté
 *
 */
void permute(user* a, user* b);

/**
 * @brief agrandi la taille de tab à new_siez
 *
 * @pre new_size >= curr_size et tab non NULL
 * @post tab a pour taille new_size et contien les même éléments
 *
 * @param tab un pointeur de tableau (soit pointeur de pointeur)
 * @param curr_size la taille de tab actuelle
 * @param new_size la taille de tab désirer
 */
void add_space(user** tab, int curr_size, int new_size);

/**
 * @brief affiche le tableau de user tab
 *
 * @pre aucune
 * @post affiche le contenue de tab avec de la couleur
 */
void print_tab(user* tab, int size_tab);

/**
 * @brief affiche le tableau de user tab sectionner par section
 *
 * @pre aucune
 * @post affiche le contenue de tab avec de la couleur et sectionner par section
 * 
 * @param section valeur par laquelle l'affichage est divisé
 */
void print_tab_sect(user* tab, int size_tab, int section);

/**
 * @brief donne le nombre de "user" supprimer
 * 
 * @pre aucune
 * @post retourne le nombre de "user" supprimer ou -1 si il y a une erreur
 */
int get_nombre_user_del(user* tab, int size_tab);

/**
 * @brief déplace le "user" de l'index "index" à la fin de "tab"
 * 
 * @pre aucune
 * @post le "user" de l'index "index" est à la fin de "tab"
 * 
 * @param tab le tableau
 * @param size_tab la taille de "tab"
 * @param index l'index du "user" à déplacer
 */
void move_user_to_end(user* tab, int size_tab, int index);

#endif
