#include <iostream>
using namespace std;

int main() {
    int M;
    int x, aux, suma, digitos;

    cout << "Ingrese la cantidad de consultas: ";
    cin >> M;

    for (int i = 1; i <= M; i++) {

        cout << "Ingrese el numero de la consulta " << i << ": ";
        cin >> x;

        aux = x;
        if (aux < 0) {
            aux = -aux;
        }

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

        if (suma % 2 == 0 && x % 4 == 0) {
            cout << "Resultado: A" << endl;
        }
        else if (suma % 2 != 0 && x % 6 == 0) {
            cout << "Resultado: B" << endl;
        }
        else if (digitos == 3) {
            cout << "Resultado: C" << endl;
        }
        else {
            cout << "Resultado: D" << endl;
        }

        cout << "-----------------------------" << endl;
    }

    return 0;
}
