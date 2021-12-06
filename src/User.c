#include "User.h"

#include "Verif.h"
#include "tableau.h"

user input_user()
{
    user u;

    setColor(ORANGE);
    printf("\nEntrez le prenom : ");
    setColor(AQUA);
    input(u.prenom, SIZE_PRENOM);

    setColor(ORANGE);
    printf("\nEntrez le nom : ");
    setColor(AQUA);
    input(u.nom, SIZE_NOM);

    setColor(ORANGE);
    printf("\nEntrez la ville : ");
    setColor(AQUA);
    input(u.ville, SIZE_VILLE);

    setColor(ORANGE);
    printf("\nEntrez le code postal : ");
    setColor(AQUA);
    input(u.code_postal, SIZE_CODE_POSTAL);
    printf("------------code postal : %s\n", u.code_postal);

    setColor(ORANGE);
    printf("\nEntrez le numero de telephone : ");
    setColor(AQUA);
    input(u.no_telephone, SIZE_NO_TELEPHONE);

    setColor(ORANGE);
    printf("\nEntrez l'email : ");
    setColor(AQUA);
    input(u.email, SIZE_EMAIL);

    setColor(ORANGE);
    printf("\nEntrez le metier : ");
    setColor(AQUA);
    input(u.metier, SIZE_METIER);
    setDefaultColor();

    return u;
}

void print_user(user u, int id)
{
    printf("[%d] %s, %s, %s, %s, %s, %s, %s", id + 1, u.prenom, u.nom, u.ville, u.code_postal, u.no_telephone, u.email, u.metier);
}
int del_user(user tab[], int id, int taille)
{
    if (id < 0 || id >= taille) {
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
        print("Erreur : le tableau n'est pas trier...\n", RED, DEFAULT_BACKGROUND_COLOR);
    }
    if (is_del(u)) {
        printf("Vous ne pouvez pas ajouté un utilisateur vide.\n");
        return EXIT_FAILURE;
    }
    int index_a_ajouter = recherche_emplacement(*tab, *taille, get_arg(&u, which), which);
    if (index_a_ajouter < 0) {
        return EXIT_FAILURE;
    }

    while (index_a_ajouter < *taille && !is_del(u)) {
        permute(&(*tab)[index_a_ajouter], &u);

        index_a_ajouter++;
    }

    if (!is_del(u)) {
        add_space(tab, *taille, *taille + 1);
        permute(&(*tab)[*taille], &u);
        (*taille)++;
    }

    return EXIT_SUCCESS;
}

int modif_user(user tab[], int id, int taille) // GROS BUG SA MERE
{
    if (id < 0 || id >= taille) {
        return -1;
    }
    user u;

    print("Entrez le prenom : ", YELLOW, DEFAULT_BACKGROUND_COLOR);
    setColor(BLUE);
    input(u.prenom, SIZE_PRENOM);
    if (u.prenom[0] != '\0') {
        strcpy(tab[id].prenom, u.prenom);
    }

    print("Entrez le nom : ", YELLOW, DEFAULT_BACKGROUND_COLOR);
    setColor(BLUE);
    input(u.nom, SIZE_NOM);
    if (u.nom[0] != '\0') {
        strcpy(tab[id].nom, u.nom);
    }

    print("Entrez la ville : ", YELLOW, DEFAULT_BACKGROUND_COLOR);
    setColor(BLUE);
    input(u.ville, SIZE_VILLE);
    if (u.ville[0] != '\0') {
        strcpy(tab[id].ville, u.ville);
    }

    print("Entrez le code postal : ", YELLOW, DEFAULT_BACKGROUND_COLOR);
    setColor(BLUE);
    input(u.code_postal, SIZE_CODE_POSTAL);
    if (u.code_postal[0] != '\0') {
        strcpy(tab[id].code_postal, u.code_postal);
    }

    print("Entrez le numero de telephone : ", YELLOW, DEFAULT_BACKGROUND_COLOR);
    setColor(BLUE);
    input(u.no_telephone, SIZE_NO_TELEPHONE);
    if (u.no_telephone[0] != '\0') {
        strcpy(tab[id].no_telephone, u.no_telephone);
    }

    print("Entrez l'email : ", YELLOW, DEFAULT_BACKGROUND_COLOR);
    setColor(BLUE);
    input(u.email, SIZE_EMAIL);
    if (u.email[0] != '\0') {
        strcpy(tab[id].email, u.email);
    }

    print("Entrez le metier : ", YELLOW, DEFAULT_BACKGROUND_COLOR);
    setColor(BLUE);
    input(u.metier, SIZE_METIER);
    if (u.metier[0] != '\0') {
        strcpy(tab[id].metier, u.metier);
    }
    setDefaultColor();
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
        if (strcmp(curr_info_lower, info_lower) < 0) {
            gauche = millieu + 1;
        } else if (strcmp(curr_info_lower, info_lower) > 0) {
            droite = millieu - 1;
        } else { // si égale
            do {
                millieu++;
                strtolower(curr_info_lower, get_arg(&tab[millieu], which), get_size_arg(which));
            } while (strcmp(curr_info_lower, info_lower) == 0);

            free(info_lower);
            free(curr_info_lower);
            return millieu;
        }
    }

    free(info_lower);
    free(curr_info_lower);
    return gauche;
}

