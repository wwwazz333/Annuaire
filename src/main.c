#include <stdio.h>
#include <stdlib.h>

#include "Save.h"
#include "Terminal.h"
#include "Timer.h"
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
void show_menu(int isdoublon)
{
    int i = 0;
    setDefaultColor();
    show_menu_Title("Menu");
    setColor(RED);
    show_line_menu("Quitter\n", &i); // 0
    setColor(GREEN);
    show_line_menu("Charger un ficher\n", &i); // 1
    show_line_menu("Sauvegarder un fichier\n", &i); // 2
    setColor(BLUE);
    show_line_menu("Ajouter un Client\n", &i); // 3
    show_line_menu("Supprimer un Client\n", &i); // 4
    show_line_menu("Modifier un Client\n", &i); // 5
    setColor(PINK);
    show_line_menu("Affichage des Clients\n", &i); // 6
    show_line_menu("Fonctions de Recherches\n", &i); // 7
    if (isdoublon==1) {
        setColor(YELLOW);
        show_line_menu("Affichage des Doublons", &i); // 8
        print(WHITE,DEFAULT_BACKGROUND_COLOR," - ");
        print(RED,DEFAULT_BACKGROUND_COLOR,"Doublon(s) trouv%s(s)\n", E);
    }

    setDefaultColor();
}

/**
 * @brief Demande de sauvegarder avant de quitter le fichier
 *
 * @pre aucune
 * @post sauvegarde, quitte ou annule l'action
 *
 * @param issave fichier deja sauvegarder ou non
 * @param save_nom_fichier sauvegarde du nom de fichier ouvert
 * @param users Annuaire d'utilisateurs
 * @param nbr_utilisateurs le nombre d'utilisateurs du tableau
 * @param users_init Pour librérer l'espace lorsqu'on quitte
 *
 */
