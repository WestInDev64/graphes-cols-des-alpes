#ifndef GRAPHE_H
#define GRAPHE_H
/* zone protégée contre les inclusions multiples */

/* types =============================================================== */
/* structures ========================================================== */

/* Structure graphe avec liste adjacentes */
typedef struct graphe
{
    int nbs;
    struct AdjList *table;
} Graphe;

/* Enum de découpage des cellules du csv */
typedef enum
{
    NOM,
    ALTITUDE,
    NB_CHAMPS
} Column;

/* Enum de découpage des cellules du csv */
typedef enum
{
    SRC,
    CIBLE,
    NB_CHAMP
} ColumnBis;


/* internal public functions =========================================== */

Graphe *new_graph(int n);
Graphe *creer_graph(const char *ccsv, const char *vcsv);
void construire_graph(Graphe *graph, const char *acsv);
void ajouter_un_arc(Graphe *graph, int src, int dest);
void split(char *token, char buff[], const char *separator, struct AdjList *vec, int nli);
int compare_token(Graphe *graph, char *token);
void affiche_liste_sommets(Graphe * grph);

#endif // GRAPHE_H
