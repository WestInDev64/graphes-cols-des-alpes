#ifndef GRAPHE_H
#define GRAPHE_H
/* zone protégée contre les inclusions multiples */

/* types =============================================================== */
/* structures ========================================================== */

/* Structure graphe avec liste adjacentes */
typedef struct graph
{
    int size;
    struct AdjList* nodes;
} Graph;

/* internal public functions =========================================== */

Graph *graph_parse_nodes(const char *fileName);
void graph_parse_arcs(Graph *graph, const char *acsv);

Graph *graph_create(int n);
void graph_add_arc(Graph *graph, int src, int dest);
int graph_find_index(Graph *graph, char *token);
void graph_print_nodes(Graph * graph);

#endif // GRAPHE_H
