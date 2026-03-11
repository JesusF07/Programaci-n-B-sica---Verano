#include <iostream>
using namespace std;

// Función que verifica si el arreglo está ordenado de forma ascendente
bool estaOrdenadoAsc(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    int arreglo[100];
    bool ordenado;

    cout << "Ingrese la cantidad de elementos: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Ingrese el elemento " << i + 1 << ": ";
        cin >> arreglo[i];
    }

    ordenado = estaOrdenadoAsc(arreglo, n);

    if (ordenado) {
        cout << "El arreglo esta ordenado de forma ascendente." << endl;
    } else {
        cout << "El arreglo NO esta ordenado de forma ascendente." << endl;
    }

    return 0;
}
