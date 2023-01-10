#include "listeadj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

/* Crée un noeud de liste d'adjacence */
AdjList* adjList_create(int id, char* name, int altitude)
{
    AdjList* node = malloc(sizeof(*node));
    assert(node);
    node->id = id;
    node->name = name;
    node->altitude = altitude;
    node->next = NULL;
    return node;
}

AdjList* adjList_get(AdjList* list, int id)
{
    assert(id >= 0);
    while (list != NULL)
    {
        if (list->id == id)
        {
            return list;
        }
        list = list->next;
    }
    return NULL;
}

int adjList_contains(AdjList* list, int id)
{
    return adjList_get(list, id) == NULL ? 0 : 1;
}

/* Fonction qui affiche une liste d'adjacence */
void adjList_print(Graph *graph)
{
    for (int v = 0; v < graph->size; v++)
    {
        AdjList *temp = graph->nodes[v].next;
        printf("\nListe d'adjacence de %d - %s : \n head ", v, graph->nodes[v].name);
        while (temp != NULL)
        {
            printf("\n -> (%d \"%s\", deniv: %d m)",
                   temp->id,
                   temp->name,
                   temp->altitude);
            temp = temp->next;
        }
        printf("\n");
    }
}

void adjList_print_ids(AdjList* list)
{
    while (list != NULL)
    {
        printf("%d ", list->id);
        list = list->next;
    }
}
