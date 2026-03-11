#include <iostream>
using namespace std;

// Función que valida si la opción está dentro del rango permitido
bool opcionValida(int opcion, int min, int max) {
    if (opcion >= min && opcion <= max) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int opcion;
    int minimo = 1;
    int maximo = 5;
    bool valida;

    cout << "Menu de opciones (1 a 5)" << endl;
    cout << "Ingrese una opcion: ";
    cin >> opcion;

    valida = opcionValida(opcion, minimo, maximo);

    if (valida) {
        cout << "Opcion valida." << endl;
    } else {
        cout << "Opcion invalida." << endl;
    }

    return 0;
}
