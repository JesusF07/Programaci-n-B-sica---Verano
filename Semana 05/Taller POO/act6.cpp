#include <iostream>
#include <string>
using namespace std;
/*
Reflexión: ¿Qué ventaja da el polimorfismo?
el polimorfismo da la ventaja de poder tratar objetos diferentes como si fueran del mismo tipo, pero haciendo que cada uno se comporte de manera distinta. 
Esto hace el código más flexible, reutilizable y fácil de ampliar, porque puedo agregar nuevas clases sin cambiar la lógica principal del programa.
*/

// Clase base
class Persona {
private:
    string nombre;
    int edad;

public:
    Persona(string nombre, int edad) {
        this->nombre = nombre;
        setEdad(edad);
    }

    void setEdad(int edad) {
        if (edad >= 0)
            this->edad = edad;
        else
            this->edad = 0;
    }

    // Metodo virtual
    virtual void rol() const {
        cout << "Soy una persona" << endl;
    }

    virtual void mostrar() const {
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << endl;
    }

    // Destructor virtual (buena practica)
    virtual ~Persona() {}
};

// Clase Estudiante
class Estudiante : public Persona {
private:
    string carrera;

public:
    Estudiante(string nombre, int edad, string carrera)
        : Persona(nombre, edad) {
        this->carrera = carrera;
    }

    void rol() const override {
        cout << "Soy estudiante" << endl;
    }
};


// Clase Profesor
class Profesor : public Persona {
private:
    string materia;

public:
    Profesor(string nombre, int edad, string materia)
        : Persona(nombre, edad) {
        this->materia = materia;
    }

    void rol() const override {
        cout << "Soy profesor" << endl;
    }
};

int main() {
    Persona* personas[2];

    personas[0] = new Estudiante("Juan", 20, "Ingenieria");
    personas[1] = new Profesor("Maria", 45, "Programacion");

    for (int i = 0; i < 2; i++) {
        personas[i]->rol();   // Polimorfismo
    }

    // Liberar memoria
    for (int i = 0; i < 2; i++) {
        delete personas[i];
    }

    return 0;
}
