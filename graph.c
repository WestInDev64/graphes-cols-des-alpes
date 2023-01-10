#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "graph.h"
#include "listeadj.h"

/* macros ============================================================== */
/* constants =========================================================== */
#define BUFF_SIZE 1024
#define DELIM ";\r\n"

/*=========================================
 * Définitions des fonctions du programme *
==========================================*/

static void parse_node(char buff[], const char *separator, AdjList *vec, int nli);
static void parse_arc(Graph *graph, const char* separator, char *p);

/* Fonction qui crée un graphe vide à n sommets. */
Graph *graph_create(int n)
{
    Graph *graphe = (Graph *)malloc(sizeof(Graph));
    assert(graphe);
    graphe->size = n;
    graphe->nodes = (AdjList *)malloc(n * sizeof(struct AdjList));
    assert(graphe->nodes);
    for (int i = 0; i < n; ++i)
    {
        graphe->nodes[i].id = i;
        graphe->nodes[i].nom = NULL;
        graphe->nodes[i].altitude = 0;
        graphe->nodes[i].next = NULL;
    }
    return graphe;
}

/* Initialise la table du graphe avec les cols et villes des csv */
Graph *graph_parse_nodes(const char *filename)
{
    Graph *graph = NULL;
    FILE *file = NULL;
    char buff[BUFF_SIZE];
    int c, current_line, nb_lines = 0;

    /* Ouverture de nos fichiers csv en lecture */
    file = fopen(filename, "r");

    if (!file)
    {
        printf("Ouverture du fichier impossible !");
        exit(0);

        return NULL;
    }

    /* Compte le nombre de lignes dans le fichier */
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
            nb_lines++;
    }

    graph = graph_create(nb_lines);

    /* Replacer les pointeurs au début des fichiers */
    fseek(file, 0, SEEK_SET);

    // lecture ligne par ligne
    current_line = 0;
    while ((fgets(buff, BUFF_SIZE, file)) != NULL)
    {
        parse_node(buff, DELIM, graph->nodes, current_line);
        current_line++;
    }

    fclose(file);

    return graph;
}

void graph_parse_arcs(Graph *graph, const char *acsv)
{
    FILE *file = NULL;
    char buff[BUFF_SIZE];

    file = fopen(acsv, "r");

    if (!file)
    {
        printf("Ouverture du fichier impossible !");
        exit(0);

        return;
    }

    // lecture ligne -> ligne du csv "accessibles"
    while ((fgets(buff, BUFF_SIZE, file)) != NULL)
    {
        parse_arc(graph, DELIM, buff);
    }

    fclose(file);
}

// ajouter un arc entre deux sommets
void graph_add_arc(Graph *graph, int src, int dst)
{
    assert(graph);
    int denivele = graph->nodes[dst].altitude - graph->nodes[src].altitude;

    /** Ajout d'un arc entre un sommet source et un sommet cible
     * Création d'un nouveau noeud de liste adjacente
     */
    AdjList *new_node = new_AdjList(dst, graph->nodes[dst].nom, denivele);
    assert(new_node);
    new_node->next = graph->nodes[src].next;
    graph->nodes[src].next = new_node;

    new_node = new_AdjList(src, graph->nodes[src].nom, -denivele);
    assert(new_node);
    new_node->next = graph->nodes[dst].next;
    graph->nodes[dst].next = new_node;
}

/* Comparaison de token de string avec strdup et strcomp */
int graph_find_index(Graph *graph, char *node_name)
{
    assert(graph);
    assert(node_name);
    char *str = strdup(node_name);
    assert(str);

    int result = -1;

    for (int k = 0; k < graph->size; k++)
    {
        if (strcmp(str, graph->nodes[k].nom) == 0)
        {
            result = k;
            break;
        }
    }

    free(str);
    return result;
}

void graph_print_nodes(Graph *graph)
{
    printf("Nombre de sommets : %d \n\n", graph->size);

    for (int n = 0; n < graph->size; n++)
    {
        printf("%3d\t%34s\t%6d m\n",
               graph->nodes[n].id,
               graph->nodes[n].nom,
               graph->nodes[n].altitude);
    }

    printf("\n");
}

/* split la ligne par séparateur et renvoi un pointeur sur le 1er char de la ligne. */
static void parse_node(char buff[], const char *separator, AdjList *vec, int nli)
{
    assert(vec != NULL);

    char* token;
    char* p = buff;

    token = strtok_r(p, separator, &p);
    vec[nli].nom = strdup(token);

    token = strtok_r(p, separator, &p);
    vec[nli].altitude = strtol(token, NULL, 10);
}

static void parse_arc(Graph *graph, const char* separator, char *p)
{
    char* token;
    int src = -1;
    int cible = -1;

    // strtok_r permet d'extraire les token d'une string specifiée par des separators
    token = strtok_r(p, separator, &p);
    src = graph_find_index(graph, token);
    if (src == -1) // si -1 le sommet n'existe pas dans la table
    {
        printf("Erreur: Sommet source \"%s\" inexistant\n", token);
        exit(0);
    }

    token = strtok_r(p, separator, &p);
    cible = graph_find_index(graph, token);
    if (cible == -1) // si -1 le sommet n'existe pas dans la table
    {
        printf("Erreur: Sommet cible \"%s\" inexistant\n", token);
        exit(0);
    }

    graph_add_arc(graph, src, cible);
}