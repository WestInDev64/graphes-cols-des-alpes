#ifndef LISTEADJ_H
#define LISTEADJ_H

#include "graphe.h"
/* zone protégée contre les inclusions multiples */

/* types =============================================================== */
/* structures ========================================================== */

/* Structure de liste d'adjacence */
typedef struct AdjList
{
    int id;                         // id  et index dans la table du graphe
    char *nom;                      // Nom du sommet
    int altitude;                   // Altitude du sommet
    struct AdjList *suivant;    // Sommet suivant accessible depuis celui-ci
} AdjList;


/* internal public functions =========================================== */

AdjList *new_AdjList(int num, char *nom, int altitude);
void affiche_adjlist(Graphe *grph);
int est_membre( AdjList * l, int id);
void print_list(AdjList *l);
AdjList *select_node(AdjList *l, int id);

#endif // LISTEADJ_H
