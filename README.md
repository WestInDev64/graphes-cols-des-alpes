# graphes-cols-des-alpes

> Projet Algorithme avancé
> Axel Labarre
> Langage C

## Description

On voudra représenter les routes entre les cols de la chaîne de montagne des Alpes dans un graphe implémenté avec les structures Lis et Vect, et déterminer le chemin permettant de passer d’un col à un autre en minimisant le dénivelé.
Les dénivelés seront représentés par des poids positifs lorsqu’il y a un dénivelé positif, négatif sinon.

https://www.cols-cyclisme.com/alpes-maritimes/liste-r61.htm

## Utilisation

La présence d’un Makefile vous permettra de compiler facilement ce projet.
src = Sommet source
dst = Sommet de destination

Quelques fonctions d’affichages sont présente, n’y faites pas trop attention.

Compiler le projet :

```shell
make 
```

Exécuter le projet :

```shell
./graph_alpes
```

Nettoyer le répertoire du projet :

```shell
make clean
```
