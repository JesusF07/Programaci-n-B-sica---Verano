#include <iostream>
#include <stdexcept>
using namespace std;

class Usuario {
private:
    string nombre;
    int edad;
    int pin;
    int codigo;

public:
    Usuario(string nombre, int edad, int pin, int codigo) {

        if (nombre.empty()) {
            throw invalid_argument("El nombre no puede estar vacio");
        }

        if (edad < 1 || edad > 120) {
            throw out_of_range("La edad esta fuera del rango permitido");
        }

        if (pin < 1000 || pin > 9999) {
            throw runtime_error("El PIN debe tener exactamente 4 digitos");
        }

        if (codigo < 0) {
            throw logic_error("El codigo no puede ser negativo");
        }

        this->nombre = nombre;
        this->edad = edad;
        this->pin = pin;
        this->codigo = codigo;
    }
};

int main() {

    // 1. invalid_argument
    try {
        Usuario u1("", 25, 1234, 10);
    }
    catch (const invalid_argument& e) {
        cout << "Error de argumento: " << e.what() << endl;
    }

    // 2. out_of_range
    try {
        Usuario u2("Ana", 150, 1234, 10);
    }
    catch (const out_of_range& e) {
        cout << "Error de rango: " << e.what() << endl;
    }

    // 3. runtime_error
    try {
        Usuario u3("Ana", 25, 12, 10);
    }
    catch (const runtime_error& e) {
        cout << "Error en tiempo de ejecucion: " << e.what() << endl;
    }

    // 4. logic_error
    try {
        Usuario u4("Ana", 25, 1234, -5);
    }
    catch (const logic_error& e) {
        cout << "Error logico: " << e.what() << endl;
    }

    return 0;
}