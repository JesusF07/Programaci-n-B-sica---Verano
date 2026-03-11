#include <iostream>
using namespace std;

// Función que retorna el valor máximo del arreglo
int maximoArreglo(int arr[], int n) {
    int maximo = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] > maximo) {
            maximo = arr[i];
        }
    }

    return maximo;
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

    resultado = maximoArreglo(arreglo, n);

    cout << "El valor maximo del arreglo es: " << resultado << endl;

    return 0;
}
