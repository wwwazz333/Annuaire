#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "Save.h"
#include "Terminal.h"
#include "User.h"
#include "Verif.h"
#include "tableau.h"

#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <wchar.h>

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

int demande_menu_while(const char* demande, char proposition[][128], int nbr_proposition)
{
    int rep = -1;
    while (rep < 0 || rep > nbr_proposition) {
        setDefaultColor();
        printf(demande);
        printf("\n");
        int i = 0;
        while (i < nbr_proposition) {
            if (i % 2 == 0) {
                setColor(PINK);
            } else {
                setColor(PURPLE);
            }
            show_line_menu(proposition[i], &i);
            setDefaultColor();
            printf("\n");
        }

        print(">> ", ORANGE, DEFAULT_BACKGROUND_COLOR);
        setColor(AQUA);
        if (scanf("%d", &rep) != 1) {
            rep = -1;
        }
        flush();
        setDefaultColor();
    }
    return rep;
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
    setColor(RED);
    show_line_menu("Quitter\n", &i); // 0
    setColor(GREEN);
    show_line_menu("Charger ficher\n", &i); // 1
    show_line_menu("Sauvgarder fichier\n", &i); // 2
    setColor(BLUE);
    show_line_menu("Ajouter Client\n", &i); // 3
    show_line_menu("Supprimer Client\n", &i); // 4
    show_line_menu("Modifier Client\n", &i); // 5
    setColor(PINK);
    show_line_menu("Afficher Clients\n", &i); // 6
    show_line_menu("Rechercher\n", &i); // 7

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
    while (reponse != '0') {
        show_menu();
        print(">> ", ORANGE, DEFAULT_BACKGROUND_COLOR);
        setColor(AQUA);
        scanf("%c", &reponse);
        setDefaultColor();

        flush(); // vide stdin (au cas ou entrer plusieur caractère précédament)
        cls(); // clear le terminal
        switch (reponse) {
        case '1': // charger un fichier
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
                quick_sort_on(users, 0, nbr_utilisateur - 1, TRIE_PRENOM);
                triersur = TRIE_PRENOM;
                // print_tab(users, nbr_utilisateur);
            }
            break;
        case '2': // Sauvegarde du tableau
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
        case '3': // ajout d'utilisateur
            if (users_init) {
                show_menu_Title("ajout Client");
                user u = input_user();
                insert_user(&users, &nbr_utilisateur, u, triersur);
            } else {
                print("vous n'avez pas charger de fichier.\n", RED, DEFAULT_BACKGROUND_COLOR);
            }
            break;
        case '4': // suppression d'utilisateur
            if (users_init) {
                show_menu_Title("suppression Client");
                print("id : ", AQUA, DEFAULT_BACKGROUND_COLOR);
                int id_del = 0;
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
        case '5': // modifcation client
            if (users_init) {
                show_menu_Title("modification Client");
                print("id : ", AQUA, DEFAULT_BACKGROUND_COLOR);
                int id = 0;
                scanf("%d", &id);
                flush();
                if (modif_user(users, id - 1, nbr_utilisateur) == 0) { // -1 pour l'id car on commence à 0 dans le code

                    print("modification effectuer.\n", GREEN, DEFAULT_BACKGROUND_COLOR);
                } else {
                    print("erreur lors de la modification.\n", RED, DEFAULT_BACKGROUND_COLOR);
                }

            } else {
                print("vous n'avez pas charger de fichier.\n", RED, DEFAULT_BACKGROUND_COLOR);
            }
            break;
        case '6': // Affichage Clients
            if (users_init) {
                show_menu_Title("Affichage Clients");

                char proposition[][128] = { "annuler", "prenom", "nom", "ville", "code postal", "profession" };
                int rep = demande_menu_while("Sur quoi voulez vous trier :", proposition, sizeof(proposition) / (128 * sizeof(char)));
                TrierSur desir_trier_sur;
                switch (rep) {
                case 1:
                    desir_trier_sur = TRIE_PRENOM;
                    break;
                case 2:
                    desir_trier_sur = TRIE_NOM;
                    break;
                case 3:
                    desir_trier_sur = TRIE_VILLE;
                    break;
                case 4:
                    desir_trier_sur = TRIE_CODE_POSTAL;
                    break;
                case 5:
                    desir_trier_sur = TRIE_METIER;
                    break;
                default:
                    desir_trier_sur = TRIE_NULL;
                    break;
                }
                if (triersur != desir_trier_sur) {
                    quick_sort_on(users, 0, nbr_utilisateur - 1, desir_trier_sur);
                    triersur = desir_trier_sur;
                }
                if (rep != 0) {
                    print_tab(users, nbr_utilisateur);
                }
            } else {
                print("vous n'avez pas charger de fichier.\n", RED, DEFAULT_BACKGROUND_COLOR);
            }
            break;
        case '7': // Recherche
            if (users_init) {
                char proposition[][128] = { "Annuler", "Recherche de donnee", "Rechercher de donnee manquante" };
                int rep = demande_menu_while("Quelle recherche vouslez vous effectuer : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                if (rep == 1) {
                    char proposition_bis[][128] = { "annuler", "prenom", "nom", "ville", "code postal", "numero telephone", "email", "profession" };
                    rep = demande_menu_while("Sur quoi voulez vous rechercher : ", proposition_bis, sizeof(proposition_bis) / (128 * sizeof(char)));
                    TrierSur desir_rechercher_sur;
                    switch (rep) {
                    case 1:
                        desir_rechercher_sur = TRIE_PRENOM;
                        break;
                    case 2:
                        desir_rechercher_sur = TRIE_NOM;
                        break;
                    case 3:
                        desir_rechercher_sur = TRIE_VILLE;
                        break;
                    case 4:
                        desir_rechercher_sur = TRIE_CODE_POSTAL;
                        break;
                    case 5:
                        desir_rechercher_sur = TRIE_NO_TELEPHONE;
                        break;
                    case 6:
                        desir_rechercher_sur = TRIE_EMAIL;
                        break;
                    case 7:
                        desir_rechercher_sur = TRIE_METIER;
                        break;
                    default:
                        desir_rechercher_sur = TRIE_NULL;
                        break;
                    }
                    if (desir_rechercher_sur != TRIE_NULL) {
                        char* search_string = malloc(get_size_arg(desir_rechercher_sur) * sizeof(char));
                        print(">> ", AQUA, DEFAULT_BACKGROUND_COLOR);
                        input(search_string, get_size_arg(desir_rechercher_sur));

                        recherche_substring(users, nbr_utilisateur, search_string, desir_rechercher_sur);
                    }
                } else if (rep == 2) {
                    char proposition_bis[][128] = { "annuler", "prenom", "nom", "ville", "code postal", "numero telephone", "email", "profession", "tous" };
                    rep = demande_menu_while("Sur quoi voulez vous rechercher : ", proposition_bis, sizeof(proposition_bis) / (128 * sizeof(char)));
                    TrierSur donner_manquante_rechercher;
                    switch (rep) {
                    case 1:
                        donner_manquante_rechercher = TRIE_PRENOM;
                        break;
                    case 2:
                        donner_manquante_rechercher = TRIE_NOM;
                        break;
                    case 3:
                        donner_manquante_rechercher = TRIE_VILLE;
                        break;
                    case 4:
                        donner_manquante_rechercher = TRIE_CODE_POSTAL;
                        break;
                    case 5:
                        donner_manquante_rechercher = TRIE_NO_TELEPHONE;
                        break;
                    case 6:
                        donner_manquante_rechercher = TRIE_EMAIL;
                        break;
                    case 7:
                        donner_manquante_rechercher = TRIE_METIER;
                        break;
                    case 8:
                        donner_manquante_rechercher = TIRE_TOUS;
                        break;
                    default:
                        donner_manquante_rechercher = TRIE_NULL;
                        break;
                    }
                    if (donner_manquante_rechercher != TRIE_NULL) {
                        if (donner_manquante_rechercher == TIRE_TOUS) {
                            recherche_tous_manquante(users, nbr_utilisateur);
                        } else {
                            recherche_string_manquante(users, nbr_utilisateur, donner_manquante_rechercher);
                        }
                    }
                }

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