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

    for (i = 0; i <= end / 2; i++) { // on parcours le tableau dans les deux sens et en même temps
        if (string_cmp(get_arg(&tab[i], which), get_arg(&tab[end - i], which)) > 0) { // comparaison des chaines opposées
            permute(&tab[i], &tab[end - i]); // permutation ces deux chaînes opposées
        }
    }
    i = 0;
    do {
        verif_permutation = 0;
        while (((sens == 1) && (i < end)) || ((sens == -1) && (i > start))) {
            i += sens;
            if (string_cmp(get_arg(&tab[i], which), get_arg(&tab[i - 1], which)) < 0) { // comparaison entre deux chaines successives
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
}

void quick_sort(user* tab, int first, int last, TrierSur which)
{
    if (last <= first) {
        return;
    }

    int i, j;
    int pivot = (first + last - 1) / 2;
    // met le pivot en fin de chaine
    permute(&tab[pivot], &tab[last]);

    i = first;
    j = last - 1;
    while (1) {
        while (i <= last && string_cmp(get_arg(&tab[i], which), get_arg(&tab[last], which)) < 0) {
            i++;
        }
        while (j > i && string_cmp(get_arg(&tab[j], which), get_arg(&tab[last], which)) > 0) {
            j--;
        }

        if (j <= i) {
            break;
        }
        if (string_cmp(get_arg(&tab[i], which), get_arg(&tab[j], which)) == 0) {
            i++;
            j--;
            continue;
        }

        permute(&tab[i], &tab[j]);
    }

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
    }
}

void print_tab_sect(user* tab, int size_tab, int section)
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
        if ((i + 1) % (section) == 0 && i != 0) {
            setColor(YELLOW);
            printf("\n[%d/%d] ", i + 1, size_tab);
            print("Appuyer sur Entrer pour continuer ou 0 pour quitter... ", GREY, DEFAULT_BACKGROUND_COLOR);
            int c;
            setColor(AQUA);
            while ((c = getchar()) != '\n' && c != '0') { }
            setDefaultColor();
            if (c == '0') {
                print("Annulation\n", RED, DEFAULT_BACKGROUND_COLOR);
                break;
            }
        }
    }
}