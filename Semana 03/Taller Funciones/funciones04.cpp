#include <iostream>
using namespace std;

// Función que calcula el promedio de un arreglo de notas
float calcularPromedio(float notas[], int n) {
    float suma = 0;

    for (int i = 0; i < n; i++) {
        suma += notas[i];
    }

    return suma / n;
}

int main() {
    int n;
    float notas[100];
    float promedio;

    cout << "Ingrese la cantidad de notas: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Ingrese la nota " << i + 1 << ": ";
        cin >> notas[i];
    }

    promedio = calcularPromedio(notas, n);

    cout << "El promedio de las notas es: " << promedio << endl;

    return 0;
}
