#include <iostream>
#include <string>
using namespace std;
/*
Reflexión: ¿Qué atributos y métodos comparten Estudiante y Profesor gracias a Persona?
Gracias a la clase Persona, tanto Estudiante como Profesor comparten los atributos nombre y edad, y también los métodos para acceder a ellos y 
mostrarlos. Para mí, esto evita repetir código y hace que el programa sea más ordenado, porque todo lo que es común se define una sola vez en la clase base.
*/

// Parte A – Clase base
class Persona {
private:
    string nombre;
    int edad;

public:
    Persona(string nombre, int edad) {
        this->nombre = nombre;
        setEdad(edad);
    }

    // Getters
    string getNombre() const {
        return nombre;
    }

    int getEdad() const {
        return edad;
    }

    // Setters con validación
    void setNombre(string nombre) {
        this->nombre = nombre;
    }

    void setEdad(int edad) {
        if (edad >= 0) {
            this->edad = edad;
        } else {
            cout << "Edad invalida. Se asigna 0." << endl;
            this->edad = 0;
        }
    }

    // Método mostrar
    void mostrar() const {
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << endl;
    }
};

// Parte B – Clases derivadas
class Estudiante : public Persona {
private:
    string carrera;

public:
    Estudiante(string nombre, int edad, string carrera)
        : Persona(nombre, edad) {
        this->carrera = carrera;
    }

    void estudiar() const {
        cout << "El estudiante esta estudiando la carrera de " << carrera << endl;
    }

    void mostrar() const {
        Persona::mostrar();
        cout << "Carrera: " << carrera << endl;
    }
};

class Profesor : public Persona {
private:
    string materia;

public:
    Profesor(string nombre, int edad, string materia)
        : Persona(nombre, edad) {
        this->materia = materia;
    }

    void ensenar() const {
        cout << "El profesor esta ensenando la materia de " << materia << endl;
    }

    void mostrar() const {
        Persona::mostrar();
        cout << "Materia: " << materia << endl;
    }
};

// Parte C Pruebas
int main() {
    Estudiante e1("Augusto", 21, "Ingenieria de Sistemas");
    Profesor p1("Marina", 35, "Programacion");

    cout << "Datos del Estudiante:" << endl;
    e1.mostrar();
    e1.estudiar();

    cout << "\nDatos del Profesor:" << endl;
    p1.mostrar();
    p1.ensenar();

    return 0;
}
