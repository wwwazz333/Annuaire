#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "ColorTerminal.h"
#include "Save.h"
#include "User.h"
#include "Verif.h"
#include "tableau.h"

#include <sys/time.h>
#include <time.h>
#include <string.h>

// TODO : quand trié ???
// TODO : tri oyalami
// TODO : strsep ???
// TODO : mettre tout en lower

/**
 * @brief efface tous dans le terminal (peut import l'OS)
 *
 * @pre aucune
 * @post le terminal est clear
 *
 */
void cls()
{
    // system("clear||cls");
}

/**
 * @brief affiche un Titre d'une séction
 *
 * @param Title chaine de charactère a afficher
 *
 * @pre aucune
 * @post affiche le Titre entré
 *
 */
void show_menu_Title(const char* Title)
{
    setDefaultColor();
    printf("\n\n");
    setBackgroundColor(WHITE);
    setColor(PINK);
    printf("-----------------%s-----------------", Title);
    setDefaultColor();
    printf("\n");
}

/**
 * @brief affiche une ligne d'un menu
 *
 * @param text text à afficher
 * @param i (ptr) l'index de la ligne
 *
 * @pre aucune
 * @post affiche une ligne d'un menu
 */
void show_line_menu(const char* text, int* i)
{
    printf("[%d] %s", (*i)++, text);
}
/**
 * @brief affiche les posibilité du menu
 *
 * @pre aucune
 * @post affiche les posibilité du menu
 */
void show_menu()
{
    int i = 0;
    setDefaultColor();
    show_menu_Title("Menu");
    setColor(GREEN);
    show_line_menu("Charger ficher\n", &i); // 0
    show_line_menu("Sauvgarder fichier\n", &i); // 1
    setColor(BLUE);
    show_line_menu("Ajouter Client\n", &i); // 2
    show_line_menu("Supprimer Client\n", &i); // 3
    setColor(PINK);
    show_line_menu("Afficher Clients\n", &i); // 4
    show_line_menu("Rechercher\n", &i); // 5
    setColor(RED);
    show_line_menu("Quitter\n", &i); // 6
    setDefaultColor();
}

/**
 * @brief affiche et gère le menu
 *
 * @pre aucune
 * @post affiche et gère le menu
 *
 * @return int 0 ssi aucune erreur (EXIT_SUCCESS)
 */
int menu()
{
    user* users;
    int users_init = 0; // 1 ssi un fichier à été charger
    FILE* fp;
    int nbr_utilisateur;
    char* nom_fichier;

    char reponse = '\0';
    while (reponse != '6') {
        show_menu();
        print(">> ", ORANGE, DEFAULT_BACKGROUND_COLOR);
        setColor(AQUA);
        scanf("%c", &reponse);
        setDefaultColor();

        flush(); // vide stdin (au cas ou entrer plusieur caractère précédament)
        cls(); // clear le terminal
        switch (reponse) {
        case '0': // charger un fichier
            show_menu_Title("Charger fichier");
            nom_fichier = ask_fichier_existant("csv");
            fp = fopen(nom_fichier, "r");
            free(nom_fichier);
            if (fp == NULL) {
                print("Le fichier n'a pas pu etre ouvert.\n", RED, DEFAULT_BACKGROUND_COLOR);
            } else {
                nbr_utilisateur = nombre_utilisateurs(fp);
                users = malloc(nbr_utilisateur * sizeof(user));
                load(fp, users, nbr_utilisateur);
                users_init = 1;
                print("Le fichier est charger.\n", GREEN, DEFAULT_BACKGROUND_COLOR);
                fclose(fp);

                quick_sort(users, 0, nbr_utilisateur - 1);
            }
            break;
        case '1': // Sauvegarde du tableau
            show_menu_Title("Sauvegarde fichier");
            if (users_init) {
                nom_fichier = ask_fichier("csv");
                fp = fopen(nom_fichier, "w");
                free(nom_fichier);
                if (fp == NULL) {
                    print("Le fichier n'a pas pu etre enregister.\n", RED, DEFAULT_BACKGROUND_COLOR);
                } else {
                    save(fp, users, nbr_utilisateur);
                    print("Le fichier est sauvgarder.\n", GREEN, DEFAULT_BACKGROUND_COLOR);
                    fclose(fp);
                }
            } else {
                print("vous n'avez pas charger de fichier.\n", RED, DEFAULT_BACKGROUND_COLOR);
            }
            break;
        case '2': // ajout d'utilisateur
            if (users_init) {
                show_menu_Title("ajout Client");
                user u = input_user();
                insert_user(&users, &nbr_utilisateur, u);
            } else {
                print("vous n'avez pas charger de fichier.\n", RED, DEFAULT_BACKGROUND_COLOR);
            }
            break;
        case '3': // suppression d'utilisateur
            if (users_init) {
                show_menu_Title("suppression Client");
                print("id : ", AQUA, DEFAULT_BACKGROUND_COLOR);
                int id_del;
                scanf("%d", &id_del);
                flush();
                if (del_user(users, id_del-1, nbr_utilisateur) == 0) {

                    print("suppression effectuer.\n", GREEN, DEFAULT_BACKGROUND_COLOR);
                }else{
                    print("erreur lors de la suppression.\n", RED, DEFAULT_BACKGROUND_COLOR);
                }

            } else {
                print("vous n'avez pas charger de fichier.\n", RED, DEFAULT_BACKGROUND_COLOR);
            }
            break;
        case '4': // Affichage Clients
            if (users_init) {
                show_menu_Title("Affichage Clients");
                int i;
                for (i = 0; i < nbr_utilisateur; i++) {
                    if (i % 2 == 0) {
                        setColor(PURPLE);
                    } else {
                        setColor(WHITE);
                    }
                    printf("[%d] %s, %s, %s, %s, %s, %s, %s", i + 1, users[i].nom, users[i].prenom, users[i].ville, users[i].code_postal, users[i].no_telephone, users[i].email, users[i].metier);
                    setDefaultColor();
                    printf("\n");
                }
            } else {
                print("vous n'avez pas charger de fichier.\n", RED, DEFAULT_BACKGROUND_COLOR);
            }
            break;
        case '5': // Recherche
            if (users_init) {
                char nn[64];
                print("nom : ", AQUA, DEFAULT_BACKGROUND_COLOR);
                input(nn, 64);
                
                int tai;
                user* substing_matches = malloc(nbr_utilisateur * sizeof(user));
                int* key_matches = malloc(nbr_utilisateur * sizeof(user));
                recherche_substring(users, substing_matches, key_matches, nbr_utilisateur, nn, &tai);
                for (int i = 0; i < tai; i++) {
                    if (i % 2 == 0) {
                        setColor(PURPLE);
                    } else {
                        setColor(WHITE);
                    }
                    printf("[%d] %s, %s, %s, %s, %s, %s, %s", key_matches[i] + 1, substing_matches[i].nom, substing_matches[i].prenom, substing_matches[i].ville, substing_matches[i].code_postal, substing_matches[i].no_telephone, substing_matches[i].email, substing_matches[i].metier);
                    setDefaultColor();
                    printf("\n");
                }

                free(substing_matches);
                free(key_matches);

            } else {
                print("vous n'avez pas charger de fichier.\n", RED, DEFAULT_BACKGROUND_COLOR);
            }
            break;
        default:
            break;
        }
    }
    if (users_init) {
        free(users);
    }

    print("exit\n", RED, DEFAULT_BACKGROUND_COLOR);
    return EXIT_SUCCESS;
}

int main()
{
    
    return menu();
}