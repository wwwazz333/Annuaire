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

    char* lower_i = malloc((64 + 1) * sizeof(char)); // 64 car c'est le nom !!!!!! à changer
    char* lower_j = malloc((64 + 1) * sizeof(char)); // 64 car c'est le nom !!!!!! à changer
    char* lower_last = malloc((64 + 1) * sizeof(char)); // 64 car c'est le nom !!!!!! à changer

    int pivot = (first + last - 1) / 2;
    // met le pivot en fin de chaine
    permute(&tab[pivot], &tab[last]);

    i = first;
    j = last - 1;
    strtolower(lower_last, tab[last].nom, 64);

    while (1) {
        strtolower(lower_i, tab[i].nom, 64);
        strtolower(lower_j, tab[j].nom, 64);
        while (strcmp(lower_i, lower_last) < 0) {
            i++;
            strtolower(lower_i, tab[i].nom, 64);
        }
        while (strcmp(lower_j, lower_last) > 0) {
            j--;
            strtolower(lower_j, tab[j].nom, 64);
        }
        if (j <= i) {
            break;
        }
        if (strcmp(lower_i, lower_j) == 0) {
            i++;
            j--;
            strtolower(lower_i, tab[i].nom, 64);
            strtolower(lower_j, tab[j].nom, 64);
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
    quick_sort(tab, first, i - 1);
    // partie droite
    quick_sort(tab, i + 1, last);
}
void quick_sort_on(user* tab, int first, int last, TrierSur which)
{
    if (last <= first) {
        return;
    }
    int i, j;
    int size_of_string = strlen(get_arg(&tab[0], which));
    char* lower_i = malloc((size_of_string + 1) * sizeof(char));
    char* lower_j = malloc((size_of_string + 1) * sizeof(char));
    char* lower_last = malloc((size_of_string + 1) * sizeof(char));

    int pivot = (first + last - 1) / 2;
    // met le pivot en fin de chaine
    permute(&tab[pivot], &tab[last]);

    i = first;
    j = last - 1;
    strtolower(lower_last, get_arg(&tab[last], which), 64);

    while (1) {
        strtolower(lower_i, get_arg(&tab[i], which), 64);
        strtolower(lower_j, get_arg(&tab[j], which), 64);
        while (strcmp(lower_i, lower_last) < 0) {
            i++;
            strtolower(lower_i, get_arg(&tab[i], which), 64);
        }
        while (strcmp(lower_j, lower_last) > 0) {
            j--;
            strtolower(lower_j, get_arg(&tab[j], which), 64);
        }

        if (j <= i) {
            break;
        }
        if (strcmp(lower_i, lower_j) == 0) {
            i++;
            j--;
            strtolower(lower_i, get_arg(&tab[i], which), 64);
            strtolower(lower_j, get_arg(&tab[j], which), 64);
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
    quick_sort_on(tab, first, i - 1, which);
    // partie droite
    quick_sort_on(tab, i + 1, last, which);
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
    for (i = 0; i < size_tab; i++) {
        if (i % 2 == 0) {
            setColor(PURPLE);
        } else {
            setColor(WHITE);
        }
        printf("[%d] %s, %s, %s, %s, %s, %s, %s", i + 1, tab[i].prenom, tab[i].nom, tab[i].ville, tab[i].code_postal, tab[i].no_telephone, tab[i].email, tab[i].metier);
        setDefaultColor();
        printf("\n");
    }
}