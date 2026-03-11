#include <iostream>
using namespace std;

const int ESTUDIANTES = 3;
const int DIAS = 5;

// Función para leer la matriz de asistencia
void leerAsistencia(int asistencia[][DIAS]) {
    for (int i = 0; i < ESTUDIANTES; i++) {
        for (int j = 0; j < DIAS; j++) {
            cin >> asistencia[i][j];
        }
    }
}

// Función para calcular la asistencia total por estudiante
void asistenciaPorEstudiante(int asistencia[][DIAS]) {
    for (int i = 0; i < ESTUDIANTES; i++) {
        int total = 0;
        for (int j = 0; j < DIAS; j++) {
            total += asistencia[i][j];
        }
        cout << "Estudiante " << (i + 1)
             << " - Asistencias: " << total << endl;
    }
}

// Función para identificar estudiantes con asistencia perfecta
void asistenciaPerfecta(int asistencia[][DIAS]) {
    for (int i = 0; i < ESTUDIANTES; i++) {
        bool perfecta = true;
        for (int j = 0; j < DIAS; j++) {
            if (asistencia[i][j] == 0) {
                perfecta = false;
                break;
            }
        }
        if (perfecta) {
            cout << "Estudiante " << (i + 1)
                 << " tiene asistencia perfecta" << endl;
        }
    }
}

// Función para calcular el total de asistencias del aula
int totalAsistenciasAula(int asistencia[][DIAS]) {
    int total = 0;
    for (int i = 0; i < ESTUDIANTES; i++) {
        for (int j = 0; j < DIAS; j++) {
            total += asistencia[i][j];
        }
    }
    return total;
}

int main() {
    int asistencia[ESTUDIANTES][DIAS];

    cout << "Ingrese la matriz de asistencia (0 = No, 1 = Si):\n";
    leerAsistencia(asistencia);

    asistenciaPorEstudiante(asistencia);
    asistenciaPerfecta(asistencia);

    int totalAula = totalAsistenciasAula(asistencia);
    cout << "Total de asistencias del aula: "
         << totalAula << endl;

    return 0;
}
