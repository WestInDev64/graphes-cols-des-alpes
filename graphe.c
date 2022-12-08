#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "graphe.h"
#include "listeadj.h"


/* macros ============================================================== */
/* constants =========================================================== */
#define BUFF_SIZE 1024
#define DELIM ";\r"


/*=========================================
 * Définitions des fonctions du programme *
==========================================*/

/* Fonction qui crée un graphe vide à n sommets. */
Graphe *new_graph(int n)
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

        grph = new_graph(nb_lines);

        /* Replacer les pointeurs au début des fichiers */
        fseek(fcol, 0, SEEK_SET);
        fseek(fvil, 0, SEEK_SET);

        current_line = 0; // Ligne courante de lecture du fichier csv

        // lecture ligne -> ligne du csv cols
        while ((fgets(buff, BUFF_SIZE, fcol)) != NULL)
        {
            split(token, buff, DELIM, grph->table, current_line);
            current_line++;
        }

        // lecture ligne -> ligne du csv villes
        while ((fgets(buff, BUFF_SIZE, fvil)) != NULL)
        {

            split(token, buff, DELIM, grph->table, current_line);
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
    int src, cible;

    facc = fopen(acsv, "r");

    if (!facc)
    {
        printf("Ouverture du fichier impossible !");
        exit(0);
    }
    else
    {
        // lecture ligne -> ligne du csv "accessibles"
        while ((fgets(buff, BUFF_SIZE, facc)) != NULL)
        {
            char *p = buff;
            int i = 0;
            src = -1;
            cible = -1;
            // strtok permet d'extraire les token d'une string specifier par des separators
            while ((token = strtok(p, DELIM)) != NULL)
            {
                if (i == 0)
                    p = NULL;
                switch (i)
                {
                case SRC:
                {
                    src = compare_token(graph, token);
                    if (src == -1) // si -1 le sommet n'existe pas dans la table
                    {
                        printf("Erreur: Sommet source \"%s\" inexistant\n", token);
                        exit(0);
                    }
                    break;
                }
                case CIBLE:
                {
                    cible = compare_token(graph, token);
                    if (cible == -1) // si -1 le sommet n'existe pas dans la table
                    {
                        printf("Erreur: Sommet cible \"%s\" inexistant\n", token);
                        exit(0);
                    }
                    break;
                }
                default:
                    break;
                }
                i++;
            }
            ajouter_un_arc(graph, src, cible);
        }
        fclose(facc);
    }
}

// ajouter un arc entre deux sommets
void ajouter_un_arc(Graphe *graph, int src, int cible)
{
    assert(graph);
    /** Ajout d'un arc entre un sommet source et un sommet cible
     * Création d'un nouveau noeud de liste adjacente
     */
    int denivele = graph->table[cible].altitude - graph->table[src].altitude;
    nodeAdjList *new_node = new_nodeadjlist(cible, graph->table[cible].nom, denivele);
    assert(new_node);

    /* Pas besoin que la liste soit trié alors autant ajouter le neud en tete de liste */
    new_node->suivant = graph->table[src].tete;
    graph->table[src].tete = new_node;

    denivele = graph->table[src].altitude - graph->table[cible].altitude;
    new_node = new_nodeadjlist(src, graph->table[src].nom, denivele);
    assert(new_node);
    new_node->suivant = graph->table[cible].tete;
    graph->table[cible].tete = new_node;
}

/* split la ligne par séparateur et renvoi un pointeur sur le 1er char de la ligne. */
void split(char *token, char buff[], const char *separator, AdjList *vec, int nli)
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

/* Comparaison de token de string avec strdup et strcomp */
int compare_token(Graphe *graph, char *token)
{
    assert(graph);
    assert(token);
    char *str = strdup(token);
    assert(str);
    int code_retour = 0;
    int result = -1;
    for (int k = 0; (k < graph->nbs) && (code_retour == 0); k++)
    {
        if (strcmp(str, graph->table[k].nom) == 0)
        {
            result = k;
            code_retour = 1;
        }
    }
    free(str);
    return result;
}
