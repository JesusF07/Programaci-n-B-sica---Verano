#include <iostream>
using namespace std;

class Animal {
public:
    virtual void sonido() {
        cout << "Sonido de animal" << endl;
    }
};

class Perro : public Animal {
public:
    void sonido() override {
        cout << "Guau" << endl;
    }
};

class Gato : public Animal {
public:
    void sonido() override {
        cout << "Miau" << endl;
    }
};

int main() {
    Animal* a1 = new Perro();
    Animal* a2 = new Gato();

    a1->sonido();  // Guau
    a2->sonido();  // Miau

    return 0;
}