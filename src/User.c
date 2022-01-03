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
    tab[id].nom[0] = '\0';
    tab[id].prenom[0] = '\0';
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
        print(RED, DEFAULT_BACKGROUND_COLOR, "Erreur : le tableau n'est pas trier...\n");
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
        strtolower(curr_info_lower, get_arg(&(*tab)[insert_locate - 1], which), get_size_arg(which));
    }
    free(info_lower);
    free(curr_info_lower);

    return EXIT_SUCCESS;
}

int modif_user(user* to_modif)
{
    user u = input_user();

    print(YELLOW, DEFAULT_BACKGROUND_COLOR, "Entrez le prenom : ");
    setColor(BLUE);
    input(u.prenom, SIZE_PRENOM);
    if (u.prenom[0] != '\0') {
        strcpy(to_modif->prenom, u.prenom);
    }

    print(YELLOW, DEFAULT_BACKGROUND_COLOR, "Entrez le nom : ");
    setColor(BLUE);
    input(u.nom, SIZE_NOM);
    if (u.nom[0] != '\0') {
        strcpy(to_modif->nom, u.nom);
    }

    print(YELLOW, DEFAULT_BACKGROUND_COLOR, "Entrez la ville : ");
    setColor(BLUE);
    input(u.ville, SIZE_VILLE);
    if (u.ville[0] != '\0') {
        strcpy(to_modif->ville, u.ville);
    }

    print(YELLOW, DEFAULT_BACKGROUND_COLOR, "Entrez le code postal : ");
    setColor(BLUE);
    input(u.code_postal, SIZE_CODE_POSTAL);
    if (u.code_postal[0] != '\0') {
        strcpy(to_modif->code_postal, u.code_postal);
    }

    print(YELLOW, DEFAULT_BACKGROUND_COLOR, "Entrez le numero de telephone : ");
    setColor(BLUE);
    input(u.no_telephone, SIZE_NO_TELEPHONE);
    if (u.no_telephone[0] != '\0') {
        strcpy(to_modif->no_telephone, u.no_telephone);
    }

    print(YELLOW, DEFAULT_BACKGROUND_COLOR, "Entrez l'email : ");
    setColor(BLUE);
    input(u.email, SIZE_EMAIL);
    if (u.email[0] != '\0') {
        strcpy(to_modif->email, u.email);
    }

    print(YELLOW, DEFAULT_BACKGROUND_COLOR, "Entrez le metier : ");
    setColor(BLUE);
    input(u.metier, SIZE_METIER);
    if (u.metier[0] != '\0') {
        strcpy(to_modif->metier, u.metier);
    }
    return 0;
}

int recherche_emplacement(user tab[], int taille, char* information, int which) // recherche le dernier
{
    int millieu;
    int gauche = 0;
    int droite = taille - 1;

    char* info_lower = malloc(get_size_arg(which) * sizeof(char));
    char* curr_info_lower = malloc(get_size_arg(which) * sizeof(char));

    strtolower(info_lower, information, get_size_arg(which));

    while (gauche <= droite) {
        millieu = (droite + gauche) / 2;
        strtolower(curr_info_lower, get_arg(&tab[millieu], which), get_size_arg(which));
        if (string_cmp(curr_info_lower, info_lower) < 0) {
            gauche = millieu + 1;
        } else if (string_cmp(curr_info_lower, info_lower) > 0) {
            droite = millieu - 1;
        } else { // si égale
            do {
                millieu++;
                strtolower(curr_info_lower, get_arg(&tab[millieu], which), get_size_arg(which));
            } while (string_cmp(curr_info_lower, info_lower) == 0);

            free(info_lower);
            free(curr_info_lower);
            return millieu;
        }
    }

    free(info_lower);
    free(curr_info_lower);
    return gauche;
}

int recherche_str_cmp(const char* s1, const char* s2)
{
    return string_cmp(s1, s2) == 0;
}
int recherche_element_cmp(const char* s1, const char* s2)
{
    return s1[0] == '\0';
}

void recherche_in_tab(user tab[], int taille, char* string, int which, int size_wanted_for_which, int (*func_compare)(const char*, const char*))
{

    // string[size_wanted_for_which-1] = '\0';
    int i, j, count, test_compare;
    char c_save;
    count = 0;
    for (i = 0, j = 0; i < taille; i++) {
        c_save = get_arg(&tab[i], which)[size_wanted_for_which - 1];
        if (size_wanted_for_which - 1 >= get_size_arg(which)) {
            fprintf(stderr, "trop grand : %d\t%d\n", size_wanted_for_which - 1, get_size_arg(which));
        }
        get_arg(&tab[i], which)[size_wanted_for_which - 1] = '\0';
        test_compare = func_compare(get_arg(&tab[i], which), string);
        get_arg(&tab[i], which)[size_wanted_for_which - 1] = c_save;
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
    printf("%d resultat(s) trouve.\n", count);
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
        if (get_arg(&tab[i], TRIE_PRENOM)[0] == '\0' || get_arg(&tab[i], TRIE_NOM)[0] == '\0' || get_arg(&tab[i], TRIE_VILLE)[0] == '\0' || get_arg(&tab[i], TRIE_CODE_POSTAL)[0] == '\0' || get_arg(&tab[i], TRIE_NO_TELEPHONE)[0] == '\0' || get_arg(&tab[i], TRIE_EMAIL)[0] == '\0' || get_arg(&tab[i], TRIE_METIER)[0] == '\0') {

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
    printf("%d resultat(s) trouve.\n", count);
    setDefaultColor();
}

user* recherche_by_id(user tab[], int taille, int id)
{
    if (id >= 0 && id < taille) {
        return NULL;
    }

    return &tab[id];
}

void usercpy(user* dst, user* src)
{
    if (dst == NULL || src == NULL) {
        return;
    }
    memcpy(dst, src, sizeof(user));
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