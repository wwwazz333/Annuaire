#ifndef _VERIF_H_
#define _VERIF_H_

#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

#include "Terminal.h"
#include "User.h"


/**
 * @brief récuper les caractère entrer et les place dans str
 *
 * @pre aucune
 * @post str contient les caractère taper (sans '\n' mais avec '\0') et le tampon est vide
 *
 * @param str la chaine a modifier
 * @param sizeof_str la taille max de la chaine
 *
 */
void input(char* str, int sizeof_str);

/**
 * @brief demande un nom de fichier et rajoute l'extension
 *
 * @pre extension non NULL
 * @post retourne un char* qui est le nom_du_fichier_entrer_au_clavier.exension
 *
 * @param extension l'extension à ajouté
 * @return char* le nom + extension
 */
char* ask_fichier(char* extension);

/**
 * @brief demande un nom de fichier existant (sinon re-demande) et rajoute l'extension
 *
 * @pre extension non NULL
 * @post retourne un char* qui est le nom_du_fichier_entrer_au_clavier.exension
 *
 * @param extension l'extension à ajouté
 * @return char* le nom + extension
 */
char* ask_fichier_existant(char* extension);

/**
 * @brief retourne 1 ssi le ficher exister
 *
 * @pre aucune
 * @post retourne 1 ssi le ficher exister
 *
 * @param file_path le chemin jusqu'au fichier
 * @return int 1 ssi le ficher exister
 */
int file_exist(const char* file_path);

/**
 * @brief vide le tampon
 *
 * @pre tampon non vide sinon attend <Entrer>
 * @post le tampon est vide
 *
 */
void flush();

/**
 *
 * @pre aucune
 * @post retourne 1 ssi del est vide (supprimer)
 *
 */
int is_del(user u);

/**
 * @brief
 *
 * @pre dst et src non NULL
 * @post dst contient les caractère de src en minuscule
 *
 */
void strtolower(char* dst, char* src, int size);

/**
 * @brief surcouche à strcmp
 *
 * @pre s1 et s2 non NULL
 * @post retourn 0 si elles sont égale, un négatif si s1 < s2 et positf si s1 > s2. une chaine de caractère vide est toujours plus grande qu'une autre
 *
 */
int string_cmp(const char* p1, const char* p2);

/**
 * @brief surcharge de la fonction strstr qui ne prend pas en compte la casse
 * 
 * @pre needle non null
 * @post retourne 1 ssi "needle" est dans "haystack" sans prendre en compte la casse
 * 
 * @param haystack la chaine de caractère dans la quelle chercher
 * @param needle la sous chaine de caractère à chercher
 */
int stringstring(const char* haystack, const char* needle);

/**
 * @brief cherche le caractère "c" dans "s"
 * 
 * @post retourne un pointeur de char sur le prochain caractère "c" rencontrer dans la chaine de caractère s
 * @param s la chaine de caractère dans la quelle chercher
 * @param c le caractère à chercher (le code ascii)
 * @return char* 
 */
char* stringchr(const char* s, int c);

/**
 * @brief
 *
 * @pre aucune
 * @post retourne 1 ssi index est >= 0 et < size_max
 */
int is_in_tab(int index, int size_max);

#endif