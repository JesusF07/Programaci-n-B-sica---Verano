#include <iostream>
using namespace std;

class Persona {
private:
    int edad;   // dato protegido

public:
    void setEdad(int e) {   // metodo para modificar
        edad = e;
    }

    int getEdad() {         // metodo para consultar
        return edad;
    }
};

int main() {
    Persona p;

    p.setEdad(20);   // usamos metodo para asignar
    cout << "Edad: " << p.getEdad() << endl;  // usamos metodo para leer

    return 0;
}