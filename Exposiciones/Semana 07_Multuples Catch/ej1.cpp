#include <iostream>
#include <stdexcept>
using namespace std;

class Persona {
private:
    int edad;
    double sueldo;

public:
    Persona(int edad, double sueldo) {

        if (edad <= 0)
            throw invalid_argument("La edad debe ser mayor que cero");

        if (sueldo < 1025)
            throw out_of_range("El sueldo es menor al minimo permitido");

        this->edad = edad;
        this->sueldo = sueldo;
    }

    void mostrar() const {
        cout << "Edad: " << edad << endl;
        cout << "Sueldo: " << sueldo << endl;
    }
};

int main() {
    try {
        int edad;
        double sueldo;

        cout << "Ingrese edad: ";
        cin >> edad;

        cout << "Ingrese sueldo: ";
        cin >> sueldo;

        Persona p(edad, sueldo);
        p.mostrar();
    }
    catch (const invalid_argument& e) {
        cout << "Error de argumento: " << e.what() << endl;
    }
    catch (const out_of_range& e) {
        cout << "Error de rango: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "Error general: " << e.what() << endl;
    }

    cout << "Fin del programa." << endl;
    return 0;
}