void ask_save(int issave, char save_nom_fichier[50], user* users, int nbr_utilisateurs, int users_init)
{
    FILE* fp;
    if (issave == 0) {
        print(RED, DEFAULT_BACKGROUND_COLOR, "Fichier non sauvegard%s\n\n", E);
        char proposition[][128] = { "Ne pas Enregrister", "Enregistrer", "Annuler" };
        int rep = demande_menu_while("Voulez vous d'abord enregistrer ? : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
        switch (rep) {
        case 0:
            if (users_init) {
                free(users);
            }
            print(RED, DEFAULT_BACKGROUND_COLOR, "exit\n");
            exit(EXIT_SUCCESS);
        case 1:
            fp = fopen(save_nom_fichier, "w");
            if (fp == NULL) {
                print(RED, DEFAULT_BACKGROUND_COLOR, "Le fichier n'a pas pu etre ouvert.\n");
                break;
            }
            save(fp, users, nbr_utilisateurs);
            print(GREEN, DEFAULT_BACKGROUND_COLOR, "Le fichier est sauvegard%s\n", E);
            fclose(fp);
            if (users_init) {
                free(users);
            }
            exit(EXIT_SUCCESS);
        case 2:
            print(ORANGE, DEFAULT_BACKGROUND_COLOR, "Annuler\n");
            break;
        }
    }
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
    int nbr_utilisateurs;
    char* nom_fichier;
    char save_nom_fichier[50];
    TrierSur triersur;
    triersur = TRIE_NULL;
    int issave = 1;
    int isdoublon = 0;

    char reponse = '\0';
    while (reponse != '0' || issave == 0) {
        show_menu(isdoublon);
        print(ORANGE, DEFAULT_BACKGROUND_COLOR, ">> ");
        setColor(AQUA);
        scanf("%c", &reponse);
        setDefaultColor();

        flush(); // vide stdin (au cas ou entrer plusieur caractère précédament)
        cls(); // clear le terminal
        switch (reponse) {
        case '0':
            ask_save(issave, save_nom_fichier, users, nbr_utilisateurs, users_init);
            break;
        case '1': // charger un fichier
            show_menu_Title("Charger fichier");
            nom_fichier = ask_fichier_existant("csv");
            strcpy(save_nom_fichier, nom_fichier);
            Clock(START); // démarage du timer
            fp = fopen(nom_fichier, "r");
            if (fp == NULL) {
                print(RED, DEFAULT_BACKGROUND_COLOR, "Le fichier n'a pas pu etre ouvert.\n");
            } else {
                nbr_utilisateurs = nombre_utilisateurs(fp);
                users = malloc(nbr_utilisateurs * sizeof(user));
                load(fp, users);
                users_init = 1;
                print(GREEN, DEFAULT_BACKGROUND_COLOR, "Le fichier a bien %st%s charg%s\n", E, E, E);
                fclose(fp);

                quick_sort(users, 0, nbr_utilisateurs - 1, TRIE_PRENOM);
                triersur = TRIE_PRENOM;
                isdoublon=exist_doublon(users, nbr_utilisateurs, triersur);
            }
            Clock(END); // affiche le timer
            break;
        case '2': // Sauvegarde du tableau
            show_menu_Title("Sauvegarde fichier");
            if (users_init) {
                nom_fichier = ask_fichier("csv");
                setColor(GREEN);
                printf("%d utilisateur(s) a sauvegard%s.\n", nbr_utilisateurs - get_nombre_user_del(users, nbr_utilisateurs), E);
                setDefaultColor();
                char proposition[][128] = { "annuler", "sauvegarder" };
                int rep = demande_menu_while("voulez vous vraiment sauvegarder ? : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                Clock(START); // démarage du timer
                if (rep == 1) {
                    fp = fopen(nom_fichier, "w");
                    free(nom_fichier);
                    if (fp == NULL) {
                        print(RED, DEFAULT_BACKGROUND_COLOR, "Le fichier n'a pas pu etre enregist%s\n", E);
                    } else {
                        save(fp, users, nbr_utilisateurs);
                        print(GREEN, DEFAULT_BACKGROUND_COLOR, "Le fichier est sauvegard%s\n", E);
                        fclose(fp);
                        issave = 1;
                    }
                } else {
                    print(RED, DEFAULT_BACKGROUND_COLOR, "action annul%se\n", E);
                }
                Clock(END); // affiche le timer
            } else {
                print(RED, DEFAULT_BACKGROUND_COLOR, "vous n'avez pas charg%s de fichier.\n", E);
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
                Clock(START); // démarage du timer
                if (rep == 1) {
                    if (insert_user(&users, &nbr_utilisateurs, u, triersur) == EXIT_SUCCESS) {
                        print(GREEN, DEFAULT_BACKGROUND_COLOR, "client ajout%s\n", E);
                        isdoublon=exist_doublon(users, nbr_utilisateurs, triersur);
                        issave = 0;
                    }
                } else {
                    print(RED, DEFAULT_BACKGROUND_COLOR, "action annuler\n");
                }
                Clock(END); // affiche le timer
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
                if (!is_in_tab(id_del - 1, nbr_utilisateurs)) {
                    print(RED, DEFAULT_BACKGROUND_COLOR, "l'id n'est pas dans le tableau\n");
                    break;
                }
                print_user(users[id_del - 1], id_del - 1);
                char proposition[][128] = { "annuler", "supprimer" };
                int rep = demande_menu_while("Voulez vous vraiment le supprimer : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                Clock(START); // démarage du timer
                if (rep == 1) {
                    if (del_user(users, id_del - 1, nbr_utilisateurs) == 0) {
                        move_user_to_end(users, nbr_utilisateurs, id_del - 1);
                        print(GREEN, DEFAULT_BACKGROUND_COLOR, "suppression effectu%se.\n", E);
                        isdoublon=exist_doublon(users, nbr_utilisateurs, triersur);
                        issave = 0;
                    } else {
                        print(RED, DEFAULT_BACKGROUND_COLOR, "erreur lors de la suppression.\n");
                    }
                } else {
                    print(RED, DEFAULT_BACKGROUND_COLOR, "action annul%se\n", E);
                }
                Clock(END); // affiche le timer
            } else {
                print(RED, DEFAULT_BACKGROUND_COLOR, "vous n'avez pas charger de fichier.\n");
            }
            break;
        case '5': // modification client
            show_menu_Title("modification Client");
            if (users_init) {
                print(YELLOW, DEFAULT_BACKGROUND_COLOR, "id utilisateur: ");
                int id = 0;
                setColor(AQUA);
                scanf("%d", &id);
                id--;
                setDefaultColor();
                flush();
                if (!is_in_tab(id - 1, nbr_utilisateurs)) {
                    print(RED, DEFAULT_BACKGROUND_COLOR, "l'id n'est pas dans le tableau\n");
                    break;
                }
                print_user(users[id], id);

                char proposition[][128] = { "annuler", "modifier" };
                int rep = demande_menu_while("voulez vous modifier celui-ci ? : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                if (rep == 1) {
                    print(GREY, DEFAULT_BACKGROUND_COLOR, "Appuyer sur ENTRER pour ne pas modifier l'information\n");
                    user temp;
                    usercpy(&temp, &users[id]);
                    modif_user(&temp);
                    print_user(temp, id);

                    rep = demande_menu_while("voulez vous modifier l'utilisateur par celui-ci ? : ", proposition, sizeof(proposition) / (128 * sizeof(char)));
                    Clock(START); // démarage du timer
                    if (rep == 1) {
                        usercpy(&users[id], &temp);
                        oyelami(users, nbr_utilisateurs - 1, triersur); // re trie le tableau
                        print(GREEN, DEFAULT_BACKGROUND_COLOR, "modification effectu%se.\n", E);
                        isdoublon=exist_doublon(users, nbr_utilisateurs, triersur);
                        issave = 0;
                    } else {
                        print(RED, DEFAULT_BACKGROUND_COLOR, "action annul%se\n", E);
                    }
                    Clock(END); // affiche le timer
                } else {
                    print(RED, DEFAULT_BACKGROUND_COLOR, "action annul%se\n", E);
                }
            } else {
                print(RED, DEFAULT_BACKGROUND_COLOR, "vous n'avez pas charg%s de fichier.\n", E);
            }
            break;
        case '6': // Affichage Clients
            show_menu_Title("Affichage Clients");
            if (users_init) {
                char proposition[][128] = { "annuler", "Affichage complet", "Affichage par section" };
                int rep = demande_menu_while("Quelle methode d'affichage choisissez-vous: ", proposition, sizeof(proposition) / (128 * sizeof(char)));

                if (rep != 0) {
                    char proposition_bis[][128] = { "annuler", "prenom", "nom", "ville", "code postal", "profession" };
                    int rep_bis = demande_menu_while("Sur quoi voulez vous trier :", proposition_bis, sizeof(proposition_bis) / (128 * sizeof(char)));
                    Clock(START); // démarage du timer
                    TrierSur desir_trier_sur;
                    switch (rep_bis) {
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
                    long time_spend = 0;
                    if (desir_trier_sur != TRIE_NULL) {
                        if (triersur != desir_trier_sur) {
                            quick_sort(users, 0, nbr_utilisateurs - 1, desir_trier_sur);
                            triersur = desir_trier_sur;
                        }
                        time_spend = Clock(END); // affiche le timer et le sauvegarde

                        if (rep == 1) {
                            print_tab(users, nbr_utilisateurs);                            
                        } else if (rep == 2) {
                            print_tab_sect(users, nbr_utilisateurs, 500);
                        }
                        print(AQUA, DEFAULT_BACKGROUND_COLOR, "%.3lf milli-secondes (pour le trie et non l'affichage)\n", time_spend / 1000.0f); // re-affiche le temps écouler l'hors du trie et non de l'affichage
                        isdoublon=exist_doublon(users, nbr_utilisateurs, triersur);
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
                } else if (rep == 5) {
                    print(YELLOW, DEFAULT_BACKGROUND_COLOR, "id utilisateur: ");
                    int id = 0;
                    setColor(AQUA);
                    scanf("%d", &id);
                    setDefaultColor();
                    flush();
                    Clock(START); // démarage du timer
                    if (!is_in_tab(id - 1, nbr_utilisateurs)) {
                        print(RED, DEFAULT_BACKGROUND_COLOR, "l'ID n'est pas dans le tableau\n");
                        break;
                    }
                    print_user(users[id - 1], id - 1);
                    Clock(END); // affiche le timer
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
                            Clock(START); // démarage du timer
                            recherche_substring(users, nbr_utilisateurs, search_string, desir_rechercher_sur);
                            Clock(END); // affiche le timer
                        } else if (rep == 2) {
                            Clock(START); // démarage du timer
                            recherche_string(users, nbr_utilisateurs, search_string, desir_rechercher_sur);
                            Clock(END); // affiche le timer
                        } else {
                            Clock(START); // démarage du timer
                            recherche_exacte(users, nbr_utilisateurs, search_string, desir_rechercher_sur);
                            Clock(END); // affiche le timer
                        }
                    }
                } else if (rep == 4) {
                    if (desir_rechercher_sur != TRIE_NULL) {
                        if (desir_rechercher_sur == TIRE_TOUS) {
                            Clock(START); // démarage du timer
                            recherche_tous_manquante(users, nbr_utilisateurs);
                            Clock(END); // affiche le timer
                        } else {
                            Clock(START); // démarage du timer
                            recherche_element_manquant(users, nbr_utilisateurs, desir_rechercher_sur);
                            Clock(END); // affiche le timer
                        }
                    }
                }
            } else {
                print(RED, DEFAULT_BACKGROUND_COLOR, "vous n'avez pas charg%s de fichier.\n", E);
            }
            break;
        case '8':
            if (isdoublon==1) {
                show_menu_Title("Affichage des Doublons");
                Clock(START); // démarage du timer
                recherche_doublon(users, nbr_utilisateurs, triersur);
                Clock(END); // affiche le timer
            }
            break;
        case '$':
            show_menu_Title("Easter Egg - Gremlins");
            show_gremlins();
            break;
        case '*':
            // Mode developpeur (pour éviter le chargement durant les tests fois le fichier)
            fp = fopen("annuaire5000.csv", "r");
            if (fp == NULL) {
                print(RED, DEFAULT_BACKGROUND_COLOR, "Le fichier n'a pas pu etre ouvert.\n");
            } else {
                nbr_utilisateurs = nombre_utilisateurs(fp);
                users = malloc(nbr_utilisateurs * sizeof(user));
                load(fp, users);
                users_init = 1;
                print(GREEN, DEFAULT_BACKGROUND_COLOR, "Le fichier a bien %st%s charg%s\n", E, E, E);
                fclose(fp);
                quick_sort(users, 0, nbr_utilisateurs - 1, TRIE_PRENOM);
                triersur = TRIE_PRENOM;
            }
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
