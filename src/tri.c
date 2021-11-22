#include "tri.h"

void permute(user* a, user* b)
{
    user temp;
    // usercpy(&temp, a);
    // usercpy(a, b);
    // usercpy(b, &temp);
    memcpy(&temp, a, sizeof(user));
    memcpy(a, b, sizeof(user));
    memcpy(b, &temp, sizeof(user));
}

void quick_sort(user* tab, int first, int last)
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
        while (strcmp(&tab[i].nom, &tab[last].nom) < 0) {
            i += 1;
        }
        while (strcmp(&tab[j].nom, &tab[last].nom) > 0) {
            j -= 1;
        }
        if (j <= i) {
            break;
        }
        if (strcmp(&tab[i].nom, &tab[j].nom) == 0) {
            i++;
            j--;
            continue;
        }

        permute(&tab[i], &tab[j]);
    }
    // remet le pivot au bonne endroit
    permute(&tab[i], &tab[last]);

    // partie gauche
    quick_sort(tab, first, i - 1);
    // partie droite
    quick_sort(tab, i + 1, last);
}