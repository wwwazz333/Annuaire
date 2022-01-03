#ifndef _SAVE_H_
#define _SAVE_H_
#include "User.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX_LIGNE 537

/**
 * @brief lit le fichier "fp" et met les caractères dans "dst" jusqu'à rencontrer le caractère "fin"
 * 
 * @pre "fp" ouvert en mode lecture et qu'il y est bien le caractère de fin dans la partie du fichier que l'on va lire
 * @post "dst" contient tous les caractères (à partir de l'emplacement de départ) jusqu'au caractère fin (éxclu), s'il y a assez de place sinon coupe la chaine et retourne un pointeur sur le prochain caractère après le char "fin"
 * 
 * @param fp le fichier
 * @param dst la chaine où l'on place les caractères
 * @param taille_max_dst la taille maximum de dst (pour ne pas écrire s'il n'y a plus d'emplacement de libre)
 * @param fin le caractère de fin
 * 
 * @return char* : retourne un pointeur qui pointe sur le caractère juste après le caractère de fin (soit le début du mot)
 */
char* readUntil(char* depart, char* dst, int taille_max_dst, char fin);

/**
 * @brief lit une ligne du fichier "fp" (à partir de l'emplacemenet du curseur) et place les informations dans l'utilisateur u
 * 
 * @pre "fp" ouvert en mode lecture
 * @post retourne EOF ssi on est a la fin du fichier et u contient les informations lu dans fp (une ligne)
 * 
 * @param fp le fichier
 * @param u l'user où vont être enregistrer les informations
 * 
 * @return int : EOF si on est à la fin du fichier et 0 sinon 
 */
int readUser(FILE* fp, user* u);

/**
 * @brief charge le fichier "fp"
 * 
 * @pre fp ouvert en mode lecture
 * @post users contien les user de fp et retourne si erreur ou non
 * 
 * @param fp le fichier
 * @param tab le tableau d'utilisateurs
 * 
 * @return retourne EXIT_FAILURE si il y a une erreur dans le chargement, sinon EXIT_SUCCESS
 */
int load(FILE* fp, user tab[]);

/**
 * @brief écrit un "user" dans "fp" à l'endroit où est le curseur
 * 
 * @pre fp ouvert en mode écriture
 * @post écrit "u" dans "fp" et retourne "0" s'il n'y a pas d'erreur
 * 
 * @param fp le fichier
 * @param u l'utilisateur que l'on veut enregistrer
 * 
 * @return retourne "0" ssi pas d'erreur 
 */
int writeUser(FILE* fp, user* u);

/**
 * @brief sauvgarde users dans le fichier fp
 * 
 * @pre fp ouvert en mode écriture
 * @post users save dans fp
 * 
 * @param fp le fichier
 * @param tab le tableau d'utilisateurs
 * @param nombre_users nombre d'utilisateurs à sauvegarder
 */
void save(FILE* fp, user tab[], int nombre_users);

/**
 * @brief retourne le nombre d'utilisateurs
 * 
 * @pre fp ouvert en mode lecture
 * @post le nombre retourné est le nombre d'utilisateurs valide
 * 
 * @param fp le fichier
 * 
 * @return int nombre d'utilisateurs valide dans fp
 */
int nombre_utilisateurs(FILE* fp);

#endif