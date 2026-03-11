#include <iostream>
#include <string>
using namespace std;

// ================= HERENCIA =================
class Persona {
protected:
    string nombre;

public:
    Persona(string n) : nombre(n) {}
    string getNombre() const { return nombre; }
};

// ================= COMPOSICIÓN =================
class Direccion {
private:
    string ciudad;

public:
    Direccion(string c) : ciudad(c) {}
    string getCiudad() const { return ciudad; }
};

// Estudiante HEREDA de Persona y COMPONE Dirección
class Estudiante : public Persona {
private:
    Direccion direccion; // composición

public:
    Estudiante(string n, string ciudad)
        : Persona(n), direccion(ciudad) {}

    void mostrar() const {
        cout << "Estudiante: " << nombre
             << ", Ciudad: " << direccion.getCiudad() << endl;
    }
};

// ================= AGREGACIÓN =================
class Escuela {
private:
    Estudiante* estudiantes[2]; // no es dueña de ellos

public:
    void agregarEstudiante(Estudiante* e, int pos) {
        estudiantes[pos] = e;
    }

    void mostrarEstudiantes() const {
        for (int i = 0; i < 2; i++)
            estudiantes[i]->mostrar();
    }
};

// ================= ASOCIACIÓN =================
class Profesor {
private:
    string nombre;

public:
    Profesor(string n) : nombre(n) {}

    void enseñar(const Estudiante& e) const {
        cout << "Profesor " << nombre
             << " enseña a " << e.getNombre() << endl;
    }
};

// ================= DEPENDENCIA =================
void imprimirEstudiante(const Estudiante& e) {
    cout << "Imprimiendo datos -> ";
    e.mostrar();
}

// ================= MAIN =================
int main() {
    Estudiante e1("Carlos", "Lima");
    Estudiante e2("Ana", "Cusco");

    Escuela escuela;
    escuela.agregarEstudiante(&e1, 0);
    escuela.agregarEstudiante(&e2, 1);

    Profesor profe("Juan");

    escuela.mostrarEstudiantes();
    profe.enseñar(e1);
    imprimirEstudiante(e2);

    return 0;
}