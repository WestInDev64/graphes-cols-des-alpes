#include "floydwarshall.h"
#include "graphe.h"
#include "listeadj.h"
#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Initialisation de la Matrice,
 * Parcours de la matrice
 * si sommet source == sommet destination -> 0
 * sinon si le sommet destination est un sommet accessible depuis le sommet source
 *       alors on le selectionne et on assigne la valeur de l'altitude
 * sinon on initialise le sommet avec une valeur MAXI INF
 * @param grph : Pointeur de Graphe des sommets
 * @param m : pointeur de Matrice des distances
 * @param pred : pointeur de Matrice des prédécesseurs
 */
void init_matrice(Graphe *grph, Mat *m, Mat *pred)
{
    assert(grph);
    assert(m);
    assert(pred);
    m->nbs = grph->nbs;
    pred->nbs = grph->nbs;
    nodeAdjList *temp = NULL;

    for (int i = 0; i < grph->nbs; i++)
    {
        for (int j = 0; j < grph->nbs; j++)
        {
            if (i == j)
            {
                m->mat[i][j] = 0;
                pred->mat[i][j] = i;
            }
            else if (est_membre(grph->table[i].tete, j) == 1)
            {
                temp = select_node(grph->table[i].tete, j);
                assert(temp);
                m->mat[i][j] = temp->altitude;
                pred->mat[i][j] = i;
            }
            else
            {
                m->mat[i][j] = INF;
                pred->mat[i][j] = -1;
            }
        }
    }
}

/**
 * Algortithme de Floyd Warshall
 * On stocke les distances pour chaque paire de sommet
 * Et on met à jour cette martrice à chaque étape en utilisant
 * la formule du minimum entre la distance du src et dest et k un sommet intermédiaire
 * En d'autres termes la distance entre i et j est égale au minimum de la distance actuelle
 * entre i et j et la distance entre i et k + k et j.
 */
void floydwarshall(Mat *m, Mat *pred)
{
    assert(m);
    assert(pred);
    int i, j, k;
    // Algo de Floyd
    for (k = 0; k < m->nbs; k++)
    {
        for (i = 0; i < m->nbs; i++)
        {
            for (j = 0; j < m->nbs; j++)
            {

                if (m->mat[i][k] != INF && m->mat[k][j] != INF && (m->mat[i][k] + m->mat[k][j]) < m->mat[i][j])
                {
                    m->mat[i][j] = m->mat[i][k] + m->mat[k][j];
                    pred->mat[i][j] = pred->mat[k][j];
                }
            }
        }
    }
}

/**
 * Calcul le dénivelé cumulé positif d'un chemin
 * @param k : Sommet intermédiaire actuel
 * @param grph : Pointeur du graphe (vecteur des sommets)
 * @param predpath : vecteur de sommet des prédecesseurs
*/
int elevation_gain( Graphe *grph,Mat * pred, Path * p)
{
    assert(grph);
    assert(pred);
    assert(p);
    int gain = 0;
    int i;
    int current;
    int next;
    for (i = 0; i < p->size-1; i++)
    {
        current = p->path[i];
        next = p->path[i+1];
        if (grph->table[current].altitude < grph->table[next].altitude)
        {
            gain += grph->table[next].altitude - grph->table[current].altitude;
        }
    }
    return gain;
}

void itineraryAtoB(Mat *pred, int src, int dst, Graphe *grph, Path * p)
{
    assert(pred);
    assert(grph);
    assert(p);
    int i, k;
    int chemin[pred->nbs];

    // Initialisation du vecteur chemin à -1
    for (k = 0; k < pred->nbs; k++)
    {
        chemin[k] = -1;
    }

    k = dst;
    i = 0;
    while (k != src)
    {
        chemin[i] = k;
        k = pred->mat[src][k];
        i++;
    }
    chemin[i] = src;
    
    // Inversement du chemin et initialisation Path
    p->size = i+1;
    p->path = (int*)malloc(sizeof(int)* p->size);
    assert(p->path);
    int j = 0;
    for(k = p->size -1 ; k >= 0 ; k--){
        p->path[j] = chemin[k];
        j++;
    }
}

void print_itinerary(Graphe * grph,Path * p, int src, int dst){
    assert(grph);
    assert(p);
    int k;
    printf("\nVoici le chemin pour aller de 🔰%s à 🏁%s : \n", grph->table[src].nom, grph->table[dst].nom);
    for (k = 0; k < p->size; k++)
    {
        printf(" -> %s - %d m\n", grph->table[p->path[k]].nom, grph->table[p->path[k]].altitude);
    }
}



