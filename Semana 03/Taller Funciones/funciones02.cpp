#include <iostream>
using namespace std;

// Función que determina si un número es par
bool esPar(int n) {
    if (n % 2 == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int numero;
    bool resultado;

    cout << "Ingrese un numero entero: ";
    cin >> numero;

    resultado = esPar(numero);

    if (resultado) {
        cout << "El numero es PAR." << endl;
    } else {
        cout << "El numero es IMPAR." << endl;
    }

    return 0;
}
