#include "listeadj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

/* Crée un noeud de liste d'adjacence */
nodeAdjList *new_nodeadjlist(int num, char *nom, int altitude)
{
    nodeAdjList *noeud = malloc(sizeof(*noeud));
    assert(noeud);
    noeud->id = num;
    noeud->nom = nom;
    noeud->altitude = altitude;
    noeud->suivant = NULL;
    return noeud;
}


/* Fonction qui affiche une liste d'adjacence */
void affiche_adjlist(Graphe *grph)
{
    int v;
    for (v = 0; v < grph->nbs; v++)
    {
        nodeAdjList *temp = grph->table[v].tete;
        printf("\nListe d'adjacence de %d - %s : \n head ", v, grph->table[v].nom);
        while (temp != NULL)
        {
            printf("\n -> (%d \"%s\", deniv: %d m)", 
                                    temp->id, 
                                    temp->nom, 
                                    temp->altitude);
                                    temp = temp->suivant;
        }
        printf("\n");
    }
}


int est_membre( nodeAdjList * l , int id)
{
    assert(l);
    assert(id >= 0);
    while(l != NULL){
        if (id == l->id){
            return 1;
        }
        l = l->suivant;
    }
    return 0;
}

void print_list(nodeAdjList *l){
    if (l != NULL){
        printf("%d ", l->id);
        print_list(l->suivant);
    }
}


