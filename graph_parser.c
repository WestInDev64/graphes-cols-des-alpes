#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "graph_parser.h"
#include "listeadj.h"

// Static functions headers

static Graph* parse_graph_nodes(const char *fileName);
static void parse_graph_arcs(Graph *graph, const char *acsv);
static void parse_node(char buff[], const char *separator, AdjList *vec, int nli);
static void parse_arc(Graph *graph, const char* separator, char *p);

// Functions

Graph* parse_graph(const char* nodes_filename, const char* arcs_filename)
{
    Graph* graph = parse_graph_nodes(nodes_filename);
    parse_graph_arcs(graph, arcs_filename);

    return graph;
}

/* Initialise la table du graphe avec les cols et villes des csv */
static Graph *parse_graph_nodes(const char *filename)
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

static void parse_graph_arcs(Graph *graph, const char *acsv)
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

/* split la ligne par séparateur et renvoi un pointeur sur le 1er char de la ligne. */
static void parse_node(char buff[], const char *separator, AdjList *vec, int nli)
{
    assert(vec != NULL);

    char* token;
    char* p = buff;

    token = strtok_r(p, separator, &p);
    vec[nli].name = strdup(token);

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