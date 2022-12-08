#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "graphe.h"
#include "utiles.h"
#include "listeadj.h"

int main()
{

    printf("\nListe des cols et villes des Alpes : \n");

    // Graphe des cols des alpes
    Graphe *gralpe = creer_graph("Docs/list_cols_alpes.csv", "Docs/list_ville_etapes.csv");

    affiche_liste_sommets(gralpe);

    construire_graph(gralpe, "Docs/list_access_cols.csv");

    affiche_adjlist(gralpe);

    free(gralpe);
    return 0;
}
