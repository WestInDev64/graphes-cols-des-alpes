#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "graph.h"
#include "listeadj.h"
#include "floydwarshall.h"

int main()
{
    // Graphe des cols des alpes
    Graph* graph = graph_parse_nodes("inputs/alpes_noeuds.csv");
    graph_parse_arcs(graph, "inputs/alpes_arcs.csv");

    Mat *mat = (Mat *)malloc(sizeof(Mat));
    assert(mat);
    Mat *pred = (Mat *)malloc(sizeof(Mat));
    assert(pred);

    /* ALGO FLOYD-WARSHALL */
    init_matrice(graph, mat, pred);
    floydwarshall(mat, pred);

    int src = 142;
    int dst = 138;

    /* AFFICHAGE */
    printf("\nListe des cols et villes des Alpes : \n");
    graph_print_nodes(graph);

    Path *p = (Path *)malloc(sizeof(Path));
    assert(p);
    p->size = 0;
    p->path = NULL;

    // Calcul l'itinéraire du meilleur chemin à partir de la matrice pred
    itineraryAtoB(pred, src, dst, graph, p);

    if (mat->mat[src][dst] != INF)
    {
        printf("\nLe dénivelé entre %s et %s est de %d m \n", graph->nodes[src].nom, graph->nodes[dst].nom, mat->mat[src][dst]);
        printf("Le dénivelé cumulé positif de l'itinéraire est de %d m D+ \n", elevation_gain(graph, pred, p));
        print_itinerary(graph, p, src, dst);
    }
    else
    {
        printf("Malheureusement, %s ne permet pas d'atteindre %s selon les données que nous disposons\n", graph->nodes[src].nom, graph->nodes[dst].nom);
    }

    free(mat);
    free(pred);
    free(p);
    free(graph);
    return 0;
}
