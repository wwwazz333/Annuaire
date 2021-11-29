#include "tableau.h"
#include <string.h>

void permute(user* a, user* b)
{
    user temp;
    usercpy(&temp, a);
    usercpy(a, b);
    usercpy(b, &temp);
}

void oyelami(user* tab, int taille, char* tri)
{
    int verif_permutation;
    int i=0, sens=1;
    int start=1, end=taille;
    for (i=0;i<=end/2;i++) { //on parcours le tableau dans les deux sens et en même temps
        if (strcmp((char*)&tab[i].nom, (char*)&tab[end - i].nom) > 0) { // comparaison des chaines opposées
                permute(&tab[i],&tab[end - i]); // permutation ces deux chaînes opposées
        }
    }
    i=0;
    do {
        verif_permutation=0;
        while (((sens==1) && (i<end)) || ((sens==-1) && (i>start))) {
            i += sens;
            if (strcmp((char*)&tab[i].nom, (char*)&tab[i-1].nom) < 0) { // comparaison entre deux chaines successives
                permute(&tab[i],&tab[i-1]); // permutation des ces deux chaines successives
                verif_permutation=1;
            }
        }
        if (sens==1) end--; else start++; //changement de sens selon ce qui est déjà trié
        sens = -sens;
    } while (verif_permutation==1);
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
        while (strcmp((char*)&tab[i].nom, (char*)&tab[last].nom) < 0) {
            i += 1;
        }
        while (strcmp((char*)&tab[j].nom, (char*)&tab[last].nom) > 0) {
            j -= 1;
        }
        if (j <= i) {
            break;
        }
        if (strcmp((char*)&tab[i].nom, (char*)&tab[j].nom) == 0) {
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


void add_space(user** tab, int curr_size, int new_size)
{
    user* temp = *tab;
    *tab = malloc(new_size * sizeof(user));
    memcpy(*tab, temp, curr_size * sizeof(user));
    free(temp);
}