#include "floydwarshall.h"
#include "graphe.h"

Mat creer_matrice( Graphe * grph, int nb)
{

    Mat m;
    int i, j;
    m.nbs = nb;
    for (int i = 0; i < nb; i++)
    {
        for (int j = 0; j < nb; j++)
        {
            if (i == j)
                m.mat[i][j] = 0;
            else if( grph->table[i].id)
        }
        
    }
    


    return m;
}

/*

 = (int **)malloc(grph->nbs * sizeof(int *));
    if (!mat)
        EXIT_FAILURE;

    // Initialisation de la matrice
    for (i = 0; i < grph->nbs ; i++)
    {
        (mat)[i] = (int *)malloc(grph->nbs * sizeof(int));
        if (!(mat)[i])
            EXIT_FAILURE;
        for (j = 0; j < grph->nbs; j++)
        {
            if (i == j)
                mat[i][j] = 0;
            else if (grph->adj[i][j] > 0)
                mat[i][j] = grph->adj[i][j];
            else
                mat[i][j] = INF;
        }
    }

} */

/* Algorithme de Floyd-Marshall, avec initialisation de la matrice de départ à partir de la matrice d'adjacence */
int *floydwarshall(Graphe *grph, int src)
{
    int i, j, k;
    // Déclaration d'une matrice

    // Algo de Floyd
    for (k = 0; k < grph->nbs; k++)
    {
        for (i = 0; i < grph->nbs; i++)
        {
            for (j = 0; j < grph->nbs; j++)
            {
                if (mat[i][k] != INF && mat[k][j] != INF && (mat[i][k] + mat[k][j]) < mat[i][j])
                {
                    mat[i][j] = mat[i][k] + mat[k][j];
                }
            }
        }
    }
    return (mat)[src];
}