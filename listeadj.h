#ifndef LISTEADJ_H
#define LISTEADJ_H

#include "graph.h"
/* zone protégée contre les inclusions multiples */

/* types =============================================================== */
/* structures ========================================================== */

/* Structure de liste d'adjacence */
typedef struct AdjList
{
    int id;                         // id  et index dans la table du graphe
    char* name;                      // Nom du sommet
    int altitude;                   // Altitude du sommet
    struct AdjList* next;    // Sommet suivant accessible depuis celui-ci
} AdjList;

/* internal public functions =========================================== */

AdjList* adjList_create(int num, char* nom, int altitude);
AdjList* adjList_get(AdjList* list, int id);
int adjList_contains(AdjList* list, int id);
void adjList_print(Graph* graph);
void adjList_print_ids(AdjList* l);

#endif // LISTEADJ_H
