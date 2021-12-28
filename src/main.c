#include <stdio.h>
#include <stdlib.h>

#include "Save.h"
#include "Terminal.h"
#include "User.h"
#include "Verif.h"
#include "gremlins.h"
#include "tableau.h"

/**
 * @brief efface tous dans le terminal (peut import l'OS)
 *
 * @pre aucune
 * @post le terminal est clear
 *
 */
void cls()
{
    system("clear||cls");
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
 * @pre demande non NULL
 * @post retourne la réponse (int) entrer au clavier parmis les propositions
 *
 */
int demande_menu_while(const char* demande, char proposition[][128], int nbr_proposition)
{
    int rep = -1;
    while (rep < 0 || rep >= nbr_proposition) {
        setDefaultColor();
        setColor(YELLOW);
        printf(demande);
        printf("\n");
        int i = 0;
        while (i < nbr_proposition) {
            if (i == 0) {
                setColor(RED);
            } else if (i % 2 == 0) {
                setColor(PINK);
            } else {
                setColor(BLUE);
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
    show_line_menu("Fonctions Recherche\n", &i); // 7

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
    TrierSur triersur;
    triersur = TRIE_NULL;

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

                quick_sort(users, 0, nbr_utilisateur - 1, TRIE_PRENOM);
                triersur = TRIE_PRENOM;
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
            show_menu_Title("ajout Client");
            if (users_init) {
                user u = input_user();
                setColor(PURPLE);
                print_user(u, -1);
                setDefaultColor();
                printf("\n");
                char proposition[][128] = { "annuler", "ajouter" };
                int rep = demande_menu_while("Voulez vous vraiment l'ajouter : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                if (rep == 1) {
                    // if (triersur == TRIE_NULL) {
                    //     oyelami(users, nbr_utilisateur - 1, TRIE_PRENOM);
                    //     triersur = TRIE_PRENOM;
                    // }
                    if (insert_user(&users, &nbr_utilisateur, u, triersur) == EXIT_SUCCESS) {
                        print("client ajouter\n", GREEN, DEFAULT_BACKGROUND_COLOR);
                    }
                } else {
                    print("action annuler\n", RED, DEFAULT_BACKGROUND_COLOR);
                }
            } else {
                print("vous n'avez pas charger de fichier.\n", RED, DEFAULT_BACKGROUND_COLOR);
            }
            break;
        case '4': // suppression d'utilisateur
            show_menu_Title("suppression Client");
            if (users_init) {
                print("id utilisateur: ", YELLOW, DEFAULT_BACKGROUND_COLOR);
                int id_del = 0;
                setColor(AQUA);
                scanf("%d", &id_del);
                setDefaultColor();
                flush();
                if (!is_in_tab(id_del - 1, nbr_utilisateur)) {
                    print("l'id n'est pas dans le tableau\n", RED, DEFAULT_BACKGROUND_COLOR);
                    break;
                }
                print_user(users[id_del - 1], id_del - 1);
                printf("\n");
                char proposition[][128] = { "annuler", "supprimer" };
                int rep = demande_menu_while("Voulez vous vraiment le suprimer : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                if (rep == 1) {
                    if (del_user(users, id_del - 1, nbr_utilisateur) == 0) {
                        oyelami(users, nbr_utilisateur - 1, triersur); // re trie le tableau
                        print("suppression effectuer.\n", GREEN, DEFAULT_BACKGROUND_COLOR);
                    } else {
                        print("erreur lors de la suppression.\n", RED, DEFAULT_BACKGROUND_COLOR);
                    }
                } else {
                    print("action annulee\n", RED, DEFAULT_BACKGROUND_COLOR);
                }
            } else {
                print("vous n'avez pas charger de fichier.\n", RED, DEFAULT_BACKGROUND_COLOR);
            }
            break;
        case '5': // modifcation client
            show_menu_Title("modification Client");
            if (users_init) {
                print("id utilisateur: ", YELLOW, DEFAULT_BACKGROUND_COLOR);
                int id = 0;
                setColor(AQUA);
                scanf("%d", &id);
                setDefaultColor();
                flush();
                if (!is_in_tab(id - 1, nbr_utilisateur)) {
                    print("l'id n'est pas dans le tableau\n", RED, DEFAULT_BACKGROUND_COLOR);
                    break;
                }
                print_user(users[id - 1], id - 1);
                printf("\n");
                char proposition[][128] = { "annuler", "modifier" };
                int rep = demande_menu_while("voulez vous modifier celui-ci ? : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                if (rep == 1) {
                    if (modif_user(users, id - 1, nbr_utilisateur) == 0) { // -1 pour l'id car on commence à 0 dans le code
                        oyelami(users, nbr_utilisateur - 1, triersur); // re trie le tableau
                        print("modification effectuer.\n", GREEN, DEFAULT_BACKGROUND_COLOR);
                    } else {
                        print("erreur lors de la modification.\n", RED, DEFAULT_BACKGROUND_COLOR);
                    }
                } else {
                    print("action annulee\n", RED, DEFAULT_BACKGROUND_COLOR);
                }
            } else {
                print("vous n'avez pas charger de fichier.\n", RED, DEFAULT_BACKGROUND_COLOR);
            }
            break;
        case '6': // Affichage Clients
            show_menu_Title("Affichage Clients");
            if (users_init) {
                char proposition[][128] = { "annuler", "Affichage complet", "Affichage sectionner" };
                int rep = demande_menu_while("Quelle methode d'affichage choississez vous: ", proposition, sizeof(proposition) / (128 * sizeof(char)));

                char proposition_bis[][128] = { "annuler", "prenom", "nom", "ville", "code postal", "profession" };
                int rep_bis = demande_menu_while("Sur quoi voulez vous trier :", proposition_bis, sizeof(proposition_bis) / (128 * sizeof(char)));
                if (rep_bis != 0) {
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
                    if (desir_trier_sur != TRIE_NULL) {
                        if (triersur != desir_trier_sur) {
                            quick_sort(users, 0, nbr_utilisateur - 1, desir_trier_sur);
                            triersur = desir_trier_sur;
                        }

                        if (rep==1) {
                            print_tab(users, nbr_utilisateur);
                        }
                        else if (rep==2) {
                            print_tab_sect(users, nbr_utilisateur, 500);
                        }
                    }
                }
            } else {
                print("vous n'avez pas charger de fichier.\n", RED, DEFAULT_BACKGROUND_COLOR);
            }
            break;
        case '7': // Recherche
            show_menu_Title("Fonctions Recherche");
            if (users_init) {
                char proposition[][128] = {
                    "Annuler", "Recherche de donnee", "Recherche de donnee qui commence par ...", "Rechercher de donnee manquante", "Recherche par identifiant"
                };
                int rep = demande_menu_while("Quelle recherche vouslez vous effectuer : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                if (rep == 0) {
                    break;
                } else if (rep == 4) {
                    print("id utilisateur: ", YELLOW, DEFAULT_BACKGROUND_COLOR);
                    int id = 0;
                    setColor(AQUA);
                    scanf("%d", &id);
                    setDefaultColor();
                    flush();
                    if (!is_in_tab(id - 1, nbr_utilisateur)) {
                        print("l'id n'est pas dans le tableau\n", RED, DEFAULT_BACKGROUND_COLOR);
                    } else {
                        print_user(users[id - 1], id - 1);
                        printf("\n");
                    }
                    break;
                }

                char proposition_bis[][128] = { "annuler", "prenom", "nom", "ville", "code postal", "numero telephone", "email", "profession", "tous" };
                int sous_rep = demande_menu_while("Sur quoi voulez vous rechercher : ",
                    proposition_bis,
                    (sizeof(proposition_bis) / (128 * sizeof(char))) - ((rep < 3) ? 1 : 0)); // si Recherche donné alors pas afficher "tous"

                TrierSur desir_rechercher_sur;
                switch (sous_rep) {
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
                case 8:
                    desir_rechercher_sur = TIRE_TOUS;
                    break;
                default:
                    desir_rechercher_sur = TRIE_NULL;
                    break;
                }

                if (rep == 1 || rep == 2) {

                    if (desir_rechercher_sur != TRIE_NULL) {

                        char* search_string = malloc(get_size_arg(desir_rechercher_sur) * sizeof(char));
                        print("Votre recherche: ", PINK, DEFAULT_BACKGROUND_COLOR);
                        print(">> ", AQUA, DEFAULT_BACKGROUND_COLOR);
                        input(search_string, get_size_arg(desir_rechercher_sur));

                        if (rep == 1) {
                            recherche_substring(users, nbr_utilisateur, search_string, desir_rechercher_sur);
                        } else {
                            recherche_string(users, nbr_utilisateur, search_string, desir_rechercher_sur);
                        }
                    }
                } else if (rep == 3) {
                    if (desir_rechercher_sur != TRIE_NULL) {
                        if (desir_rechercher_sur == TIRE_TOUS) {
                            recherche_tous_manquante(users, nbr_utilisateur);
                        } else {
                            recherche_element_manquant(users, nbr_utilisateur, desir_rechercher_sur);
                        }
                    }
                }
            } else {
                print("vous n'avez pas charger de fichier.\n", RED, DEFAULT_BACKGROUND_COLOR);
            }
            break;
        case '$':
            show_menu_Title("Easter Egg - Gremlins");
            show_gremlins();
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
