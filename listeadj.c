#include "listeadj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

/* Crée un noeud de liste d'adjacence */
AdjList *new_AdjList(int num, char *nom, int altitude)
{
    AdjList *noeud = malloc(sizeof(*noeud));
    assert(noeud);
    noeud->id = num;
    noeud->nom = nom;
    noeud->altitude = altitude;
    noeud->next = NULL;
    return noeud;
}


/* Fonction qui affiche une liste d'adjacence */
void affiche_adjlist(Graph *graph)
{
    int v;
    for (v = 0; v < graph->size; v++)
    {
        AdjList *temp = graph->nodes[v].next;
        printf("\nListe d'adjacence de %d - %s : \n head ", v, graph->nodes[v].nom);
        while (temp != NULL)
        {
            printf("\n -> (%d \"%s\", deniv: %d m)",
                                    temp->id,
                                    temp->nom,
                                    temp->altitude);
                                    temp = temp->next;
        }
        printf("\n");
    }
}


int est_membre(AdjList * l , int id)
{
    assert(id >= 0);
    while(l != NULL){
        if (id == l->id){
            return 1;
        }
        l = l->next;
    }
    return 0;
}

void print_list(AdjList *l){
    if (l != NULL){
        printf("%d ", l->id);
        print_list(l->next);
    }
}

AdjList * select_node(AdjList *l, int id)
{
    AdjList *temp = NULL;
    int code_success = 0;
    while (l != NULL && code_success == 0)
    {
        if (l->id == id)
        {
            temp = l;
            code_success = 1;
        }
            l = l->next;
    }
    return temp;
}
