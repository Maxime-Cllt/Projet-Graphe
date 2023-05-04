
#ifndef PROJET_HPP
#define PROJET_HPP

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

// VARIABLES GLOBALES
int n; // nombre de sommets
int **adj; //[n][n];  // matrice d'adjacence du graphe
int *couleur1; //[n];  // couleurs des sommets pour l'algorithme exact
int *couleur2; //[n]; // couleurs pour DSATUR
int *DSAT; //[n]; // degré de saturation
int *Degre; //[n]; // degré des sommets
bool trouve = false; // permet de stopper l'algorithme exact quand une coloration a été trouvé

//DECLARATION DES FONCTIONS

void genere(int p);

bool convient(int x, int c);

bool convientDSAT(int x, int c);

void colorRR(int x, int k);

void colorexact(int k);

int nbChromatique(int d);

int dsatMax();

int DSATUR();

int DSATUR(int k);

int DSATUR2(int k);

int degmoy();

void affichegraphe();

int ColorGlouton();


//FONTIONS GLOBALES

void genere(int p) // génère un graphe non orientÈ de n sommets et probabilité p d'arête entre toute paire de sommets
{
    srand(time(NULL));
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++)
            if (rand() % 101 <= p)
                adj[i][j] = adj[j][i] = 1;
            else adj[i][j] = adj[j][i] = 0;
    }
}

bool convient(int x,
              int c) // teste si la couleur c peut Ítre donnee au sommet x (elle n'est pas utilisee par un de ses voisins)
{
    for (int i = 0; i < x; i++)
        if (adj[x][i] && (couleur1[i] == c)) return false;
    return true;
}

bool convientDSAT(int x, int c) // teste si la couleur c peut Ítre donnee au sommet x - version pour DSATUR
{
    for (int i = 0; i < n; i++)
        if (adj[x][i] && (couleur2[i] == c)) return false;
    return true;
}

void colorRR(int x, int k) // fonction recursive pour tester toutes les couleurs possible pour le sommet x
{
    if (x == n) {
        cout << "Coloration en " << k << " couleurs trouvé" << endl;
        for (int i = 0; i < n; i++) cout << "couleur de " << i << " : " << couleur1[i] << endl; //int z;cin >> z;
        trouve = true;
    } else
        for (int c = 1; c <= k; c++)
            if (convient(x, c)) {
                couleur1[x] = c;//cout << "=>couleur de " << x << " : " << couleur[x] << endl;
                colorRR(x + 1, k);
                if (trouve) return;
            }
    //return false;
}

void colorexact(int k) // teste si le graphe possede une coloration en k couleurs en essayant toutes les combinaisons
{
    for (int i = 0; i < n; i++)
        couleur1[i] = 0;
    colorRR(0, k);
    if (!trouve) cout << "Pas de coloration en " << k << " couleurs" << endl;
}

int nbChromatique(
        int d) {// calcule le nombre chromatique en testant ‡ partir de d couleurs et diminuant k tant que c'est possible
    int k = d + 1;
    do {
        k--;
        trouve = false;
        colorexact(k);
    } while (trouve);
    return k + 1;
}

int dsatMax() {
    int maxDeg = -1, maxDSAT = -1, smax = 0;
    for (int i = 0; i < n; i++)
        if (couleur2[i] == 0 && (DSAT[i] > maxDSAT || (DSAT[i] == maxDSAT && Degre[i] > maxDeg))) {
            maxDSAT = DSAT[i];
            maxDeg = Degre[i];
            smax = i;
        }
    //cout << "sommet " << smax << " choisi" << endl;
    return smax;
}

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

    while (nb < n)  // tant qu'on a pas colorié tous les sommets
    {
        c = 1;
        x = dsatMax(); // on choisit le sommet de DSAT max non encore colorié
        while (!convientDSAT(x, c)) {
            if (c == k) c++; // si la couleur atteint le degré d'impropreté, on saute cette couleur
            c++;
        }
        for (int j = 0; j < n; j++) // mise à jour des DSAT
        {
            if (adj[x][j] && convientDSAT(j, c))
                DSAT[j]++; // j n'avait aucun voisin colorié c,on incrémente donc son DSAT
        }
        couleur2[x] = c;
        if (cmax < c) cmax = c;
        nb++;
    }

    return cmax;
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

/**
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
*/

int degmoy() {
    float moy = 0, moy_col = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j) {
            if (adj[i][j] == 1) {
                moy_col++;
            }
        }
        moy += (moy_col / n);
    }
    return (moy / (n - 1));
}

int DSATUR2(int k) {
    int nb = 0, c, x, cmax = 0;
    for (int i = 0; i < n; i++) {
        couleur2[i] = 0;
        DSAT[i] = 0;
        Degre[i] = 0;
        for (int j = 0; j < n; j++)
            if (adj[i][j]) Degre[i]++;
        DSAT[i] = Degre[i];
    }

    while (nb < n) {  // tant qu'on a pas colorié tous les sommets
        c = 1;
        x = dsatMax(); // on choisit le sommet de DSAT max non encore colorié
        while (!convientDSAT(x, c)) {
            if (c == k) c++; // si la couleur atteint le degré d'impropreté, on saute cette couleur
            c++;
        }
        for (int j = 0; j < n; j++) { // mise à jour des DSAT
            if (adj[x][j] && convientDSAT(j, c)) {
                int count = 0;
                for (int l = 0; l < n; l++) {
                    if (adj[j][l] && couleur2[l] == c) {
                        count++;
                    }
                }
                if (count < k) {
                    DSAT[j]++; // j n'avait aucun voisin colorié c, on incrémente donc son DSAT
                }
            }
        }
        couleur2[x] = c;
        if (cmax < c) cmax = c;
        nb++;
    }
    return cmax;
}


#endif //PROJET_HPP
