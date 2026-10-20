
#include <iostream>
using namespace std;

long long mergeContar(int a[], int aux[], int inicio, int fin) {
    // 1. CASO BASE
    if (fin - inicio <= 1) //  0 o 1
        return 0;
    // 2. DIVIDIR
    int medio = (inicio + fin) / 2;
    // resolver ambas mitades
    long long izquierda = mergeContar(a, aux, inicio, medio);
    long long derecha = mergeContar(a, aux, medio, fin);
    long long cuenta = izquierda + derecha;
    // COMBINAR
    int i = inicio;
    int j = medio;
    int k = inicio;

    while (i < medio && j < fin) {
        if (a[i] <= a[j]) {
            aux[k] = a[i];
            i++;
        }
        else {
            aux[k] = a[j];
            j++;
            // Contar inversiones cruzadas
            cuenta += medio - i;
        }
        k++;
    }
    //COPIAR elementos restantes
    while (i < medio) {
        aux[k++] = a[i++];
    }
    while (j < fin) {
        aux[k++] = a[j++];
    }
    for (int p = inicio; p < fin; p++) {
        a[p] = aux[p];
    }
    return cuenta;
}

int main() {
    int n;

    while (cin >> n && n != 0) {
        int* A = new int[n];
        int* aux = new int[n];
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }
        cout << mergeContar(A, aux, 0, n) << endl;
        delete[] A;
        delete[] aux;
    }

    return 0;
}
