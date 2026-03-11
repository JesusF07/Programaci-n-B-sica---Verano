#include <iostream>
using namespace std;

const int DIAS = 8;

// Función para leer los valores diarios
void leerDatos(int datos[]) {
    for (int i = 0; i < DIAS; i++) {
        cin >> datos[i];
    }
}

// Función para calcular la mayor racha positiva
int mayorRachaPositiva(int datos[]) {
    int rachaActual = 0;
    int rachaMayor = 0;

    for (int i = 0; i < DIAS; i++) {
        if (datos[i] > 0) {
            rachaActual++;
            if (rachaActual > rachaMayor) {
                rachaMayor = rachaActual;
            }
        } else {
            rachaActual = 0;
        }
    }

    return rachaMayor;
}

int main() {
    int datos[DIAS];

    cout << "Ingrese los valores diarios:\n";
    leerDatos(datos);

    int racha = mayorRachaPositiva(datos);

    cout << "Mayor racha positiva: "
         << racha << " dias" << endl;

    return 0;
}
