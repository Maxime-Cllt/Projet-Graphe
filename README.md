# Projet de Graphes - DSATUR

Ce projet a été réalisé dans le cadre d'un cours sur les graphes. Il vise à explorer l'utilisation de l'algorithme DSATUR pour la coloration de graphes.

## Présentation du projet

L'objectif de ce projet était de mettre en pratique les concepts appris en cours sur les graphes en utilisant l'algorithme DSATUR pour la coloration de graphes. Nous avons implémenté cet algorithme en C++ en utilisant des tableaux.

## Fonctionnement de l'algorithme DSATUR
L'algorithme DSATUR (Degree of the Smallest Adjacent Color plus Saturation) est un algorithme de coloration de graphes qui consiste à choisir à chaque étape le sommet ayant le plus grand degré et la saturation la plus élevée. La saturation d'un sommet est le nombre de couleurs différentes utilisées par ses voisins. Cet algorithme a été proposé par Brélaz en 1979.

<h2>Execution du code</h2>

Pour exécuter le programme avec les meilleures performances, compiler le fichier "Projet.cpp" en utilisant les commandes suivantes :

````
g++ -o exec -O3 Projet.cpp
````
````
./exec 
````
## Conclusion
Ce projet nous a permis de mieux comprendre le fonctionnement des graphes et de l'algorithme DSATUR en particulier. Nous avons également appris à implémenter cet algorithme en utilisant des tableaux en C++.
