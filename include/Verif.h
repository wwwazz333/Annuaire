#ifndef _VERIF_H_
#define _VERIF_H_

#include "User.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "ColorTerminal.h"


/**
 * @brief récuper les caractère entrer et les place dans str
 *
 * @pre aucune
 * @post str contient les caractère taper (sans '\n' mais avec '\0')
 * 
 * @param str la chaine a modifier
 * @param sizeof_str la taille max de la chaine
 *
 */
void input(char* str, int sizeof_str);

/**
 * @brief demande un nom de fichier et rajoute l'extension
 * 
 * @pre aucune
 * @post retourne un char* qui est le nom_du_fichier_entrer_au_clavier.exension
 * 
 * @param extension l'extension à ajouté
 * @return char* le nom + extension
 */
char* ask_fichier(char* extension);

/**
 * @brief demande un nom de fichier existant (sinon re-demande) et rajoute l'extension
 * 
 * @pre aucune
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
 * @brief 
 * 
 * @pre aucune
 * @post retourne 1 ssi del est vide (supprimer)
 * 
 * @param u 
 * @return int 
 */
int is_del(user u);

void strtolower(char* dst, char* src, int size);

#endif