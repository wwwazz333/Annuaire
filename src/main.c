#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "ColorTerminal.h"
#include "Save.h"
#include "User.h"
#include "Verif.h"
#include "tableau.h"

#include <string.h>
#include <sys/time.h>
#include <time.h>

// TODO : quand trié ???
// TODO : tri oyalami
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
    int users_init = 0; // 1 ssi un fichier à été charger.
    FILE* fp;
    int nbr_utilisateur;
    char* nom_fichier;
    TrierSur triersur = TRIE_NULL;

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


				// oyelami(users, nbr_utilisateur-1, TRIE_PRENOM);
				// print_tab(users, nbr_utilisateur);
                quick_sort_on(users, 0, nbr_utilisateur - 1, TRIE_NOM);
                triersur = TRIE_PRENOM;
				// print_tab(users, nbr_utilisateur);
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
                if (del_user(users, id_del - 1, nbr_utilisateur) == 0) {

                    print("suppression effectuer.\n", GREEN, DEFAULT_BACKGROUND_COLOR);
                } else {
                    print("erreur lors de la suppression.\n", RED, DEFAULT_BACKGROUND_COLOR);
                }

            } else {
                print("vous n'avez pas charger de fichier.\n", RED, DEFAULT_BACKGROUND_COLOR);
            }
            break;
        case '4': // Affichage Clients
            if (users_init) {
                show_menu_Title("Affichage Clients");
                int rep = -1;
                while (rep < 0 || rep > 4) {
                    setDefaultColor();
                    printf("Sur quoi voulez vous trier :\n");
                    int i = 0;
                    show_line_menu("annuler\n", &i);
                    show_line_menu("prenom\n", &i);
                    show_line_menu("nom\n", &i);
                    show_line_menu("code postal\n", &i);
                    show_line_menu("profession\n", &i);

                    print(">> ", ORANGE, DEFAULT_BACKGROUND_COLOR);
                    setColor(AQUA);
                    if (scanf("%d", &rep) != 1) {
                        rep = -1;
                    }
                    flush();
                    setDefaultColor();
                }

                switch (rep) {
                case 1:
					if (triersur != TRIE_PRENOM) {
                        quick_sort_on(users, 0, nbr_utilisateur - 1, TRIE_PRENOM);
                        triersur = TRIE_PRENOM;
                    }
                    break;
                case 2:
                    if (triersur != TRIE_NOM) {
                        quick_sort_on(users, 0, nbr_utilisateur - 1, TRIE_NOM);
                        triersur = TRIE_NOM;
                    }
                    break;
                case 3:
                    if (triersur != TRIE_CODE_POSTAL) {
                        quick_sort_on(users, 0, nbr_utilisateur - 1, TRIE_CODE_POSTAL);
                        triersur = TRIE_CODE_POSTAL;
                    }
                    break;
                case 4:
                    if (triersur != TRIE_METIER) {
                        quick_sort_on(users, 0, nbr_utilisateur - 1, TRIE_METIER);
                        triersur = TRIE_METIER;
                    }
                    break;
                default:
                    break;
                }
                if (rep != 0) {
                    print_tab(users, nbr_utilisateur);
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

                recherche_substring(users, nbr_utilisateur, nn);

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