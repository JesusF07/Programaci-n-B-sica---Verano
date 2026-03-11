#include <iostream>
using namespace std;

// Función que calcula el factorial de un número
long long factorial(int n) {
    long long resultado = 1;

    for (int i = 1; i <= n; i++) {
        resultado *= i;
    }

    return resultado;
}

int main() {
    int numero;
    long long resultado;

    cout << "Ingrese un numero entero (>= 0): ";
    cin >> numero;

    if (numero < 0) {
        cout << "No se puede calcular el factorial de un numero negativo." << endl;
    } else {
        resultado = factorial(numero);
        cout << "El factorial de " << numero << " es: " << resultado << endl;
    }

    return 0;
}
