#include <iostream>
using namespace std;

int main() {
    int M;
    cin >> M;

    int x, aux, suma, digitos;

    for (int i = 0; i < M; i++) {
        cin >> x;

        // Trabajamos con valor absoluto para los dígitos
        aux = x;
        if (aux < 0) {
            aux = -aux;
        }

        // Calcular suma de dígitos
        suma = 0;
        digitos = 0;

        if (aux == 0) {
            suma = 0;
            digitos = 1;
        } else {
            while (aux > 0) {
                suma = suma + (aux % 10);
                aux = aux / 10;
                digitos++;
            }
        }

        // Prioridad de condiciones
        if (suma % 2 == 0 && x % 4 == 0) {
            cout << "A" << endl;
        }
        else if (suma % 2 != 0 && x % 6 == 0) {
            cout << "B" << endl;
        }
        else if (digitos == 3) {
            cout << "C" << endl;
        }
        else {
            cout << "D" << endl;
        }
    }

    return 0;
}
