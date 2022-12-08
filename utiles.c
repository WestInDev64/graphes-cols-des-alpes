#include "utiles.h"
#include "listeadj.h"
#include <stdio.h>

void affiche_liste_sommets(Graphe * grph) {
    printf("Nombre de sommets : %d \n\n",grph->nbs);
    int n = 0;
    while (n < grph->nbs)
    {
        printf("%3d\t%34s\t%6d m\n", 
            grph->table[n].id, 
            grph->table[n].nom, 
            grph->table[n].altitude);
        n++;
    }
    printf("\n");
}

void print_matrice2D(int **tab, int lin, int col)
{
    if (!tab)
    {
        printf("Ref Graphe NULL \n");
        return;
    }
    int i, j, k;
    // TITLE
    printf("\n/*=====┌ ┐ ─── = ├ ┤ └ ┘ │ =====Affichage Matrice 2D=============*/\n");
    printf("\n\t");
    // HEADER
    for (int h = 0; h < col; h++)
        printf("  %02d ", h);
    printf("\n\n\n");
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
            printf(" %4d │", tab[i][j]);
        }
    }
    // BOT LINE
    printf("\n\t└");
    for (k = 0; k < (col - 1); k++)
        printf("────┴");
    printf("────┘\n");
    printf("\n");
}

/* Fonctions qui affiche les tableaux des accessibles et des distances */
void print_acc(int *tab, int size, int s)
{
    int i;
    printf("Sommets : \t \t");
    for (i = 0; i < size; i++)
    {
        printf("%d", i);
        printf(i < size - 1 ? "\t" : "\n");
    }
    printf("Acc. depuis %d : \t", s);
    for (i = 0; i < size; i++)
    {
        printf("%d", tab[i]);
        printf(i < size - 1 ? "\t" : "\n");
    }
}

void print_dist(int *tab, int size, int s)
{
    int i;
    printf("Sommets : \t \t");
    for (i = 0; i < size; i++)
    {
        printf("%d", i);
        printf(i < size - 1 ? "\t" : "\n");
    }
    printf("Dist. depuis %d : \t", s);
    for (i = 0; i < size; i++)
    {
        printf("%d", tab[i]);
        printf(i < size - 1 ? "\t" : "\n");
    }
}
