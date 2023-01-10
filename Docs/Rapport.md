# Brouillon de Rapport de projet

choix faits, 
problèmes rencontrés,
code d’illustration, 
mode d’emploi,
exemple d’utilisation, discussion ...

// Créer un fichier texte en listant les cols des Alpes

Le nb de cols
Le nom du col en tant que sommet destination
Lé départ en tant que sommet intermédiaire

Les arcs de poids négatifs ou positifs selon le dénivelé


## Etablir un peu plus de connexité entre les cols

Gros travail de recherche à l'aide de Google Map et d'itinéraire cycliste pour définir un peu plus de connexité entre les cols des alpes.

## Lire et extraire les données de mes fichiers csv

Manipulation de fichier à l'aide des fonctions de la lib string.h
à refactoriser dès que possible.

Ancienne structure avant d'introduire le type liste:

```c
typedef struct sommet
{
    int id;
    char *nom;
    int altitude;
} Sommet;

typedef struct vec_sommet
{
    Sommet *s;
    int nb_sommet;
} Vec_sommet_t;

typedef enum /* Découpage des cellules du csv */
{
    NOM,
    ALTITUDE,
    NB_CHAMPS
} Sommet_t;

```

[x] - TODO : Lire le 3eme fichier CSV afin de construire les arcs du graphe

[x] TODO : Faire un makefile

[x] TODO : Envoyer travail intermédiaire

[x] TODO : Refactoriser le code 1 langue 1 convention
[] TODO : Resoudre fuite de mémoire -> graph->table et char * nom  avec strdup

[x] TODO : split_row() a un paramètre token qui n'est jamais utilisé en dehors de cette fonction. Ca pourrait simplement être une variable locale

[] TODO : Alternative un peu moins lisible mais qui ne nécessite pas une variable tierce et un test bizarre à l'intérieur pour strtok
Aucune idée de si ça peut être mieux ou moins bien...
Faudrait regarder les façons conventionnelles d'utiliser cette fonction
`for (token = strtok(buff, separator); token != NULL; token = strtok(NULL, separator))`
[x] TODO : Initialiser les valeurs de src et cible à -1 et faire un test ou assert
[x] TODO :  On s'en fiche de l'ordre de la liste, alors je pourrais juste rajouter un nouvel élément en tête à chaque fois

```c
new_node->suivant = graph->table[src].tete;
graph->table[src].tete = new_node;
```

[x] TODO : Assigner dans les noeuds des listes adjacentes le dénivelé ascendant ou descendant par rapport au noeud source

[x] TODO : Integrer L'alogithme de Floyd Marshall

[x] TODO : Décomposer son code