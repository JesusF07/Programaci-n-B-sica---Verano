#include <iostream>
using namespace std;

// Función que retorna el valor mínimo del arreglo
int minimoArreglo(int arr[], int n) {
    int minimo = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < minimo) {
            minimo = arr[i];
        }
    }

    return minimo;
}

int main() {
    int n;
    int arreglo[100];
    int resultado;

    cout << "Ingrese la cantidad de elementos: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Ingrese el elemento " << i + 1 << ": ";
        cin >> arreglo[i];
    }

    resultado = minimoArreglo(arreglo, n);

    cout << "El valor minimo del arreglo es: " << resultado << endl;

    return 0;
}
