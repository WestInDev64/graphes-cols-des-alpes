#ifndef UTILES_H
#define UTILES_H

#include "graphe.h"

/* zone protégée contre les inclusions multiples */

void affiche_liste_sommets(Graphe * grph);
void print_matrice2D(int **tab, int lin, int col);
void print_dist(int *tab, int size, int s);
void print_acc(int *tab, int size, int s);

#endif // UTILES_H
