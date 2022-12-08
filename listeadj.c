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
    int res = 0;
    while(l->suivant != NULL){
        if (id == l->id){
            res = 1;
        }
        l = l->suivant;
    }
    return res;
}


int main()
{

    nodeAdjList * node1 = new_nodeadjlist(1,"test1",123);
    nodeAdjList * node2 = new_nodeadjlist(2,"test2",123);
    nodeAdjList * node3 = new_nodeadjlist(3,"test3",123);
    nodeAdjList * node4 = new_nodeadjlist(4,"test4",123);
    nodeAdjList * node5 = new_nodeadjlist(5,"test5",123);

    node5->suivant = node3;
    node3->suivant = node1;
    node1->suivant = node4;
    node4->suivant = node2;

    AdjList * li = (AdjList *) malloc(sizeof(AdjList));
    assert(li);
    li->id = 6;
    li->nom = "Col de test";
    li->altitude = 50;
    li->tete = node5;

    int res = est_membre(li->tete, 2);
    printf("res = %d \n", res);

    assert(est_membre(li->tete,3) == 1);
    assert(est_membre(li->tete,7) == 0);
    assert(est_membre(li->tete,5) == 1);
    assert(est_membre(li->tete,1) == 1);

    free(li);
    return 0;
}

