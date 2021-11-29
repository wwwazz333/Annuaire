#include <stdio.h>
#include <stdlib.h>

#include "ColorTerminal.h"
#include "Save.h"
#include "User.h"
#include "Verif.h"
#include "tableau.h"

#include <sys/time.h>
#include <time.h>

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
    int users_init = 0;
    FILE* fp;
    int nbr_utilisateur;

    char reponse = '\0';
    while (reponse != '6') {
        show_menu();
        setColor(ORANGE);
        printf(">> ");
        setColor(AQUA);
        scanf("%c", &reponse);
        setDefaultColor();
        // while ((reponse = getc(stdin)) == '\n') { }; // passe les '\n' inutile
        flush(); // vide stdin (au cas ou entrer plusieur caractère précédament)
        cls();
        switch (reponse) {
        case '0': // charger un fichier
            show_menu_Title("Charger fichier");
            fp = fopen(ask_fichier_existant("csv"), "r");
            if (fp == NULL) {
                setColor(RED);
                printf("Le fichier n'a pas pu etre ouvert.\n");
                setDefaultColor();
            } else {
                nbr_utilisateur = nombre_utilisateurs(fp);
                users = malloc(nbr_utilisateur * sizeof(user));
                load(fp, users, nbr_utilisateur);
                users_init = 1;
                setColor(GREEN);
                printf("Le fichier est charger.\n");
                setDefaultColor();
                fclose(fp);

                quick_sort(users, 0, nbr_utilisateur - 1);
            }
            break;
        case '1': // Sauvegarde du tableau
            show_menu_Title("Sauvegarde fichier");
            fp = fopen(ask_fichier("csv"), "w");
            if (fp == NULL) {
                setColor(RED);
                printf("Le fichier n'a pas pu etre ouvert.\n");
                setDefaultColor();
            } else {
                oyelami(users,nbr_utilisateur-1, 4);
                save(fp, users, nbr_utilisateur);
                setColor(GREEN);
                printf("Le fichier est sauvgarder.\n");
                setDefaultColor();
                fclose(fp);
            }
            break;
        case '2': // ajout d'utilisateur
            show_menu_Title("ajout Client");
            user u = input_user();
            insert_user(&users, &nbr_utilisateur, u);
            break;
        case '3': // suppression d'utilisateur
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
            }
            break;
        case '5': // Recherche
            break;
        default:
            break;
        }
    }
    if (users_init) {
        free(users);
    }

    setColor(RED);
    printf("exit\n");
    setDefaultColor();
    return EXIT_SUCCESS;
}
int main()
{
    return menu();
}