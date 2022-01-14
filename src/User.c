#include "User.h"

#include "Verif.h"
#include "tableau.h"

user input_user()
{
    user u;

    setColor(YELLOW);
    printf("\nEntrez le prenom : ");
    setColor(AQUA);
    input(u.prenom, SIZE_PRENOM);

    setColor(YELLOW);
    printf("\nEntrez le nom : ");
    setColor(AQUA);
    input(u.nom, SIZE_NOM);

    setColor(YELLOW);
    printf("\nEntrez la ville : ");
    setColor(AQUA);
    input(u.ville, SIZE_VILLE);

    setColor(YELLOW);
    printf("\nEntrez le code postal : ");
    setColor(AQUA);
    input(u.code_postal, SIZE_CODE_POSTAL);

    setColor(YELLOW);
    printf("\nEntrez le numero de telephone : ");
    setColor(AQUA);
    input(u.no_telephone, SIZE_NO_TELEPHONE);

    setColor(YELLOW);
    printf("\nEntrez l'email : ");
    setColor(AQUA);
    input(u.email, SIZE_EMAIL);

    setColor(YELLOW);
    printf("\nEntrez le metier : ");
    setColor(AQUA);
    input(u.metier, SIZE_METIER);
    setDefaultColor();

    return u;
}

void print_user(user u, int id)
{
    if (!is_del(u)) {
        printf("[%d] %s, %s, %s, %s, %s, %s, %s\n", id + 1, u.prenom, u.nom, u.ville, u.code_postal, u.no_telephone, u.email, u.metier);
    }
}
int del_user(user tab[], int id, int taille)
{
    if (!is_in_tab(id, taille)) {
        return -1;
    }
    tab[id].prenom[0] = '\0';
    tab[id].nom[0] = '\0';
    tab[id].ville[0] = '\0';
    tab[id].code_postal[0] = '\0';
    tab[id].no_telephone[0] = '\0';
    tab[id].email[0] = '\0';
    tab[id].metier[0] = '\0';
    return 0;
}

int insert_user(user* tab[], int* taille, user u, int which)
{
    if (which == TRIE_NULL) {
        print(RED, DEFAULT_BACKGROUND_COLOR, "Erreur : le tableau n'est pas tri%s...\n", E);
        return EXIT_FAILURE;
    }
    if (is_del(u)) {
        print(RED, DEFAULT_BACKGROUND_COLOR, "Ajout d'utilisateur vide impossible\n");
        return EXIT_FAILURE;
    }
    int insert_locate;
    if (!is_del((*tab)[(*taille) - 1])) {
        insert_locate = *taille;
        add_space(tab, *taille, *taille + 1);
        permute(&(*tab)[insert_locate], &u);
        (*taille)++;
    } else {
        insert_locate = *taille - 1;
        permute(&(*tab)[insert_locate], &u);
    }

    char* info_lower = malloc((get_size_arg(which)) * sizeof(char));
    char* curr_info_lower = malloc(get_size_arg(which) * sizeof(char));

    strtolower(info_lower, get_arg(&(*tab)[insert_locate], which), get_size_arg(which));
    strtolower(curr_info_lower, get_arg(&(*tab)[insert_locate - 1], which), get_size_arg(which));

    while (insert_locate > 0 && string_cmp(info_lower, curr_info_lower) < 0) {
        permute(&(*tab)[insert_locate], &(*tab)[insert_locate - 1]);
        insert_locate--;
        if (insert_locate > 0) {
            strtolower(curr_info_lower, get_arg(&(*tab)[insert_locate - 1], which), get_size_arg(which));
        }
    }
    free(info_lower);
    free(curr_info_lower);

    return EXIT_SUCCESS;
}

int modif_user(user* to_modif)
{
    if (to_modif == NULL) {
        return EXIT_FAILURE;
    }
    user u = input_user();

    if (u.prenom[0] != '\0') {
        strcpy(to_modif->prenom, u.prenom);
    }

    if (u.nom[0] != '\0') {
        strcpy(to_modif->nom, u.nom);
    }

    if (u.ville[0] != '\0') {
        strcpy(to_modif->ville, u.ville);
    }

    if (u.code_postal[0] != '\0') {
        strcpy(to_modif->code_postal, u.code_postal);
    }

    if (u.no_telephone[0] != '\0') {
        strcpy(to_modif->no_telephone, u.no_telephone);
    }

    if (u.email[0] != '\0') {
        strcpy(to_modif->email, u.email);
    }

    if (u.metier[0] != '\0') {
        strcpy(to_modif->metier, u.metier);
    }
    return EXIT_SUCCESS;
}

int recherche_str_cmp(const char* s1, const char* s2)
{
    return string_cmp(s1, s2) == 0;
}
int recherche_element_cmp(const char* s1, const char* s2) // nous n'utilisons pas le second argument (s2) mais nous le mettons quand même car il est necessaire que la fonction ("func_compare") de comparaison dans la fonction "recherche_in_tab" soit de la frome (int (fonction)(const char*, const char*)) se qui nous évite d'écrire 4 fois la "recherche_in_tab"
{
    return s1[0] == '\0';
}

