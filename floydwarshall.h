#ifndef FLOYDWARSHALL_H
#define FLOYDWARSHALL_H

#include "graphe.h"

#define MAXMAT 256

typedef int matrice[MAXMAT][MAXMAT];

typedef struct mat
{
    int nbs;
    matrice mat;
} Mat;



int *floydwarshall(Graphe *grph, int src);
Mat creer_matrice(Graphe *grph, int nb);

#endif // FLOYDWAGraphe_H
#endif // FLOYDWARSHALL_H#include "graphe.h"

