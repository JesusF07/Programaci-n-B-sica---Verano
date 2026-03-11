#include <iostream>
using namespace std;

const int DIAS = 7;

// Función para leer las temperaturas
void leerTemperaturas(int temp[]) {
    for (int i = 0; i < DIAS; i++) {
        cin >> temp[i];
    }
}

// Función para encontrar la temperatura máxima y su día
void temperaturaMaxima(int temp[], int &max, int &diaMax) {
    max = temp[0];
    diaMax = 1;

    for (int i = 1; i < DIAS; i++) {
        if (temp[i] > max) {
            max = temp[i];
            diaMax = i + 1;
        }
    }
}

// Función para encontrar la temperatura mínima y su día
void temperaturaMinima(int temp[], int &min, int &diaMin) {
    min = temp[0];
    diaMin = 1;

    for (int i = 1; i < DIAS; i++) {
        if (temp[i] < min) {
            min = temp[i];
            diaMin = i + 1;
        }
    }
}

// Función para contar días mayores a 30 grados
int contarMayores30(int temp[]) {
    int contador = 0;

    for (int i = 0; i < DIAS; i++) {
        if (temp[i] > 30) {
            contador++;
        }
    }

    return contador;
}

int main() {
    int temperaturas[DIAS];
    int max, min, diaMax, diaMin;
    int diasMayor30;

    cout << "Ingrese las temperaturas de los 7 dias:\n";
    leerTemperaturas(temperaturas);

    temperaturaMaxima(temperaturas, max, diaMax);
    temperaturaMinima(temperaturas, min, diaMin);
    diasMayor30 = contarMayores30(temperaturas);

    cout << "Maxima: " << max << " (dia " << diaMax << ")" << endl;
    cout << "Minima: " << min << " (dia " << diaMin << ")" << endl;
    cout << "Dias mayores a 30: " << diasMayor30 << endl;

    return 0;
}
