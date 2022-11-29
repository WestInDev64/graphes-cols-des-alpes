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

Poser la question à Bourdin concernant la connexité du GRAPHE

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

Envoyer travail intermédiaire

[] TODO : Refactoriser le code 1 langue 1 convention
[] TODO : Resoudre fuite de mémoire -> graph->table et char * nom  avec strdup
[] TODO : split_row() a un paramètre token qui n'est jamais utilisé en dehors de cette fonction. Ca pourrait simplement être une variable locale
[] TODO : Alternative un peu moins lisible mais qui ne nécessite pas une variable tierce et un test bizarre à l'intérieur pour strtok
Aucune idée de si ça peut être mieux ou moins bien...
Faudrait regarder les façons conventionnelles d'utiliser cette fonction
`for (token = strtok(buff, separator); token != NULL; token = strtok(NULL, separator))`
[] TODO : Initialiser les valeurs de src et cible à -1 et faire un test ou assert
