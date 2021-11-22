#ifndef _tri_h_
#define _tri_h_

#include "User.h"
#include "string.h"
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

#endif
