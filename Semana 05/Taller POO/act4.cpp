#include <iostream>
#include <string>
using namespace std;
/*
Reflexión: ¿Por qué es útil tener constructores sobrecargados?
tener constructores sobrecargados es útil porque me permite crear objetos de diferentes formas 
según la información que tenga disponible. Así puedo inicializar un objeto fácilmente sin repetir código
*/
class Celular {
private:
    string marca;
    string modelo;
    int bateria;

public:
    // 1. Constructor por defecto
    Celular() {
        marca = "Desconocida";
        modelo = "Generico";
        bateria = 100;
    }

    // 2. Constructor con 2 parámetros
    Celular(string marca, string modelo) {
        this->marca = marca;
        this->modelo = modelo;
        bateria = 100;
    }

    // 3. Constructor con 3 parámetros (con validación)
    Celular(string marca, string modelo, int bateria) {
        this->marca = marca;
        this->modelo = modelo;
        setBateria(bateria);
    }

    // Setter con validación
    void setBateria(int bateria) {
        if (bateria >= 0 && bateria <= 100) {
            this->bateria = bateria;
        } else {
            cout << "Bateria invalida (" << bateria << "), se asigna 100 por defecto." << endl;
            this->bateria = 100;
        }
    }

    // Método para mostrar información
    void mostrarInfo() const {
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Bateria: " << bateria << "%" << endl;
    }
};

int main() {
    // 4. Crear objetos con cada constructor
    Celular c1; // constructor por defecto
    Celular c2("Samsung", "Galaxy S25 Ultra"); // constructor con 2 parámetros
    Celular c3("Apple", "iPhone 17 Pro Max", 80); // constructor con 3 parámetros

    cout << "Celular 1:" << endl;
    c1.mostrarInfo();

    cout << "\nCelular 2:" << endl;
    c2.mostrarInfo();

    cout << "\nCelular 3:" << endl;
    c3.mostrarInfo();

    return 0;
}
