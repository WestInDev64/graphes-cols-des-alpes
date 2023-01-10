#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "graphe.h"
#include "listeadj.h"
#include "floydwarshall.h"

int main()
{

    printf("\nListe des cols et villes des Alpes : \n");

    // Graphe des cols des alpes
    Graphe *gralpe = creer_graph("Docs/list_cols_alpes.csv", "Docs/list_ville_etapes.csv");
    construire_graph(gralpe, "Docs/list_access_cols.csv");

    Mat *mat = (Mat *)malloc(sizeof(Mat));
    assert(mat);
    Mat *pred = (Mat *)malloc(sizeof(Mat));
    assert(pred);

    /* ALGO FLOYD-WARSHALL */
    init_matrice(gralpe, mat, pred);
    floydwarshall(mat, pred);

    int src = 142;
    int dst = 138;

    /* AFFICHAGE */
    affiche_liste_sommets(gralpe);

    Path *p = (Path *)malloc(sizeof(Path));
    assert(p);
    p->size = 0;
    p->path = NULL;

    // Calcul l'itinéraire du meilleur chemin à partir de la matrice pred
    itineraryAtoB(pred, src, dst, gralpe, p);

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
