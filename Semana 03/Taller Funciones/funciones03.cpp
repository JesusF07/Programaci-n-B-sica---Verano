#include <iostream>
using namespace std;

// Función que calcula la suma de los elementos del arreglo
int sumaArreglo(int arr[], int n) {
    int suma = 0;

    for (int i = 0; i < n; i++) {
        suma += arr[i];
    }

    return suma;
}

int main() {
    int n;
    int arreglo[100]; // tamaño máximo permitido
    int resultado;

    cout << "Ingrese la cantidad de elementos: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Ingrese el elemento " << i + 1 << ": ";
        cin >> arreglo[i];
    }

    resultado = sumaArreglo(arreglo, n);

    cout << "La suma de los elementos del arreglo es: " << resultado << endl;

    return 0;
}
