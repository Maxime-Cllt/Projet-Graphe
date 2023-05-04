#include <cstdlib>
#include <iostream>
#include <new>
#include <ctime>
#include "Projet.hpp"

using namespace std;


int main() {
    int p, k, nbc;

    srand(time(nullptr));
    n = rand() % 10;
    p = rand() % 100;
//
//    n = 5;
//    p = 50;
    int degre_k = rand() % 10;


    // Allocation dynamique des tableaux
    adj = new int *[n];
    for (int i = 0; i < n; i++) adj[i] = new int[n];
    couleur1 = new int[n];
    couleur2 = new int[n];
    DSAT = new int[n];
    Degre = new int[n];

    // Initialisation des tableaux
    genere(p);

    cout << "N : " << n << endl;
    cout << "P : " << p << endl;
    cout << "Degré moyen dans le graphe : [" << degmoy() << "]" << endl;

//
//    for (int i = 0; i < n; i++) {
//        cout << "sommet " << i << " : ";
//        for (int j = 0; j < n; j++)
//            if (adj[i][j]) cout << j << " ";
//        cout << endl;
//    }
//
    k = DSATUR(degre_k);
    cout << "----------------------------" << endl;
    cout << "DSATUR : " << "Nombre de couleurs : " << DSATUR() << endl;
    cout << "DSATUR avec k : " << degre_k << " impropre. Nombre de couleurs : " << k << endl;
    cout << "DSATUR2 avec k : " << degre_k << " impropre. Nombre de couleurs : " << DSATUR2(degre_k) << endl;
    cout << "----------------------------" << endl;
//    for (int i = 0; i  < n; i++)
//        cout << "couleur de " << i << " : " << couleur2[i] << endl;

//    cout << "ColorExact :" << colorexact(k) << endl;
    nbc = nbChromatique(k);
    cout << "Nombre chromatique : " << nbc << endl;


    // Libération de la mémoire
    delete adj;
    delete couleur2;
    delete couleur1;
    delete DSAT;
    delete Degre;

    return 0;
}
