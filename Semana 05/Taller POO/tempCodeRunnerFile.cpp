#include <iostream>
#include <string>
using namespace std;
/*
Reflexión: ¿Por qué la herencia reduce repetición de código?
la herencia reduce la repetición de código porque permite colocar los atributos y métodos comunes en una sola clase base. Así, las clases hijas reutilizan ese código 
sin volver a escribirlo, lo que hace el programa más ordenado, fácil de mantener y menos propenso a errores.
*/


// Clase base

class Vehiculo {
private:
    string marca;
    int velocidadMax;

public:
    Vehiculo(string marca, int velocidadMax) {
        this->marca = marca;
        setVelocidadMax(velocidadMax);
    }

    // Getters
    string getMarca() const {
        return marca;
    }

    int getVelocidadMax() const {
        return velocidadMax;
    }

    // Setters
    void setMarca(string marca) {
        this->marca = marca;
    }

    void setVelocidadMax(int velocidadMax) {
        if (velocidadMax > 0)
            this->velocidadMax = velocidadMax;
        else
            this->velocidadMax = 0;
    }

    // Método mostrar
    virtual void mostrarInfo() const {
        cout << "Marca: " << marca << endl;
        cout << "Velocidad Maxima: " << velocidadMax << " km/h" << endl;
    }

    virtual ~Vehiculo() {}
};

// Clase derivada Carro

class Carro : public Vehiculo {
private:
    int puertas;

public:
    Carro(string marca, int velocidadMax, int puertas)
        : Vehiculo(marca, velocidadMax) {
        this->puertas = puertas;
    }

    void mostrarInfo() const override {
        Vehiculo::mostrarInfo();
        cout << "Puertas: " << puertas << endl;
    }
};

// Clase derivada Moto

class Moto : public Vehiculo {
private:
    int cilindraje;

public:
    Moto(string marca, int velocidadMax, int cilindraje)
        : Vehiculo(marca, velocidadMax) {
        this->cilindraje = cilindraje;
    }

    void mostrarInfo() const override {
        Vehiculo::mostrarInfo();
        cout << "Cilindraje: " << cilindraje << " cc" << endl;
    }
};


int main() {
    Carro c1("Toyota", 180, 4);
    Moto m1("Yamaha", 220, 600);

    cout << "Datos del Carro:" << endl;
    c1.mostrarInfo();

    cout << "\nDatos de la Moto:" << endl;
    m1.mostrarInfo();

    return 0;
}