// écrire les plus courts chemins en consultant les tableaux m et pred
void ecrirePlusCourt(Graphe *graphe, Mat *m, Mat *pred)
{
    printf("\n\nPlus court chemin (Floyd)\n");
    for (int i = 0; i < graphe->nbs; i++)
    {
        printf("pour aller de %s à :\n", graphe->table[i].nom);
        for (int j = 0; j < graphe->nbs; j++)
        {
            if ((i != j) && (m->mat[i][j] != INF))
            {
                printf(" %s (cout = %d) : ",
                       graphe->table[j].nom, m->mat[i][j]);
                int k = pred->mat[i][j];
                printf("%s, %s", graphe->table[j].nom, graphe->table[k].nom);
                while (k != i)
                {
                    k = pred->mat[i][k];
                    printf(", %s ", graphe->table[k].nom);
                }
                printf("\n");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void ecrirePlusCourtUnChemin(Graphe *graphe, Mat *m, Mat *pred, int src)
{

    printf("pour aller de %s à :\n", graphe->table[src].nom);
    for (int j = 0; j < graphe->nbs; j++)
    {
        if ((src != j) && (m->mat[src][j] != INF))
        {
            printf(" %s (cout = %d) : ",
                   graphe->table[j].nom, m->mat[src][j]);
            int k = pred->mat[src][j];
            printf("%s, %s", graphe->table[j].nom, graphe->table[k].nom);
            while (k != src)
            {
                k = pred->mat[src][k];
                printf(", %s ", graphe->table[k].nom);
            }
            printf("\n");
        }
    }
    printf("\n");
}

void print_matrice2D(Mat *m, int lin, int col, int digit)
{
    if (!m)
    {
        printf("Error Ref Matrice NULL \n");
        return;
    }
    int i, j, k;
    // TITLE
    printf("\n/*=====┌ ┐ ─── = ├ ┤ └ ┘ │ =====Affichage Matrice 2D=============*/\n");
    printf("\n\t");

    switch (digit)
    {
    case 2:
        // HEADER
        for (int h = 0; h < col; h++)
        {
            printf("  %02d ", h);
        }
        printf("\n\n");
        for (i = 0; i < lin; i++)
        {
            if (i == 0)
            {
                // TOP LINE
                printf("\t┌");
                for (k = 0; k < (col - 1); k++)
                    printf("────┬");
                printf("────┐\n");
            }
            else
            {
                // INTERSEC LINE
                printf("\n\t├");
                for (k = 0; k < (col - 1); k++)
                    printf("────┼");
                printf("────┤\n");
            }
            printf(" %02d\t│", i);
            for (j = 0; j < col; j++)
            {
                printf(" %4d │", m->mat[i][j]);
            }
        }
        // BOT LINE
        printf("\n\t└");
        for (k = 0; k < (col - 1); k++)
            printf("────┴");
        printf("────┘\n");

        break;

    case 4:
        // HEADER
        for (int h = 0; h < col; h++)
        {
            printf("  %04d ", h);
        }
        printf("\n\n");
        for (i = 0; i < lin; i++)
        {
            if (i == 0)
            {
                // TOP LINE
                printf("\t┌");
                for (k = 0; k < (col - 1); k++)
                    printf("──────┬");
                printf("──────┐\n");
            }
            else
            {
                // mLE LINE
                printf("\n\t├");
                for (k = 0; k < (col - 1); k++)
                    printf("──────┼");
                printf("──────┤\n");
            }
            printf(" %04d\t│", i);

            for (j = 0; j < col; j++)
            {
                printf(" %4d │", m->mat[i][j]);
            }
        }
        // BOTTOM LINE
        printf("\n\t└");
        for (k = 0; k < (col - 1); k++)
            printf("──────┴");
        printf("──────┘\n");

        break;
    case 0:
        // HEADER
        for (int h = 0; h < col; h++)
        {
            printf(" %05d ", h);
        }
        printf("\n\n");
        for (i = 0; i < lin; i++)
        {
            if (i == 0)
            {
                // TOP LINE
                printf("\t");
                for (k = 0; k < (col - 1); k++)
                    printf("-------");
                printf("\n");
            }
            else
            {
                printf("\n");
            }
            printf(" %05d\t|", i);
            for (j = 0; j < col; j++)
            {
                printf(" %5d ", m->mat[i][j]);
            }
        }
        // BOTTOM LINE
        printf("\n\t");
        for (k = 0; k < (col - 1); k++)
            printf("-------");
        printf("\n");

        break;
    default:
        break;
    }
    printf("\n");
}

void print_vector(int *vec, int nb)
{
    if (!vec)
    {
        printf("Error Ref Vector NULL \n");
        return;
    }
    int i, k;
    // TITLE
    printf("\n/* ========================== Affichage Vector ============================= */\n");

    printf("\n");
    // HEADER
    for (int h = 0; h < nb; h++)
    {
        printf("  %04d ", h);
    }
    // TOP LINE
    printf("\n┌");
    for (k = 0; k < (nb - 1); k++)
    {
        printf("──────┬");
    }
    printf("──────┐\n");

    // VECTOR
    printf("│");
    for (i = 0; i < nb; i++)
    {
        printf(" %4d │", vec[i]);
    }

    // BOTTOM LINE
    printf("\n└");
    for (k = 0; k < (nb - 1); k++)
        printf("──────┴");
    printf("──────┘\n");
}

void ecrireEtape(Mat *a, Mat *p, int k, int ns)
{
    if (k == -1)
    {
        printf("Matrices initiales de court et de dernier sommet visité\n");
    }
    else
    {
        printf("Passage par le sommet numéro %d\n", k);
    }
    for (int i = 0; i < ns; i++)
    {
        for (int j = 0; j < ns; j++)
        {
            if (a->mat[i][j] == INF)
            {
                printf(" %3s", "*");
            }
            else
            {
                printf(" %3d", a->mat[i][j]);
            }
        }
        printf("%6s", " ");
        for (int j = 0; j < ns; j++)
        {
            printf("%d", p->mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
