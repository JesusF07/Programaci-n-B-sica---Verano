#include <iostream>
#include <string>
using namespace std;
/*
Reflexión: ¿Qué pasaría si no usas this-> cuando el nombre del parámetro y el atributo son iguales?
Si no uso this-> cuando el parámetro y el atributo tienen el mismo nombre, el programa no sabrá a cuál me refiero y 
terminaré asignando el parámetro a sí mismo. Como resultado, el atributo del objeto no cambiará y el setter no funcionará correctamente.
*/
class Celular {
private:
    string marca;
    string modelo;
    int bateria;

public:
    // Constructor
    Celular(string marca, string modelo, int bateria) {
        this->marca = marca;
        this->modelo = modelo;
        setBateria(bateria);
    }

    // Getters
    string getMarca() const {
        return marca;
    }

    string getModelo() const {
        return modelo;
    }

    int getBateria() const {
        return bateria;
    }

    // Setters usando this->
    void setMarca(string marca) {
        this->marca = marca;
    }

    void setModelo(string modelo) {
        this->modelo = modelo;
    }

    void setBateria(int bateria) {
        if (bateria >= 0 && bateria <= 100) {
            this->bateria = bateria;
        } else {
            cout << "Error: Bateria invalida (" << bateria << ")" << endl;
        }
    }
};

int main() {
    Celular c1("Samsung", "Galaxy S25 Ultra", 80);

    cout << "Marca: " << c1.getMarca() << endl;
    cout << "Modelo: " << c1.getModelo() << endl;
    cout << "Bateria: " << c1.getBateria() << "%" << endl;

    c1.setMarca("Apple");
    c1.setModelo("iPhone 17 Pro Max");
    c1.setBateria(95);

    cout << "\nDespues de cambios:" << endl;
    cout << "Marca: " << c1.getMarca() << endl;
    cout << "Modelo: " << c1.getModelo() << endl;
    cout << "Bateria: " << c1.getBateria() << "%" << endl;

    return 0;
}
