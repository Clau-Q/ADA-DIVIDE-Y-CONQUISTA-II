#include <iostream>
using namespace std;

long long* memo[20][20];   // memo[ini][fin] = resultados ya calculados de e[ini..fin]
int cant[20][20];          // cant[ini][fin] = cuantos resultados hay en memo[ini][fin]

void agregar(long long *&R, int &n, int &cap, long long valor) {
    if (n == cap) {
        if (cap == 0)
            cap = 4;
        else
            cap = cap * 2;
        long long *nuevo = new long long[cap];
        for (int i = 0; i < n; i++)
            nuevo[i] = R[i];
        delete[] R;
        R = nuevo;
    }
    R[n] = valor;
    n++;
}

void print(long long *R, int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << R[i];
    }
    cout << endl;
}

void selectionsort (long long *R, int n) {
    for (int i=0; i<n - 1; i++) {
        for (int j=i + 1; j<n; j++) {
            if (R[i] > R[j]) {
                long long aux = R[i];
                R[i] = R[j];
                R[j] = aux;
            }
        }
    }
}

long long* formas(char e[], int ini, int fin, int &n) {
    // si ya lo calcule, lo devuelvo sin volver a operar
    if (memo[ini][fin] != nullptr) {
        n = cant[ini][fin];
        return memo[ini][fin];
    }

    long long *R = nullptr;
    n = 0;
    int cap = 0;
    for (int i=ini; i<=fin; i++) {
        if (e[i]=='+'|| e[i]=='-' || e[i]=='*') {
            int na = 0, nb = 0;
            long long *A = formas(e, ini, i-1, na);
            long long *B = formas(e, i+1, fin, nb);
            for (int a = 0; a<na; a++) {
                for (int b = 0; b < nb; b++) {
                    long long val;
                    if (e[i] == '+') 
                        val = A[a] + B[b];
                    else if (e[i] == '-') 
                        val = A[a] - B[b];
                    else 
                        val = A[a] * B[b];
                    agregar(R, n, cap, val);
                }
            }
            // A y B pertenecen a la memoria: no se borran aqui
        }
    }
    //base
    if (n == 0) {
        long long num = 0;
        for (int i=ini; i <= fin; i++) {
            num = num * 10 + (e[i] - '0');
        }
        agregar(R, n,cap, num);
    }

    memo[ini][fin] = R;      // guardar para la proxima vez
    cant[ini][fin] = n;
    return R;
}

int main() {
    char e[21];
    cin >> e;
    int tam = 0;
    while (e[tam] != '\0') {
        tam++;
    }
    int n = 0;
    long long *R = formas(e, 0, tam - 1, n);
    selectionsort (R, n);
    print(R, n);

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            delete[] memo[i][j];
    return 0;
}