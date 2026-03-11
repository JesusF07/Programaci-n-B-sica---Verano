#include <iostream>
using namespace std;

// Clase padre
class Animal {
public:
    string nombre;

    void hacerSonido() {
        cout << "El animal hace un sonido." << endl;
    }
};

// Clase hija
class Perro : public Animal {
public:
    void ladrar() {
        cout << "El perro ladra: Guau!" << endl;
    }
};

int main() {
    Perro miPerro;

    miPerro.nombre = "Firulais";
    cout << "Nombre: " << miPerro.nombre << endl;

    miPerro.hacerSonido();  // heredado
    miPerro.ladrar();       // propio

    return 0;
}