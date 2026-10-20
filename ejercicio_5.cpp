#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void swap(int &a, int &b) {
    int aux = a;
    a = b;
    b = aux;
}

int quickselect(int *A, int n, int pos) {
    int ini = 0; 
    int fin = n - 1;

    while (true) {
        // ELEGIR PIVOTE ALEATORIO
        int pivote = A[ini + rand() % (fin - ini + 1)];
        int menor = ini;
        int i = ini;
        int mayor = fin;

        // PARTICIONAR EL ARREGLO
        while (i <= mayor) {
            if (A[i] < pivote) { //menor que pivote
                swap(A[menor], A[i]);
                menor++;
                i++;
            } else if (A[i] > pivote) { //mayor que pivote
                swap(A[i], A[mayor]);
                mayor--;
            } else { //igual a pivote
                i++;
            }
        }
        // SELECCIONAR LA PARTICION
        if (pos < menor) {
            fin = menor - 1;
        } else if (pos > mayor) {
            ini = mayor + 1;
        } else {
            return pivote;
        }
    }
}


int main() {
    srand(time(0));
    int n, k;
    cout << "Cantidad de numeros: ";
    cin >> n;
    cout << "Que mayor deseas encontrar: ";
    cin >> k;
    int *A = new int[n];
    cout << "Ingresa los numeros: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    cout << "Resultado: " << quickselect(A, n, n - k) << endl;
    delete[] A;
    return 0;
}
