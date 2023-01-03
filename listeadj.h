#ifndef LISTEADJ_H
#define LISTEADJ_H

#include "graphe.h"
/* zone protégée contre les inclusions multiples */

/* types =============================================================== */
/* structures ========================================================== */

/* Structure de liste d'adjacence */
typedef struct nodeAdjList
{
    int id;                         // id  et index dans la table du graphe
    char *nom;                      // Nom du sommet
    int altitude;                   // Altitude du sommet
    struct nodeAdjList *suivant;    // Sommet suivant accessible depuis celui-ci
} nodeAdjList;

typedef struct AdjList
{
    int id;                         // id  et index dans la table du graphe
    char *nom;                      // Nom du sommet
    int altitude;                   // Altitude du sommet
    struct nodeAdjList *tete;       // Tete de liste
} AdjList;


/* internal public functions =========================================== */

nodeAdjList *new_nodeadjlist(int num, char *nom, int altitude);
void affiche_adjlist(Graphe *grph);
int est_membre( nodeAdjList * l, int id);
void print_list(nodeAdjList *l);
nodeAdjList *select_node(nodeAdjList *l, int id);

#endif // LISTEADJ_H
