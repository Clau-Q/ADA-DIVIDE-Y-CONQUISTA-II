#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
// PUNTO
struct Punto {
    int x;
    int y;
};

long long dist2(Punto a, Punto b) {   // distancia al cuadrado 
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// Ordena P
void ordenarPorX(Punto *P, Punto *aux, int ini, int fin) {
    // Caso base
    if (ini >= fin) {
        return;
    }
    // Dividir
    int med = (ini + fin) / 2;
     // Conquistar
    ordenarPorX(P, aux, ini, med);
    ordenarPorX(P, aux, med + 1, fin);
    // Combinar
    int i = ini;
    int j = med + 1;
    int k = ini;
    
    while (i <= med && j <= fin) {//COMPARA
        if (P[i].x <= P[j].x) {
            aux[k++] = P[i++];
        } else {
            aux[k++] = P[j++];
        }
    }

    while (i <= med) {//sobrantes
        aux[k++] = P[i++];
    }
    while (j <= fin) {
        aux[k++] = P[j++];
    }
    for (k = ini; k <= fin; k++) {//aux copia a P
        P[k] = aux[k];
    }
}

// 5. ALGORITMO DEL PAR MAS CERCANO
long long masCercano(Punto P[], Punto aux[], Punto franja[], int inicio, int fin) {

    const long long INF = 4000000000000000000LL;
    // CASO BASE
    if (inicio >= fin)
        return INF;
    //  DIVIDIR
    int medio = (inicio + fin) / 2;
    int xMedio = P[medio].x;
    // CONQUISTAR
    long long d1 = masCercano(P, aux, franja, inicio, medio);
    long long d2 = masCercano(P, aux, franja, medio + 1, fin);
    // Elegir la menor distancia
    long long d = min(d1, d2);
    // COMBINAR
    mezclarPorY(P, aux, inicio, medio, fin);
    // CREAR FRANJA CENTRAL
    int tam = 0;
    for (int i = inicio; i <= fin; i++) {
        long long dx = 1LL * P[i].x - xMedio;
        if (dx * dx < d) {
            // COMPARAR PUNTOS CERCANOS
            for (int j = tam - 1; j >= 0; j--) {
                long long dy = 1LL * P[i].y - franja[j].y;
                if (dy * dy >= d)
                    break;
                long long nuevaDist = dist2(P[i], franja[j]);
                if (nuevaDist < d)
                    d = nuevaDist;
            }
            franja[tam++] = P[i];
        }
    }
    //  DEVOLVER MENOR DISTANCIA
    return d;
}

// MEZCLAR DOS MITADES ORDENADAS POR Y
void mezclarPorY(Punto P[], Punto aux[],
                int inicio, int medio, int fin) {

    int i = inicio;
    int j = medio + 1;
    int k = inicio;

    while (i <= medio && j <= fin) {
        if (P[i].y <= P[j].y)
            aux[k++] = P[i++];
        else
            aux[k++] = P[j++];
    }

    while (i <= medio)
        aux[k++] = P[i++];

    while (j <= fin)
        aux[k++] = P[j++];

    for (int p = inicio; p <= fin; p++)
        P[p] = aux[p];
}

int main() {
    int n;
    while (cin >> n && n != 0) {
        Punto *P = new Punto[n];
        Punto *aux = new Punto[n];
        Punto *franja = new Punto[n];
        for (int i = 0; i < n; i++) {
            cin >> P[i].x >> P[i].y;
        }
        if (n == 1) {  // Solo un punto, no hay par
            cout << "INFINITY" << endl;   

        } else {
            ordenarPorX(P, aux, 0, n - 1);
            long long d = masCercano(P, aux, franja, 0, n - 1);
            if (d >= 100000000LL) {          // distancia >= 10000
                cout << "INFINITY" << endl;
            } else {
                cout << fixed << setprecision(4) << sqrt((double)d) << endl;
            }
        }
        delete[] P;
        delete[] aux;
        delete[] franja;
    }
    return 0;
}