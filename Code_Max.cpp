#include <cstdlib>
#include <iostream>
#include <cmath>
#include <new>

using namespace std;

int n; // nombre de sommets
int **adj; //[n][n];  // matrice d'adjacence du graphe
int *couleur1; //[n];  // couleurs des sommets pour l'agorithme exact
int *couleur2; //[n]; // couleurs pour DSATUR
int *DSAT; //[n]; // degrÈs de saturation
int *Degre; //[n]; // degrÈs des sommets
bool trouve = false; // permet de stopper l'algorithme exact quand une coloration  a ete trouvee


void genere(int p) // genere un graphe non orientÈ de n sommets et probabilitÈ p d'arÍte entre toute paire de sommets
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
        cout << "Coloration en " << k << " couleurs trouvÈe" << endl;
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
    //if(!trouve) cout << "Pas de coloration en " << k <<" couleurs" << endl;
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


int main() {
    int p, k, nbc;
    const int N = 50;
    cout << "Nombre de sommets" << endl;
    //cin >> n;
    n = 10;
    cout << "Proba d'arÍte: " << endl;
//    cin >> p;
    p = 100;

    adj = new int *[n];
    for (int i = 0; i < n; i++)
        adj[i] = new int[n];
    couleur1 = new int[n];
    couleur2 = new int[n];
    DSAT = new int[n];
    Degre = new int[n];

    genere(p);

//    for (int i = 0; i < n; i++) {
//        cout << "sommet " << i << " : ";
//        for (int j = 0; j < n; j++)
//            if (adj[i][j]) cout << j << " ";
//        cout << endl;
//    }
//
//    k = DSATUR(0);
//    cout << "DSAT: coloration en " << k << " couleurs : " << endl;
//    for (int i = 0; i  < n; i++)
//        cout << "couleur de " << i << " : " << couleur2[i] << endl;
//
//    cout << "ColorExact :" << endl;
//    nbc = nbChromatique(k);
//    cout << "Nombre chromatique : " << nbc << endl;

    cout << "N : " << n << endl;
    cout << "P : " << p << endl;
    cout << "Degré moyen dans le graphe : [" << degmoy() << "]" << endl;


    delete adj;
    delete couleur2;
    delete couleur1;
    delete DSAT;
    delete Degre;

    return 0;
}