void recherche_in_tab(user tab[], int taille, char* string, int which, int size_wanted_for_which, int (*func_compare)(const char*, const char*))
{
    if (string == NULL || tab == NULL) {
        return;
    }
    int i, j, count, test_compare;
    char c_save;
    char* ptr_chaine_compare;
    count = 0;
    for (i = 0, j = 0; i < taille; i++) {
        ptr_chaine_compare = get_arg(&tab[i], which);
        c_save = ptr_chaine_compare[size_wanted_for_which];
        ptr_chaine_compare[size_wanted_for_which] = '\0';
        test_compare = func_compare(ptr_chaine_compare, string);
        ptr_chaine_compare[size_wanted_for_which] = c_save;
        if (test_compare) {
            if (j % 2 == 0) {
                setColor(PURPLE);
            } else {
                setColor(WHITE);
            }

            print_user(tab[i], i);
            setDefaultColor();
            if (!is_del(tab[i])) {
                j++;
                count++;
            }
        }
    }
    setColor(GREEN);
    printf("%d r%ssultat(s) trouv%s(s)\n", count, E, E);
    setDefaultColor();
}

void recherche_substring(user tab[], int taille, char* substring, int which) // et affiche
{
    recherche_in_tab(tab, taille, substring, which, get_size_arg(which), stringstring);
}

void recherche_string(user tab[], int taille, char* string, int which) // et affiche
{
    recherche_in_tab(tab, taille, string, which, strlen(string), recherche_str_cmp);
}

void recherche_exacte(user tab[], int taille, char* string, int which) // et affiche
{
    recherche_in_tab(tab, taille, string, which, get_size_arg(which), recherche_str_cmp);
}

void recherche_element_manquant(user tab[], int taille, int which) // et affiche
{
    recherche_in_tab(tab, taille, "NULL", which, 2, recherche_element_cmp);
}

void recherche_tous_manquante(user tab[], int taille) // et affiche
{
    int i, j, count;
    count = 0;
    for (i = 0, j = 0; i < taille; i++) {
        if (tab[i].prenom[0] == '\0' || tab[i].nom[0] == '\0' || tab[i].ville[0] == '\0' || tab[i].code_postal[0] == '\0' || tab[i].no_telephone[0] == '\0' || tab[i].email[0] == '\0' || tab[i].metier[0] == '\0') {

            if (j % 2 == 0) {
                setColor(PURPLE);
            } else {
                setColor(WHITE);
            }
            print_user(tab[i], i);
            setDefaultColor();
            if (!is_del(tab[i])) {
                j++;
                count++;
            }
        }
    }
    setColor(GREEN);
    printf("%d r%ssultat(s) trouv%s(s)\n", count, E, E);
    setDefaultColor();
}

void usercpy(user* dst, user* src)
{
    if (dst == NULL || src == NULL) {
        return;
    }
    memcpy(dst, src, sizeof(user));
}
int userEqual(user* u1, user* u2)
{
    return (u1 != NULL && u2 != NULL && string_cmp((const char*)u1->prenom, (const char*)u2->prenom) == 0 && string_cmp((const char*)u1->nom, (const char*)u2->nom) == 0 && string_cmp((const char*)u1->ville, (const char*)u2->ville) == 0 && string_cmp((const char*)u1->code_postal, (const char*)u2->code_postal) == 0 && string_cmp((const char*)u1->email, (const char*)u2->email) == 0 && string_cmp((const char*)u1->metier, (const char*)u2->metier) == 0 && string_cmp((const char*)u1->no_telephone, (const char*)u2->no_telephone) == 0);
}

char* get_arg(user* u, int which_one)
{
    switch (which_one) {
    case TRIE_PRENOM:
        return u->prenom;
        break;
    case TRIE_NOM:
        return u->nom;
        break;
    case TRIE_VILLE:
        return u->ville;
        break;
    case TRIE_CODE_POSTAL:
        return u->code_postal;
        break;
    case TRIE_NO_TELEPHONE:
        return u->no_telephone;
        break;
    case TRIE_EMAIL:
        return u->email;
        break;
    case TRIE_METIER:
        return u->metier;
        break;
    }
    return NULL;
}

int get_size_arg(int which_one)
{
    switch (which_one) {
    case TRIE_PRENOM:
        return SIZE_PRENOM;
        break;
    case TRIE_NOM:
        return SIZE_NOM;
        break;
    case TRIE_VILLE:
        return SIZE_VILLE;
        break;
    case TRIE_CODE_POSTAL:
        return SIZE_CODE_POSTAL;
        break;
    case TRIE_NO_TELEPHONE:
        return SIZE_NO_TELEPHONE;
        break;
    case TRIE_EMAIL:
        return SIZE_EMAIL;
        break;
    case TRIE_METIER:
        return SIZE_METIER;
        break;
    }
    return 0;
}

void recherche_doublon(user tab[], int taille, int which_trier)
{
    if (tab == NULL) {
        return;
    }
    int i, j, count;
    count = 0;
    for (i = 0, j = 0; i < taille - 1; i++) {
        int k = i + 1;
        if (is_del(tab[i])) {
            break;
        }
        while (k < taille && string_cmp(get_arg(&tab[i], which_trier), get_arg(&tab[k], which_trier)) == 0) {
            if (userEqual(&tab[i], &tab[k]) == 1) {
                if (j % 2 == 0) {
                    setColor(PURPLE);
                    print_user(tab[i], i);
                    setColor(WHITE);
                    print_user(tab[k], k);
                } else {
                    setColor(WHITE);
                    print_user(tab[i], i);
                    setColor(PURPLE);
                    print_user(tab[k], k);
                }

                setDefaultColor();
                count += 2;

                i = k;

                if (userEqual(&tab[i], &tab[k + 1]) == 1) {
                    if (j % 2 == 0) {
                        setColor(PURPLE);
                    } else {
                        setColor(WHITE);
                    }
                    print_user(tab[k + 1], k + 1);
                    count++;
                    j++;

                    i += 2;
                    k += 2;
                } else {
                    k++;
                }
                setDefaultColor();
            }
            k++;
        }
    }
    setColor(GREEN);
    printf("%d similaire trouv%s(s)\n", count, E);
    setDefaultColor();
}