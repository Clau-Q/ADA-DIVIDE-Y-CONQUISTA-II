//T(n)=3T(n/2)+Θ(n)

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

string quitarCeros(const string& num) {
    int i = 0;

    while (i < (int)num.size() - 1 && num[i] == '0')
        i++;

    return num.substr(i);
}

string sumar(string a, string b) {
    string resultado = "";
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int acarreo = 0;
    while (i >= 0 || j >= 0 || acarreo > 0) {
        int suma = acarreo;
        if (i >= 0) suma += a[i--] - '0';
        if (j >= 0) suma += b[j--] - '0';
        resultado += char('0' + suma % 10);
        acarreo = suma / 10;
    }

    reverse(resultado.begin(), resultado.end());
    return quitarCeros(resultado);
}

string restar(string a, string b) {
    string resultado = "";
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int prestamo = 0;
    while (i >= 0) {
        int diferencia = a[i--] - '0' - prestamo;
        if (j >= 0)
            diferencia -= b[j--] - '0';
        if (diferencia < 0) {
            diferencia += 10;
            prestamo = 1;
        } else {
            prestamo = 0;
        }

        resultado += char('0' + diferencia);
    }
    reverse(resultado.begin(), resultado.end());
    return quitarCeros(resultado);
}

string mulEscolar(string a, string b) {
    a = quitarCeros(a);
    b = quitarCeros(b);
    if (a == "0" || b == "0")
        return "0";
    int n = a.size();
    int m = b.size();
    vector<int> v(n + m, 0);
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            v[i+j+1] += (a[i]-'0') * (b[j]-'0');
        }
    }
    for (int i = n+m-1; i > 0; i--) {
        v[i-1] += v[i] / 10;
        v[i] %= 10;
    }
    string resultado = "";
    for (int i = 0; i < n+m; i++)
        resultado += char('0' + v[i]);

    return quitarCeros(resultado);
}

// ALGORITMO DE KARATSUBA
string karatsuba(string X, string Y) {

    X = quitarCeros(X);
    Y = quitarCeros(Y);
    int n = max(X.size(), Y.size());
    // CASO BASE
    if (n <= 3)
        return to_string((X[0] - '0') * (Y[0] - '0'));
    // DIVIDIR
    if (n % 2 != 0)
        n++;
    X = string(n - X.size(), '0') + X;
    Y = string(n - Y.size(), '0') + Y;
    int mitad = n / 2;
    string A = X.substr(0, mitad);
    string B = X.substr(mitad);
    string C = Y.substr(0, mitad);
    string D = Y.substr(mitad);

    // CONQUISTAR: TRES LLAMADAS RECURSIVAS
    string E = karatsuba(A, C);
    string F = karatsuba(B, D);
    string suma1 = sumar(A, B);
    string suma2 = sumar(C, D);
    string G = karatsuba(suma1, suma2);
    // COMBINAR: CALCULAR TERMINO CRUZADO
    string H = restar(restar(G, E), F);
    // DESPLAZAR Y SUMAR LOS RESULTADOS
    string parte1 = E + string(n, '0');
    string parte2 = H + string(mitad, '0');

    string resultado = sumar(parte1, parte2);
    resultado = sumar(resultado, F);

    return quitarCeros(resultado);
}




int main() {
    string numero1, numero2;

    cout << "Ingrese el primer numero: ";
    cin >> numero1;

    cout << "Ingrese el segundo numero: ";
    cin >> numero2;

    string resultadoEscolar, resultadoKaratsuba;
    const int repeticiones = 1000;

    // MULTIPLICACION ESCOLAR
    auto inicio1 = chrono::steady_clock::now();

    for (int i = 0; i < repeticiones; i++) {
        resultadoEscolar = mulEscolar(numero1, numero2);
    }

    auto fin1 = chrono::steady_clock::now();

    // MULTIPLICACION KARATSUBA
    auto inicio2 = chrono::steady_clock::now();

    for (int i = 0; i < repeticiones; i++) {
        resultadoKaratsuba = karatsuba(numero1, numero2);
    }

    auto fin2 = chrono::steady_clock::now();

    // TIEMPOS PROMEDIO EN NANOSEGUNDOS
    double tiempoEscolar =
        chrono::duration<double, nano>(fin1 - inicio1).count()
        / repeticiones;

    double tiempoKaratsuba =
        chrono::duration<double, nano>(fin2 - inicio2).count()
        / repeticiones;

    cout << fixed << setprecision(2);

    cout << "\nMULTIPLICACION ESCOLAR\n";
    cout << "Resultado: " << resultadoEscolar << endl;
    cout << "Tiempo promedio: " << tiempoEscolar << " ns\n";

    cout << "\nKARATSUBA\n";
    cout << "Resultado: " << resultadoKaratsuba << endl;
    cout << "Tiempo promedio: " << tiempoKaratsuba << " ns\n";


    return 0;
}
