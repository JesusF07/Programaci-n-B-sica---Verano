#include <iostream>
#include <string>
using namespace std;
/*
Reflexión: ¿Qué problema evita el encapsulamiento?
El encapsulamiento evita el problema de que cualquier parte del programa cambie los datos de un objeto sin control. 
Gracias al encapsulamiento, puedo proteger la información y asegurarme de que los valores sean correctos
*/
class Celular {
private:
    string marca;
    string modelo;
    int bateria;

public:
    // Constructor
    Celular(string mar, string mod, int b) {
        marca = mar;
        modelo = mod;
        setBateria(b); // usamos el setter para validar
    }

    // Getters (const)
    string getMarca() const {
        return marca;
    }

    string getModelo() const {
        return modelo;
    }

    int getBateria() const {
        return bateria;
    }

    // Setter con validación
    void setBateria(int b) {
        if (b >= 0 && b <= 100) {
            bateria = b;
        } else {
            cout << "Error: Bateria invalida (" << b << "). Debe estar entre 0 y 100." << endl;
        }
    }
};

int main() {
    Celular c1("Samsung", "Galaxy S25 Ultra", 80);

    cout << "Bateria inicial: " << c1.getBateria() << "%" << endl;

    // Pruebas con valores inválidos
    c1.setBateria(150);
    c1.setBateria(-20);

    // Valor válido
    c1.setBateria(90);

    cout << "Bateria final: " << c1.getBateria() << "%" << endl;

    return 0;
}
