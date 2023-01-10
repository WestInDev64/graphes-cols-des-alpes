#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "floydwarshall.h"
#include "graph.h"
#include "listeadj.h"

/* Fichier de test pour tester rapidement des fonctions avant de les implémenter  */

int main()
{

    printf("\nListe des cols et villes des Alpes : \n");

    // Graphe des cols des alpes
    Graphe *gralpe = creer_graph("Docs/liste_test.csv", "Docs/liste_test2.csv");

    affiche_liste_sommets(gralpe);

    construire_graph(gralpe, "Docs/liste_test_graphe.csv");

    Mat *mat = (Mat *)malloc(sizeof(Mat));
    assert(mat);
    Mat *pred = (Mat *)malloc(sizeof(Mat));
    assert(pred);

    init_matrice(gralpe, mat, pred);
    floydwarshall(mat, pred);

    int src = 0;
    int dst = 4;

    /* AFFICHAGE */
    affiche_liste_sommets(gralpe);

    Path *p = (Path *)malloc(sizeof(Path));
    assert(p);
    p->size = 0;
    p->path = NULL;

    itineraryAtoB(pred, src, dst, gralpe, p);

    for (int i = 0; i < p->size; i++)
    {
        printf(" %d ", p->path[i]);
    }

    if (mat->mat[src][dst] != INF)
    {
        printf("\nLe dénivelé entre %s et %s est de %d m \n", gralpe->table[src].nom, gralpe->table[dst].nom, mat->mat[src][dst]);
        printf("Le dénivelé cumulé positif de l'itinéraire est de %d m D+ \n", elevation_gain(gralpe, pred, p));
        print_itinerary(gralpe, p, src, dst);
    }
    else
    {
        printf("Malheureusement, %s ne permet pas d'atteindre %s selon les données que nous disposons\n", gralpe->table[src].nom, gralpe->table[dst].nom);
    }

    free(mat);
    free(pred);
    free(p);
    free(gralpe);
    return 0;
}
