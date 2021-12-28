#include "tableau.h"

#include "Terminal.h"
#include "Verif.h"

void permute(user* a, user* b)
{
    if (a == NULL || b == NULL) {
        return;
    }
    user temp;
    usercpy(&temp, a);
    usercpy(a, b);
    usercpy(b, &temp);
}

void oyelami(user* tab, int taille, TrierSur which)
{
    int verif_permutation;
    int i = 0, sens = 1;
    int start = 1, end = taille;

    int size_of_string = get_size_arg(which);
    char* lower_i = malloc((size_of_string + 1) * sizeof(char));
    char* lower_j = malloc((size_of_string + 1) * sizeof(char));

    for (i = 0; i <= end / 2; i++) { // on parcours le tableau dans les deux sens et en même temps
        strtolower(lower_i, get_arg(&tab[i], which), size_of_string);
        strtolower(lower_j, get_arg(&tab[end - i], which), size_of_string);
        if (string_cmp(lower_i, lower_j) > 0) { // comparaison des chaines opposées
            permute(&tab[i], &tab[end - i]); // permutation ces deux chaînes opposées
        }
    }
    i = 0;
    do {
        verif_permutation = 0;
        while (((sens == 1) && (i < end)) || ((sens == -1) && (i > start))) {
            i += sens;
            strtolower(lower_i, get_arg(&tab[i], which), size_of_string);
            strtolower(lower_j, get_arg(&tab[i - 1], which), size_of_string);
            if (string_cmp(lower_i, lower_j) < 0) { // comparaison entre deux chaines successives
                permute(&tab[i], &tab[i - 1]); // permutation des ces deux chaines successives
                verif_permutation = 1;
            }
        }
        if (sens == 1)
            end--;
        else
            start++; // changement de sens selon ce qui est déjà trié
        sens = -sens;
    } while (verif_permutation == 1);

    free(lower_i);
    free(lower_j);
}

void quick_sort(user* tab, int first, int last, TrierSur which)
{
    if (last <= first) {
        return;
    }

    int i, j;
    int size_of_string = get_size_arg(which);
    char* lower_i = malloc((size_of_string + 1) * sizeof(char));
    char* lower_j = malloc((size_of_string + 1) * sizeof(char));
    char* lower_last = malloc((size_of_string + 1) * sizeof(char));

    int pivot = (first + last - 1) / 2;
    // met le pivot en fin de chaine
    permute(&tab[pivot], &tab[last]);

    i = first;
    j = last - 1;
    strtolower(lower_last, get_arg(&tab[last], which), size_of_string);
    while (1) {
        strtolower(lower_i, get_arg(&tab[i], which), size_of_string);
        strtolower(lower_j, get_arg(&tab[j], which), size_of_string);
        while (string_cmp(lower_i, lower_last) < 0 && i <= last) {
            i++;
            strtolower(lower_i, get_arg(&tab[i], which), size_of_string);
        }
        while (string_cmp(lower_j, lower_last) > 0 && j > i) {
            j--;
            strtolower(lower_j, get_arg(&tab[j], which), size_of_string);
        }

        if (j <= i) {
            break;
        }
        if (string_cmp(lower_i, lower_j) == 0) {
            i++;
            j--;
            strtolower(lower_i, get_arg(&tab[i], which), size_of_string);
            strtolower(lower_j, get_arg(&tab[j], which), size_of_string);
            continue;
        }

        permute(&tab[i], &tab[j]);
    }
    free(lower_i);
    free(lower_j);
    free(lower_last);
    // remet le pivot au bonne endroit
    permute(&tab[i], &tab[last]);

    // partie gauche
    quick_sort(tab, first, i - 1, which);
    // partie droite
    quick_sort(tab, i + 1, last, which);
}

void add_space(user** tab, int curr_size, int new_size)
{
    user* temp = *tab;
    *tab = malloc(new_size * sizeof(user));
    memcpy(*tab, temp, curr_size * sizeof(user));
    free(temp);
}

void print_tab(user* tab, int size_tab)
{
    int i;
    setDefaultColor();
    printf("\n");
    for (i = 0; i < size_tab; i++) {
        if (i % 2 == 0) {
            setColor(PURPLE);
        } else {
            setColor(WHITE);
        }
        print_user(tab[i], i);
        setDefaultColor();
        printf("\n");
    }
}

void print_tab_sect(user* tab, int size_tab, int section) {
    int i;
    setDefaultColor();
    printf("\n");
    for (i = 0; i < size_tab; i++) {
        if (i % 2 == 0) {
            setColor(PURPLE);
        } else {
            setColor(WHITE);
        }
        print_user(tab[i], i);
        setDefaultColor();
        printf("\n");
        if ((i+1)%(section) == 0 && i !=0) {
            setColor(YELLOW);
            printf("\n[%d/%d] ",i+1,size_tab);
            print(GREY, DEFAULT_BACKGROUND_COLOR, "Appuyer sur Entrer pour continuer ou 0 pour quitter... ");
            int c;
            setColor(AQUA);
            while((c = getchar()) != '\n' && c != '0'){}
            setDefaultColor();
            if (c=='0') {
                print(RED,DEFAULT_BACKGROUND_COLOR, "Annulation");
                printf("\n");
                break;
            }
        }
    }
}