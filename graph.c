#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "graph.h"
#include "listeadj.h"

/*=========================================
 * Définitions des fonctions du programme *
==========================================*/

/* Fonction qui crée un graphe vide à n sommets. */
Graph *graph_create(int n)
{
    Graph *graphe = (Graph *)malloc(sizeof(Graph));
    assert(graphe);
    graphe->size = n;
    graphe->nodes = (AdjList *)malloc(n * sizeof(struct AdjList));
    assert(graphe->nodes);
    for (int i = 0; i < n; ++i)
    {
        graphe->nodes[i].id = i;
        graphe->nodes[i].nom = NULL;
        graphe->nodes[i].altitude = 0;
        graphe->nodes[i].next = NULL;
    }
    return graphe;
}

// ajouter un arc entre deux sommets
void graph_add_arc(Graph *graph, int src, int dst)
{
    assert(graph);
    int denivele = graph->nodes[dst].altitude - graph->nodes[src].altitude;

    /** Ajout d'un arc entre un sommet source et un sommet cible
     * Création d'un nouveau noeud de liste adjacente
     */
    AdjList *new_node = new_AdjList(dst, graph->nodes[dst].nom, denivele);
    assert(new_node);
    new_node->next = graph->nodes[src].next;
    graph->nodes[src].next = new_node;

    new_node = new_AdjList(src, graph->nodes[src].nom, -denivele);
    assert(new_node);
    new_node->next = graph->nodes[dst].next;
    graph->nodes[dst].next = new_node;
}

/* Comparaison de token de string avec strdup et strcomp */
int graph_find_index(Graph *graph, char *node_name)
{
    assert(graph);
    assert(node_name);
    char *str = strdup(node_name);
    assert(str);

    int result = -1;

    for (int k = 0; k < graph->size; k++)
    {
        if (strcmp(str, graph->nodes[k].nom) == 0)
        {
            result = k;
            break;
        }
    }

    free(str);
    return result;
}

void graph_print_nodes(Graph *graph)
{
    printf("Nombre de sommets : %d \n\n", graph->size);

    for (int n = 0; n < graph->size; n++)
    {
        printf("%3d\t%34s\t%6d m\n",
               graph->nodes[n].id,
               graph->nodes[n].nom,
               graph->nodes[n].altitude);
    }

    printf("\n");
}