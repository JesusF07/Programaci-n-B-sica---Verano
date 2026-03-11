#include <iostream>
using namespace std;

// Función que busca un valor dentro del arreglo
bool buscarValor(int arr[], int n, int valor) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == valor) {
            return true;
        }
    }
    return false;
}

int main() {
    int n;
    int arreglo[100];
    int valor;
    bool encontrado;

    cout << "Ingrese la cantidad de elementos: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Ingrese el elemento " << i + 1 << ": ";
        cin >> arreglo[i];
    }

    cout << "Ingrese el valor a buscar: ";
    cin >> valor;

    encontrado = buscarValor(arreglo, n, valor);

    if (encontrado) {
        cout << "El valor SI existe en el arreglo." << endl;
    } else {
        cout << "El valor NO existe en el arreglo." << endl;
    }

    return 0;
}
