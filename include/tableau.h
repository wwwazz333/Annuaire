#ifndef _tri_h_
#define _tri_h_

#include "User.h"
#include "string.h"

typedef enum {
    TRIE_PRENOM,
    TRIE_NOM,
    TRIE_VILLE,
    TRIE_CODE_POSTAL,
    TRIE_NO_TELEPHONE,
    TRIE_EMAIL,
    TRIE_METIER,
	TRIE_NULL
} TrierSur;

/**
 * @brief tire le tableau tab de l'indice first à last
 *
 * @pre first et last des index de tab
 * @post le tableau tab est tiré par le nom
 *
 * @param tab le tableau a trié
 * @param first où commencer
 * @param last recommander : len-1
 */
void quick_sort(user* tab, int first, int last);
void quick_sort_on(user* tab, int first, int last, TrierSur which);

/**
 * @brief permute user a et b
 *
 * @pre aucune
 * @post a et b sont permuté
 *
 * @param a
 * @param b
 */
void permute(user* a, user* b);

/**
 * @brief agrandi la taille de tab à new_siez
 *
 * @pre new_size >= curr_size
 * @post tab a pour taille new_size et contien les même éléments
 *
 * @param tab un pointeur de tableau
 * @param curr_size la taille de tab actuelle
 * @param new_size la taille de tab désirer
 */
void add_space(user** tab, int curr_size, int new_size);



void print_tab(user* tab, int size_tab);

#endif
