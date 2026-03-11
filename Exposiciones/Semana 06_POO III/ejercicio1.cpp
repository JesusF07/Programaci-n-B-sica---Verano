#include <iostream>
using namespace std;

/*
Una Persona puede ser un Estudiante → Herencia
Un Estudiante tiene una Dirección que no existe sola → Composición
Una Escuela recibe un Estudiante, pero no lo crea → Agregación
Un Profesor usa a un Estudiante → Asociación
Una función usa un Estudiante → Dependencia
*/

// ================= HERENCIA =================
class Persona {
public:
    string nombre;
};

// ================= COMPOSICIÓN =================
class Direccion {
public:
    string ciudad;
};

class Estudiante : public Persona {
public:
    Direccion dir;   // composición
};

// ================= AGREGACIÓN =================
class Escuela {
public:
    void mostrarEstudiante(Estudiante e) {
        cout << "Escuela muestra: " << e.nombre << endl;
    }
};

// ================= ASOCIACIÓN =================
class Profesor {
public:
    void enseñar(Estudiante e) {
        cout << "Profesor ensena a: " << e.nombre << endl;
    }
};

// ================= DEPENDENCIA =================
void imprimir(Estudiante e) {
    cout << "Imprimiendo: " << e.nombre << endl;
}

// ================= MAIN =================
int main() {
    Estudiante est;
    est.nombre = "Dalex";
    est.dir.ciudad = "Tingo Maria";

    Escuela esc;
    Profesor prof;

    esc.mostrarEstudiante(est); // agregación
    prof.enseñar(est);          // asociación
    imprimir(est);              // dependencia

    return 0;
}