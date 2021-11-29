#include "tableau.h"
#include <string.h>

void permute(user* a, user* b)
{
    user temp;
    usercpy(&temp, a);
    usercpy(a, b);
    usercpy(b, &temp);
}
void oyelami(user* tab, int taille)
{
    int permutation;
    int en_cours=0, sens=1;
    int debut=1, fin=taille;
    printf("cc toi");
    for (en_cours=0;en_cours<=fin/2;en_cours++) {
        if (strcmp((char*)&tab[en_cours].nom, (char*)&tab[fin - en_cours].nom) > 0) { //tab[en_cours]>tab[fin - en_cours]
                permute(&tab[en_cours],&tab[fin - en_cours]);
                // user temp = tab[en_cours];
                // tab[en_cours] = tab[fin - en_cours];
                // tab[fin - en_cours] = temp;        
        }
    }
    en_cours=0;
    do {
        permutation=0;
        while (((sens==1) && (en_cours<fin)) || ((sens==-1) && (en_cours>debut))) {
            en_cours += sens;
            if (strcmp((char*)&tab[en_cours].nom, (char*)&tab[en_cours-1].nom) < 0) { // tab[en_cours] < tab[en_cours-1]
                permute(&tab[en_cours],&tab[en_cours-1]);
                // user temp = tab[en_cours];
                // tab[en_cours] = tab[en_cours-1];
                // tab[en_cours-1]=temp;
                permutation=1;
            }
        }
        if (sens==1) fin--; else debut++;
        sens = -sens;
    } while (permutation==1);
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