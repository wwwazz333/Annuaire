#ifndef _SAVE_H_
#define _SAVE_H_
#include "User.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO : verifier si ouvert dans le bon mode ??????? (r, w)


/**
 * @brief lit le fichier fp et met les caractère dans str jusqu'à renctonrer le char "fin"
 * 
 * @pre fp ouvert en mode lecture et qu'il y est bien le caractère de fin dans la partie du fichier que l'on va lire
 * @post retourne EOF si on est a la fin du fichier et str contien tous les caractère (à partir de l'emplacement de départ) jusqu'au caractère fin (éxclu)
 * 
 * @param fp le fichier
 * @param str la chaine ou l'on place les caractère
 * @param taille_str la taille de str (pour ne pas écrire si il n'y a plus d'emplacement de libre)
 * @param fin le caractère de fin
 * @return int : EOF si on est a la fin du fichier et 0 sinon
 */
int readUntil(FILE* fp, char* str, int taille_str, char fin);

/**
 * @brief lit une ligne du fichier fp (à partire de l'emplacemenet du curseur) et place les information dans l'user u
 * 
 * @pre fp ouvert en mode lecture!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * @post retourne EOF si on est a la fin du fichier et u contient les information lu dans fp
 * 
 * @param fp le fichier
 * @param u l'user où vont être enregistrer les informations
 * @return int : EOF si on est a la fin du fichier et 0 sinon 
 */
int readUser(FILE* fp, user* u);

int load(FILE* fp, user* users, int nombre_user);

/**
 * @brief écrit un user dans fp a l'endroit où est le curseur
 * 
 * @pre fp ouvert en mode écriture
 * @post écrit u dans fp retourne 0 si tout c'est bien dérouler
 * 
 * @param fp le fichier
 * @param u l'user que l'on veut enregistrer
 * @return int 0 ssi pas d'erreur 
 */
int writeUser(FILE* fp, user* u);
/**
 * @brief 
 * 
 * @param fp 
 * @param users 
 * @param nombre_user 
 * @return int 
 */
int save(FILE* fp, user* users, int nombre_user);
/**
 * @brief retourne le nombre d'utilisateur
 * 
 * @pre fp ouvert en mode lecture
 * @post le nombre retourné est le nombre d'utilisateur valide
 * 
 * @param fp le fichier
 * @return int nombre d'utilisateur valide dans fp
 */
int nombre_utilisateurs(FILE* fp);

#endif