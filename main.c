#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define DELIM ";\r"
#define BUFF_SIZE 1024

/* Structure de liste d'adjacence */
typedef struct nodeAdjList
{
    int id;                      // id  et index dans la table du graphe
    char *nom;                   // Nom du sommet
    int altitude;                // Altitude du sommet
    struct nodeAdjList *suivant; // Sommet suivant accessible depuis celui-ci
} nodeAdjList;

typedef struct AdjList
{
    int id;                   // id  et index dans la table du graphe
    char *nom;                // Nom du sommet
    int altitude;             // Altitude du sommet
    struct nodeAdjList *tete; // Tete de liste
} AdjList;

typedef enum /* Enum de découpage des cellules du csv */
{
    NOM,
    ALTITUDE,
    NB_CHAMPS
} Column;

typedef enum /* Enum de découpage des cellules du csv */
{
    SRC,
    CIBLE,
    NB_CHAMP
} ColumnBis;

typedef struct graphe /* Structure graphe avec Table de liste adjacentes */
{
    int nbs;
    struct AdjList *table;
} Graphe;

/* Prototypes des fonctions de notre programme */
nodeAdjList *new_nodeAdjList(int num, char *nom, int altitude);
Graphe *newgraph(int n);
void construire_graph(Graphe *graph, const char *acsv);
void ajouterUnArc(Graphe *graph, int src, int dest);
void print_adjlist(Graphe *grph);
void split_row(char *token, char buff[], const char *separator, AdjList *vec, int nli);
Graphe *creer_graph(const char *ccsv, const char *vcsv);

int main()
{

    printf("Liste des cols et villes : \n");

    // Graphe des cols des alpes
    Graphe *graphlpe = creer_graph("Docs/list_cols_alpes.csv", "Docs/list_ville_etapes.csv");
    int n = 0;
    printf("Nombre de sommets : %d \n", graphlpe->nbs);
    while (n < graphlpe->nbs)
    {
        printf("%3d\t%34s\t%6d m\n", graphlpe->table[n].id, graphlpe->table[n].nom, graphlpe->table[n].altitude);
        n++;
    }
    printf("\n");
    construire_graph(graphlpe, "Docs/list_access_cols.csv");
    print_adjlist(graphlpe);

    free(graphlpe);
    return 0;
}

/******************************************
 * Définitions des fonctions du programme *
 *******************************************/

/* Crée un noeud de liste d'adjacence */
nodeAdjList *new_nodeAdjList(int num, char *nom, int altitude)
{
    nodeAdjList *noeud = malloc(sizeof(*noeud));
    assert(noeud);
    noeud->id = num;
    noeud->nom = nom;
    noeud->altitude = altitude;
    noeud->suivant = NULL;
    return noeud;
}

/* Fonction qui crée un graphe vide à n sommets. */
Graphe *newgraph(int n)
{
    Graphe *grph = (Graphe *)malloc(sizeof(Graphe));
    assert(grph);
    grph->nbs = n;
    grph->table = (AdjList *)malloc(n * sizeof(struct AdjList));
    assert(grph->table);
    for (int i = 0; i < n; ++i)
    {
        grph->table[i].id = i;
        grph->table[i].nom = NULL;
        grph->table[i].altitude = 0;
        grph->table[i].tete = NULL;
    }
    return grph;
}

/* Initialise la table du graphe avec les cols et villes des csv */
Graphe *creer_graph(const char *ccsv, const char *vcsv)
{
    Graphe *grph = NULL;
    FILE *fcol = NULL;
    FILE *fvil = NULL;
    char *token = NULL;
    char buff[BUFF_SIZE];
    int c, current_line, nb_lines = 0;

    /* Ouverture de nos fichiers csv en lecture */
    fcol = fopen(ccsv, "r");
    fvil = fopen(vcsv, "r");

    if (!fcol && !fvil)
    {
        printf("Ouverture des fichiers impossible !");
        exit(0);
    }
    else
    {
        /* Compte le nb de ligne dans le fichier */
        while ((c = fgetc(fcol)) != EOF)
        {
            if (c == '\n')
                nb_lines++;
        }

        while ((c = fgetc(fvil)) != EOF)
        {
            if (c == '\n')
                nb_lines++;
        }

        grph = newgraph(nb_lines);

        /* Replacer les pointeurs au début des fichiers */
        fseek(fcol, 0, SEEK_SET);
        fseek(fvil, 0, SEEK_SET);

        current_line = 0; // Ligne courante de lecture du fichier csv

        // lecture ligne -> ligne du csv cols
        while ((fgets(buff, BUFF_SIZE, fcol)) != NULL)
        {
            split_row(token, buff, DELIM, grph->table, current_line);
            current_line++;
        }

        // lecture ligne -> ligne du csv villes
        while ((fgets(buff, BUFF_SIZE, fvil)) != NULL)
        {

            split_row(token, buff, DELIM, grph->table, current_line);
            current_line++;
        }

        fclose(fcol);
        fclose(fvil);
    }
    return grph;
}

