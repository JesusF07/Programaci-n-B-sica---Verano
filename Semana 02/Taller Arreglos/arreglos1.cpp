#include <iostream>
using namespace std;

int main() {
    int gastos[7];
    int total = 0;
    int diasMayorPromedio = 0;
    float promedio;

    // Entrada de datos
    cout << "Ingrese los gastos de la semana:\n";
    for (int i = 0; i < 7; i++) {
        cin >> gastos[i];
        total += gastos[i];
    }

    // Calcular promedio
    promedio = total / 7.0;

    // Contar días con gasto mayor al promedio
    for (int i = 0; i < 7; i++) {
        if (gastos[i] > promedio) {
            diasMayorPromedio++;
        }
    }

    // Salida
    cout << "Total: " << total << endl;
    cout << "Promedio: " << promedio << endl;
    cout << "Dias con gasto mayor al promedio: " 
         << diasMayorPromedio << endl;

    return 0;
}
