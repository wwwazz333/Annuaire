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
 * @brief affiche un Titre d'une section
 *
 * @param Title chaine de character a afficher
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

        print(ORANGE, DEFAULT_BACKGROUND_COLOR, ">> ");
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
 * @brief affiche les possibilité du menu
 *
 * @pre aucune
 * @post affiche les possibilité du menu
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
    show_line_menu("Sauvegarder fichier\n", &i); // 2
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
        print(ORANGE, DEFAULT_BACKGROUND_COLOR, ">> ");
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
                print(RED, DEFAULT_BACKGROUND_COLOR, "Le fichier n'a pas pu etre ouvert.\n");
            } else {
                nbr_utilisateur = nombre_utilisateurs(fp);
                users = malloc(nbr_utilisateur * sizeof(user));
                load(fp, users, nbr_utilisateur);
                users_init = 1;
                print(GREEN, DEFAULT_BACKGROUND_COLOR, "Le fichier est charger.\n");
                fclose(fp);

                quick_sort(users, 0, nbr_utilisateur - 1, TRIE_PRENOM);
                triersur = TRIE_PRENOM;
            }
            break;
        case '2': // Sauvegarde du tableau
            show_menu_Title("Sauvegarde fichier");
            if (users_init) {
                nom_fichier = ask_fichier("csv");
                setColor(GREEN);
                printf("%d utilisateur(s) a sauvegarder.\n", nbr_utilisateur);
                setDefaultColor();
                char proposition[][128] = { "annuler", "sauvegarder" };
                int rep = demande_menu_while("voulez vous vraiment sauvegarder ? : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                if (rep==1) {
                    fp = fopen(nom_fichier, "w");
                    free(nom_fichier);
                }
                if (fp == NULL) {
                    print(RED, DEFAULT_BACKGROUND_COLOR, "Le fichier n'a pas pu etre enregister.\n");
                } else {
                    save(fp, users, nbr_utilisateur);
                    print(GREEN, DEFAULT_BACKGROUND_COLOR, "Le fichier est sauvgarder.\n");
                    fclose(fp);
                }
            } else {
                print(RED, DEFAULT_BACKGROUND_COLOR, "vous n'avez pas charger de fichier.\n");
            }
            break;
        case '3': // ajout d'utilisateur
            show_menu_Title("ajout Client");
            if (users_init) {
                user u = input_user();
                setColor(PURPLE);
                print_user(u, -1);
                setDefaultColor();
                char proposition[][128] = { "annuler", "ajouter" };
                int rep = demande_menu_while("Voulez vous vraiment l'ajouter : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                if (rep == 1) {
                    if (insert_user(&users, &nbr_utilisateur, u, triersur) == EXIT_SUCCESS) {
                        print(GREEN, DEFAULT_BACKGROUND_COLOR, "client ajouter\n");
                    }
                } else {
                    print(RED, DEFAULT_BACKGROUND_COLOR, "action annuler\n");
                }
            } else {
                print(RED, DEFAULT_BACKGROUND_COLOR, "vous n'avez pas charger de fichier.\n");
            }
            break;
        case '4': // suppression d'utilisateur
            show_menu_Title("suppression Client");
            if (users_init) {
                print(YELLOW, DEFAULT_BACKGROUND_COLOR, "id utilisateur: ");
                int id_del = 0;
                setColor(AQUA);
                scanf("%d", &id_del);
                setDefaultColor();
                flush();
                if (!is_in_tab(id_del - 1, nbr_utilisateur)) {
                    print(RED, DEFAULT_BACKGROUND_COLOR, "l'id n'est pas dans le tableau\n");
                    break;
                }
                print_user(users[id_del - 1], id_del - 1);
                char proposition[][128] = { "annuler", "supprimer" };
                int rep = demande_menu_while("Voulez vous vraiment le supprimer : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                if (rep == 1) {
                    if (del_user(users, id_del - 1, nbr_utilisateur) == 0) {
                        oyelami(users, nbr_utilisateur - 1, triersur); // re trie le tableau
                        print(GREEN, DEFAULT_BACKGROUND_COLOR, "suppression effectuer.\n");
                    } else {
                        print(RED, DEFAULT_BACKGROUND_COLOR, "erreur lors de la suppression.\n");
                    }
                } else {
                    print(RED, DEFAULT_BACKGROUND_COLOR, "action annulee\n");
                }
            } else {
                print(RED, DEFAULT_BACKGROUND_COLOR, "vous n'avez pas charger de fichier.\n");
            }
            break;
        case '5': // modifcation client
            show_menu_Title("modification Client");
            if (users_init) {
                print(YELLOW, DEFAULT_BACKGROUND_COLOR, "id utilisateur: ");
                int id = 0;
                setColor(AQUA);
                scanf("%d", &id);
                id--;
                setDefaultColor();
                flush();
                if (!is_in_tab(id - 1, nbr_utilisateur)) {
                    print(RED, DEFAULT_BACKGROUND_COLOR, "l'id n'est pas dans le tableau\n");
                    break;
                }
                print_user(users[id], id);

                char proposition[][128] = { "annuler", "modifier" };
                int rep = demande_menu_while("voulez vous modifier celui-ci ? : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                if (rep == 1) {
                    user temp;
                    usercpy(&temp, &users[id]);
                    modif_user(&temp);
                    print_user(temp, id);

                    rep = demande_menu_while("voulez vous modifier l'utilisateur par celui-ci ? : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                    if (rep == 1) {
                        usercpy(&users[id], &temp);
                        oyelami(users, nbr_utilisateur - 1, triersur); // re trie le tableau
                        print(GREEN, DEFAULT_BACKGROUND_COLOR, "modification effectuer.\n");
                    } else {
                        print(RED, DEFAULT_BACKGROUND_COLOR, "erreur lors de la modification.\n");
                    }
                } else {
                    print(RED, DEFAULT_BACKGROUND_COLOR, "action annulee\n");
                }
            } else {
                print(RED, DEFAULT_BACKGROUND_COLOR, "vous n'avez pas charger de fichier.\n");
            }
            break;
        case '6': // Affichage Clients
            show_menu_Title("Affichage Clients");
            if (users_init) {
                char proposition[][128] = { "annuler", "Affichage complet", "Affichage sectionner" };
                int rep = demande_menu_while("Quelle methode d'affichage choisissez vous: ", proposition, sizeof(proposition) / (128 * sizeof(char)));

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

                        if (rep == 1) {
                            print_tab(users, nbr_utilisateur);
                        } else if (rep == 2) {
                            print_tab_sect(users, nbr_utilisateur, 500);
                        }
                    }
                }
            } else {
                print(RED, DEFAULT_BACKGROUND_COLOR, "vous n'avez pas charger de fichier.\n");
            }
            break;
        case '7': // Recherche
            show_menu_Title("Fonctions Recherche");
            if (users_init) {
                char proposition[][128] = {
                    "Annuler", "Recherche de donnee", "Recherche de donnee qui commence par ...", "Recherche de donnee exacte", "Rechercher de donnee manquante", "Recherche par identifiant"
                };
                int rep = demande_menu_while("Quelle recherche voulez vous effectuer : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                if (rep == 0) {
                    break;
                } else if (rep == 4) {
                    print(YELLOW, DEFAULT_BACKGROUND_COLOR, "id utilisateur: ");
                    int id = 0;
                    setColor(AQUA);
                    scanf("%d", &id);
                    setDefaultColor();
                    flush();
                    if (!is_in_tab(id - 1, nbr_utilisateur)) {
                        print(RED, DEFAULT_BACKGROUND_COLOR, "l'id n'est pas dans le tableau\n");
                    } else {
                        print_user(users[id - 1], id - 1);
                    }
                    break;
                }

                char proposition_bis[][128] = { "annuler", "prenom", "nom", "ville", "code postal", "numero telephone", "email", "profession", "tous" };
                int sous_rep = demande_menu_while("Sur quoi voulez vous rechercher : ",
                    proposition_bis,
                    (sizeof(proposition_bis) / (128 * sizeof(char))) - ((rep < 4) ? 1 : 0)); // si Recherche donné alors pas afficher "tous"

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

                if (rep <= 3) {

                    if (desir_rechercher_sur != TRIE_NULL) {

                        char* search_string = malloc(get_size_arg(desir_rechercher_sur) * sizeof(char));
                        print(PINK, DEFAULT_BACKGROUND_COLOR, "Votre recherche: ");
                        print(AQUA, DEFAULT_BACKGROUND_COLOR, ">> ");
                        input(search_string, get_size_arg(desir_rechercher_sur));

                        if (rep == 1) {
                            recherche_substring(users, nbr_utilisateur, search_string, desir_rechercher_sur);
                        } else if (rep == 2) {
                            recherche_string(users, nbr_utilisateur, search_string, desir_rechercher_sur);
                        } else {
                            recherche_exacte(users, nbr_utilisateur, search_string, desir_rechercher_sur);
                        }
                    }
                } else if (rep == 4) {
                    if (desir_rechercher_sur != TRIE_NULL) {
                        if (desir_rechercher_sur == TIRE_TOUS) {
                            recherche_tous_manquante(users, nbr_utilisateur);
                        } else {
                            recherche_element_manquant(users, nbr_utilisateur, desir_rechercher_sur);
                        }
                    }
                }
            } else {
                print(RED, DEFAULT_BACKGROUND_COLOR, "vous n'avez pas charger de fichier.\n");
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
    print(RED, DEFAULT_BACKGROUND_COLOR, "exit\n");
    return EXIT_SUCCESS;
}

int main()
{
    return menu();
}
