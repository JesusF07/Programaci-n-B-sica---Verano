#include <iostream>
using namespace std;

int main() {
    int numero;

    while (true) {
        cout << "Ingrese un numero (0 para salir): ";
        cin >> numero;

        if (numero == 0) {
            break;
        }

        cout << "Numero ingresado: " << numero << endl;
    }

    cout << "El ciclo ha terminado." << endl;

    return 0;
}

