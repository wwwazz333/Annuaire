#include <stdio.h>
#include <stdlib.h>

#include "ColorTerminal.h"
#include "Save.h"
#include "User.h"
#include "Verif.h"

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
    printf("\n-----------------%s-----------------\n", Title);
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
    show_menu_Title("Menu");
    show_line_menu("Charger ficher\n", &i);
    show_line_menu("Sauvgarder fichier\n", &i);
    show_line_menu("Afficher Clients\n", &i);
    show_line_menu("Ajouter Client\n", &i);
    show_line_menu("Supprimer Client\n", &i);
    show_line_menu("Rechercher\n", &i);
    show_line_menu("Quiter\n", &i);
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
        printf(">> ");
        scanf("%c", &reponse);
        // while ((reponse = getc(stdin)) == '\n') { }; // passe les '\n' inutile
        flush(); // vide stdin (au cas ou entrer plusieur caractère précédament)
        cls();
        switch (reponse) {
        case '0':
            show_menu_Title("Charger fichier");
            fp = fopen(ask_fichier_existant("csv"), "r");
            if (fp == NULL) {
                printf("Le fichier n'a pas pu etre ouvert.\n");
            } else {
                nbr_utilisateur = nombre_utilisateurs(fp);
                users = malloc(nbr_utilisateur * sizeof(user));
                load(fp, users, nbr_utilisateur);
                users_init = 1;
                printf("Le fichier est charger.\n");
                fclose(fp);
            }
            // tri_vide(users, 5, nbr_utilisateur);
            break;
        case '1':
            show_menu_Title("Sauvgarde fichier");
            fp = fopen(ask_fichier("csv"), "w");
            if (fp == NULL) {
                printf("Le fichier n'a pas pu etre ouvert.\n");
            } else {

                save(fp, users, nbr_utilisateur);
                printf("Le fichier est sauvgarder.\n");
                fclose(fp);
            }
            break;
        case '2':
            if (users_init) {
                show_menu_Title("Affichage Clients");
                for (int i = 0; i < nbr_utilisateur; i++) {
                    if (i % 2 == 0) {
                        setColor(YELLOW);
                    } else {
                        setColor(WHITE);
                    }
                    printf("[%d] %s, %s, %s, %s, %s, %s, %s", i + 1, users[i].nom, users[i].prenom, users[i].ville, users[i].code_postal, users[i].no_telephone, users[i].email, users[i].metier);
                    setDefaultColor();
                    printf("\n");
                }
            }
            break;

        default:
            break;
        }
    }

    if (users_init) {
        free(users);
    }

    printf("exit\n");
    return EXIT_SUCCESS;
}
int main()
{
    setColor(RED);
    printf("bonjour\n");
    setColor(GREEN);
    printf("bonjour\n");
    setColor(BLUE);
    printf("bonjour\n");
    setColor(BLACK);
    printf("bonjour\n");
    setDefaultColor();
    printf("fin\n");
    return 0;
}