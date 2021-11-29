#include "tableau.h"

#include "Verif.h"
#include <string.h>

void permute(user* a, user* b)
{
    user temp;
    usercpy(&temp, a);
    usercpy(a, b);
    usercpy(b, &temp);
}

void quick_sort(user* tab, int first, int last)
{
    if (last <= first) {
        return;
    }
    int i, j;

    char* name_lower_i = malloc((64 + 1) * sizeof(char)); // 64 car c'est le nom !!!!!! à changer
    char* name_lower_j = malloc((64 + 1) * sizeof(char)); // 64 car c'est le nom !!!!!! à changer
    char* name_lower_last = malloc((64 + 1) * sizeof(char)); // 64 car c'est le nom !!!!!! à changer

    int pivot = (first + last - 1) / 2;
    // met le pivot en fin de chaine
    permute(&tab[pivot], &tab[last]);

    i = first;
    j = last - 1;
    strtolower(name_lower_last, tab[last].nom, 64);

    while (1) {
        strtolower(name_lower_i, tab[i].nom, 64);
        strtolower(name_lower_j, tab[j].nom, 64);
        while (strcmp(name_lower_i, name_lower_last) < 0) {
            i++;
            strtolower(name_lower_i, tab[i].nom, 64);
        }
        while (strcmp(name_lower_j, name_lower_last) > 0) {
            j--;
            strtolower(name_lower_j, tab[j].nom, 64);
        }
        if (j <= i) {
            break;
        }
        if (strcmp(name_lower_i, name_lower_j) == 0) {
            i++;
            j--;
            strtolower(name_lower_i, tab[i].nom, 64);
            strtolower(name_lower_j, tab[j].nom, 64);
            continue;
        }

        permute(&tab[i], &tab[j]);
    }
    free(name_lower_i);
    free(name_lower_j);
    free(name_lower_last);
    // remet le pivot au bonne endroit
    permute(&tab[i], &tab[last]);

    // partie gauche
    quick_sort(tab, first, i - 1);
    // partie droite
    quick_sort(tab, i + 1, last);
}

void add_space(user** tab, int curr_size, int new_size)
{
    user* temp = *tab;
    *tab = malloc(new_size * sizeof(user));
    memcpy(*tab, temp, curr_size * sizeof(user));
    free(temp);
}