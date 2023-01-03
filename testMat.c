#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "floydwarshall.h"
#include "graphe.h"
#include "listeadj.h"


/* Fichier de test pour tester rapidement des fonctions avant de les implémenter  */


int main()
{

    printf("\nListe des cols et villes des Alpes : \n");

    // Graphe des cols des alpes
    Graphe *gralpe = creer_graph("Docs/list_cols_alpes.csv", "Docs/list_ville_etapes.csv");

    affiche_liste_sommets(gralpe);

    construire_graph(gralpe, "Docs/list_access_cols.csv");

    Mat * mat = (Mat *)malloc(sizeof(Mat));
    assert(mat);
    Mat * pred = (Mat *)malloc(sizeof(Mat));
    assert(pred);

    init_matrice(gralpe,mat,pred);
    floydwarshall(mat, pred);

    int src = 142;
    int dst = 52;

    //print_matrice2D(mat , gralpe->nbs, gralpe->nbs, 0);
    printf("Le dénivelé minimisé entre %s et %s est de %d m \n", gralpe->table[src].nom, gralpe->table[dst].nom, mat->mat[src][dst]);
    //print_vector(mat->mat[31], mat->nbs);
    //ecrirePlusCourt(gralpe,mat,pred);

    itineraryAtoB(pred, src,dst, gralpe);

    //ecrirePlusCourtUnChemin(gralpe,mat,pred,src);
    //print_itinerary(pred, src, dst, gralpe);
    
    free(gralpe);
    free(mat);
    free(pred);
    return 0;
}
