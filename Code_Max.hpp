
#ifndef GRAPHE_TP3_HPP
#define GRAPHE_TP3_HPP

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

const int n = 35; // nombre de sommets
int adj[n][n];  // matrice d'adjacence du graphe
int couleur1[n];  // couleurs des sommets pour l'agorithme exact
int couleur2[n];  // couleurs des sommets pour l'agorithme glouton
int couleur3[n];  // couleurs des sommets pour l'agorithme glouton



bool trouve = false; // permet de stopper l'algorithme exact
// quand une coloration  a ete trouvee


int DSATUR() {
    int nb = 0, c, x, cmax = 0;
    for (int i = 0; i < n; i++) {
        couleur2[i] = 0;
        DSAT[i] = 0;
        Degre[i] = 0;
        for (int j = 0; j < n; j++)
            if (adj[i][j]) Degre[i]++;
        DSAT[i] = Degre[i];
    }

    while (nb < n)  // tant qu'on a pas coloriÈ tous les sommets
    {
        c = 1;
        x = dsatMax(); // on choisit le sommet de DSAT max non encore coloriÈ
        while (!convientDSAT(x, c)) c++; // on cherche la plus petite couleur disponible pour ce sommet
        for (int j = 0; j < n; j++) // mise ‡ jour des DSAT
        {
            if (adj[x][j] && convientDSAT(j, c))
                DSAT[j]++; // j n'avait aucun voisin coloriÈ c,on incrÈmente donc son DSAT
        }
        couleur2[x] = c;
        if (cmax < c) cmax = c;
        nb++;
    }

    return cmax;
}

int DSATUR(int k) {
    int nb = 0, c, x, cmax = 0;
    for (int i = 0; i < n; i++) {
        couleur2[i] = 0;
        DSAT[i] = 0;
        Degre[i] = 0;
        for (int j = 0; j < n; j++)
            if (adj[i][j]) Degre[i]++;
        DSAT[i] = Degre[i];
    }

    while (nb < n)  // tant qu'on a pas coloriÈ tous les sommets
    {
        c = 1;
        x = dsatMax(); // on choisit le sommet de DSAT max non encore coloriÈ
        while (!convientDSAT(x, c)) {

            c++; // on cherche la plus petite couleur disponible pour ce sommet

        }
        for (int j = 0; j < n; j++) // mise ‡ jour des DSAT
        {
            if (adj[x][j] && convientDSAT(j, c))
                DSAT[j]++; // j n'avait aucun voisin coloriÈ c,on incrÈmente donc son DSAT
        }
        couleur2[x] = c;
        if (cmax < c) cmax = c;
        nb++;
    }

    return cmax;
}

bool convient(int x, int c) {
    for (int i = 0; i < x; i++)
        if (adj[x][i] && (couleur1[i] == c)) return false;
    return true;
}

void colorRR(int x, int k) {
    if (x == n) {
        cout << "Coloration en " << k << " couleurs trouvee" << endl;
        for (int i = 0; i < n; i++) cout << "couleur de " << i << " : " << couleur1[i] << endl; //int z;cin >> z;
        trouve = true;
    } else
        for (int c = 1; c <= k; c++)
            if (convient(x, c)) {
                couleur1[x] = c;
                colorRR(x + 1, k);
                if (trouve) return;
            }
}

void colorExact(int k) {
    for (int i = 0; i < n; i++)
        couleur1[i] = 0;
    colorRR(0, k);
    if (!trouve) cout << "Pas de coloration en " << k << " couleurs" << endl;
}

void generegraphe(int p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rand() % 100 < p) {
                adj[i][j] = 1;
                adj[j][i] = 1;
            }
        }
    }
}

void affichegraphe() {
    for (int i = 0; i < n; i++) {
        cout << "Sommet " << i << " : ";
        for (int j = 0; j < n; j++) {
            if (adj[i][j] == 1) {
                cout << j << " ";
            }
        }
        cout << endl;
    }
}

int nbChromatique() {
    int k = 1;
    while (true) {
        trouve = false;
        colorExact(k);
        if (trouve) return k;
        k++;
    }
}

int degmoy() {
    float moy = 0, moy_col = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j) {
            if (adj[i][j] == 1) {
                moy_col++;
            }
//            cout << " " << adj[i][j] << " ";
        }
        moy += (moy_col / n);
//        cout << endl;
    }
//    cout << "Degré moyen dans le graphe : " << (moy/(n-1)) << endl;
    return (moy / (n - 1));
}


/*
 * coloration gloutonne
 *  en utilisant la fonction convient
 */
int ColorGlouton() {
    for (int &i: couleur2) {
        i = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int c = 1; c <= n; c++) {
            if (convient(i, c)) {
                couleur2[i] = c;
                break;
            }
        }
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (couleur2[i] > k) {
            k = couleur2[i];
        }
    }
    return k;
}

#endif //GRAPHE_TP3_HPP
