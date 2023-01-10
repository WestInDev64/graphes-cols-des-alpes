#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "listeadj.h"

/* Fichier de test pour tester rapidement des fonctions avant de les implémenter  */


int main()
{

    AdjList *node1 = new_AdjList(1, "test1", 123);
    AdjList *node2 = new_AdjList(2, "test2", 123);
    AdjList *node3 = new_AdjList(3, "test3", 123);
    AdjList *node4 = new_AdjList(4, "test4", 123);
    AdjList *node5 = new_AdjList(5, "test5", 123);

    node5->suivant = node3;
    node3->suivant = node1;
    node1->suivant = node4;
    node4->suivant = node2;

    AdjList *li = (AdjList *)malloc(sizeof(AdjList));
    assert(li);
    li->id = 6;
    li->nom = "Col de test";
    li->altitude = 50;
    li->suivant = node5;

    print_list(node5);
    printf("\n");

    int res = est_membre(li->suivant, 2);
    printf("res = %d \n", res);



    AdjList * memberlist = select_node(node5, 2);
    assert(memberlist);
    int id = memberlist->id;
    printf("id noeud selectionné: %d \n", id);

    assert(est_membre(li->suivant, 3) == 1);
    assert(est_membre(li->suivant, 7) == 0);
    assert(est_membre(li->suivant, 5) == 1);
    assert(est_membre(li->suivant, 1) == 1);
    assert(id == 2);

    free(li);
    return 0;
}
