#include <iostream>
using namespace std;

int main() {
    int opciones[3];

    // Ingresar las opciones
    for (int i = 0; i < 3; i++) {
        cout << "Ingrese una opcion (1, 2 o 3): ";
        cin >> opciones[i];
    }

    // Procesar las opciones
    for (int i = 0; i < 3; i++) {
        switch (opciones[i]) {
            case 1:
                cout << "Opcion UNO" << endl;
                break;
            case 2:
                cout << "Opcion DOS" << endl;
                break;
            case 3:
                cout << "Opcion TRES" << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
                continue; // sigue buscando una opcion valida
        }

        break; // ← rompe el FOR cuando ya se ejecuto una opcion valida
    }

    return 0;
}