/* int recherche_emplacement_existant(user tab[], int taille, char* information, int which) // sert a rien pour l'instant !!!!!!!!!!!!!
{
    int millieu;
    int gauche = 0;
    int droite = taille - 1;

    char* name_lower = malloc(get_size_arg(which) * sizeof(char));
    char* curr_name_lower = malloc(get_size_arg(which) * sizeof(char));

    strtolower(name_lower, information, get_size_arg(which));

    while (gauche <= droite) {
        millieu = (droite + gauche) / 2;
        strtolower(curr_name_lower, get_arg(&tab[millieu], which), get_size_arg(which));
        if (strcmp(curr_name_lower, name_lower) < 0) {
            gauche = millieu + 1;
        } else if (strcmp(curr_name_lower, name_lower) > 0) {
            droite = millieu - 1;
        } else { // si égale cherche le dernier
            while (strcmp(curr_name_lower, name_lower) == 0) {
                millieu++;
                strtolower(curr_name_lower, get_arg(&tab[millieu], which), get_size_arg(which));
            }

            free(name_lower);
            free(curr_name_lower);
            return millieu;
        }
    }

    free(name_lower);
    free(curr_name_lower);
    return -1;
} */
void recherche_substring(user tab[], int taille, char* substring, int which) // et affiche
{

    char* substring_lower = malloc((strlen(substring) + 1) * sizeof(char));
    char* curr_info_lower = malloc((get_size_arg(which) + 1) * sizeof(char));

    strtolower(substring_lower, substring, strlen(substring) + 1);
    int i, j;
    for (i = 0, j = 0; i < taille; i++) {
        strtolower(curr_info_lower, get_arg(&tab[i], which), get_size_arg(which));
        if (strstr(curr_info_lower, substring_lower) != NULL) {
            if (j % 2 == 0) {
                setColor(PURPLE);
            } else {
                setColor(WHITE);
            }
            // printf("[%d] %s, %s, %s, %s, %s, %s, %s", i + 1, tab[i].prenom, tab[i].nom, tab[i].ville, tab[i].code_postal, tab[i].no_telephone, tab[i].email, tab[i].metier);
            print_user(tab[i], i);
            setDefaultColor();
            printf("\n");
            j++;
        }
    }

    free(substring_lower);
    free(curr_info_lower);
}

/* void recherche_string(user tab[], int taille, char* string, int which) // et affiche
{
    int size_string_lower = strlen(string) + 1;
    char* string_lower = malloc(size_string_lower * sizeof(char));
    char* curr_name_lower = malloc(size_string_lower * sizeof(char));

    strtolower(string_lower, string, size_string_lower);

    for (int i = 0, j = 0; i < taille; i++) {
        strtolower(curr_name_lower, get_arg(&tab[i], which), size_string_lower);
        if (strcmp(curr_name_lower, string_lower) == 0) {
            if (j % 2 == 0) {
                setColor(PURPLE);
            } else {
                setColor(WHITE);
            }
            printf("[%d] %s, %s, %s, %s, %s, %s, %s", i + 1, tab[i].prenom, tab[i].nom, tab[i].ville, tab[i].code_postal, tab[i].no_telephone, tab[i].email, tab[i].metier);
            setDefaultColor();
            printf("\n");
            j++;
        }
    }

    free(string_lower);
    free(curr_name_lower);
} */

void recherche_string_manquante(user tab[], int taille, int which) // et affiche
{
    int count = 0;
    for (int i = 0, j = 0; i < taille; i++) {
        if (get_arg(&tab[i], which)[0] == '\0') {
            count++;
            if (j % 2 == 0) {
                setColor(PURPLE);
            } else {
                setColor(WHITE);
            }
            // printf("[%d] %s, %s, %s, %s, %s, %s, %s", i + 1, tab[i].prenom, tab[i].nom, tab[i].ville, tab[i].code_postal, tab[i].no_telephone, tab[i].email, tab[i].metier);
            print_user(tab[i], i);
            setDefaultColor();
            printf("\n");
            j++;
        }
    }
    setColor(GREEN);
    printf("%d resultat(s) trouve.\n", count);
    setDefaultColor();
}

void recherche_tous_manquante(user tab[], int taille) // et affiche
{
    int count = 0;
    for (int i = 0, j = 0; i < taille; i++) {
        if (get_arg(&tab[i], TRIE_PRENOM)[0] == '\0' || get_arg(&tab[i], TRIE_NOM)[0] == '\0' || get_arg(&tab[i], TRIE_VILLE)[0] == '\0' || get_arg(&tab[i], TRIE_CODE_POSTAL)[0] == '\0' || get_arg(&tab[i], TRIE_NO_TELEPHONE)[0] == '\0' || get_arg(&tab[i], TRIE_EMAIL)[0] == '\0' || get_arg(&tab[i], TRIE_METIER)[0] == '\0') {
            count++;
            if (j % 2 == 0) {
                setColor(PURPLE);
            } else {
                setColor(WHITE);
            }
            // printf("[%d] %s, %s, %s, %s, %s, %s, %s", i + 1, tab[i].prenom, tab[i].nom, tab[i].ville, tab[i].code_postal, tab[i].no_telephone, tab[i].email, tab[i].metier);
            print_user(tab[i], i);
            setDefaultColor();
            printf("\n");
            j++;
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