void construire_graph(Graphe *graph, const char *acsv)
{
    FILE *facc = NULL;
    char *token = NULL;
    char buff[BUFF_SIZE];
    int src = 0, cible = 0;

    facc = fopen(acsv, "r");

    if (!facc)
    {
        printf("Ouverture du fichier impossible !");
        exit(0);
    }
    else
    {
        // lecture ligne -> ligne du csv cols
        while ((fgets(buff, BUFF_SIZE, facc)) != NULL)
        {
            char *p = buff;
            int i = 0;
            // strtok permet d'extraire les token d'une string specifier par des separators
            while ((token = strtok(p, DELIM)) != NULL)
            {
                if (i == 0)
                    p = NULL;
                switch (i)
                {
                case SRC:
                {
                    // strdup permet de dupliquer une string
                    char *str_source = strdup(token);
                    if(!str_source) exit(0);
                    for (int k = 0; k < graph->nbs; k++)
                    {
                        if (strcmp(str_source, graph->table[k].nom) == 0){
                            src = k;
                        }
                    }
                    free(str_source);
                    break;
                }
                case CIBLE:
                {
                    char *str_cible = strdup(token);
                    if(!str_cible) exit(0);
                    for (int k = 0; k < graph->nbs; k++)
                    {
                        if (strcmp(str_cible, graph->table[k].nom) == 0)
                            cible = k;
                    }
                    free(str_cible);
                    break;
                }
                default:
                    break;
                }
                i++;
            }
            ajouterUnArc(graph, src, cible);
        }
        fclose(facc);
    }
}

// ajouter un arc entre deux sommets
void ajouterUnArc(Graphe *graph, int src, int cible)
{
    assert(graph);
    /** Ajout d'un arc entre un sommet source et un sommet cible
     * Création d'un nouveau noeud de liste adjacente
     */
    nodeAdjList *tmp = NULL;
    nodeAdjList *new_node = new_nodeAdjList(cible, graph->table[cible].nom, graph->table[cible].altitude);
    assert(new_node);

    if (graph->table[src].tete == NULL) // si la liste adjacente est vide
    {
        new_node->suivant = graph->table[src].tete;
        graph->table[src].tete = new_node;
    }
    else // Sinon on parcours la liste adjacente pour ajouter le nouveau noeud
    {
        tmp = graph->table[src].tete; // Pointe sur la tete de la liste
        while (tmp->suivant != NULL)
            tmp = tmp->suivant;  // parcours de liste
        tmp->suivant = new_node; // link du nouveau noeud en fin de liste
    }

    new_node = new_nodeAdjList(src, graph->table[src].nom, graph->table[src].altitude);
    assert(new_node);
    if (graph->table[cible].tete == NULL)
    {
        new_node->suivant = graph->table[cible].tete;
        graph->table[cible].tete = new_node;
    }
    else
    {
        tmp = graph->table[cible].tete;
        while (tmp->suivant != NULL)
        {
            tmp = tmp->suivant;
        }
        tmp->suivant = new_node;
    }
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

/* Fonction qui affiche une liste d'adjacence */
void print_adjlist(struct graphe *grph)
{
    int v;
    for (v = 0; v < grph->nbs; v++)
    {
        nodeAdjList *temp = grph->table[v].tete;
        printf("\n Liste d'adjacence de %d : \n head ", v);
        while (temp != NULL)
        {
            printf("\n -> (%d, %d m)", temp->id, temp->altitude);
            temp = temp->suivant;
        }
        printf("\n");
    }
}

/* split la ligne par séparateur et renvoi un pointeur sur le 1er char de la ligne. */
void split_row(char *token, char buff[], const char *separator, AdjList *vec, int nli)
{
    assert(vec != NULL);
    char *p = buff;
    int i = 0;
    while ((token = strtok(p, separator)) != NULL)
    {
        if (i == 0)
            p = NULL;
        switch (i)
        {
        case NOM:
            vec[nli].nom = strdup(token);
            break;
        case ALTITUDE:
            vec[nli].altitude = strtol(token, NULL, 10);
            break;
        default:
            break;
        }
        i++;
    }
}
