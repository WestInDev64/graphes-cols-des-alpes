#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "listeadj.h"

/* Fichier de test pour tester rapidement des fonctions avant de les implémenter  */


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

    print_list(node5);
    printf("\n");

    int res = est_membre(li->tete, 2);
    printf("res = %d \n", res);

    assert(est_membre(li->tete,3) == 1);
    assert(est_membre(li->tete,7) == 0);
    assert(est_membre(li->tete,5) == 1);
    assert(est_membre(li->tete,1) == 1);



    free(li);
    return 0;
}
