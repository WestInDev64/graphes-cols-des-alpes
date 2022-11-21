#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

typedef struct col
{
    char *nom;
    int poids;
} Col_t;

typedef struct graph
{
    int nbs;
    int *vec;
} Graph_t;

Graph_t creegraphe(int nbs);
int voir(Graph_t g, int i, int j);
void placer(Graph_t g, int i, int j, int val);
void voirgraf(Graph_t g);

int main()
{
    Graph_t g = creegraphe(25);
    voirgraf(g);
    //voir(g, 9, 9);
    return 0;
}

Graph_t creegraphe(int nbs)
{
    int i, j, max, num;
    float v, taux;
    Graph_t g;
    g.nbs = nbs;
    max = nbs * nbs;
    taux = 25.0;
    num = nbs / 10;

    while (num > 1)
    {
        num /= 5;
        taux /= 3.0;
    }
    taux /= 100.0;
    printf("taux %g\n", taux);
    g.vec = (int *)malloc(max * sizeof(int));
    if (!g.vec)
        exit(1);
    memset(g.vec, 0, max);
    srand(time(NULL));
    for (num = 0, i = 0; i < nbs; i++)
    {
        for (j = 0; j < nbs; j++)
        {
            v = (float)rand() / RAND_MAX;
            g.vec[num++] = v < taux ? (int)(v * 1000.) : 0;
        }
    }
    return g;
}

void voirgraf(Graph_t g)
{
    int i, j, nb, num;
    nb = g.nbs;
    printf("Graphe\n");
    for (i = 0, num = 0; i < nb; i++)
    {
        for (j = 0; j < nb; j++)
            printf("%c ", g.vec[num++] ? '1' : ' ');
        printf("\n");
    }
}
