#include <iostream>
using namespace std;

class Calculadora {
private:
    int resultado;  // Oculto

public:
    void sumar(int a, int b) {
        resultado = a + b;
    }

    int obtenerResultado() {
        return resultado;
    }
};

int main() {
    Calculadora calc;
    calc.sumar(5, 3);
    cout << "Resultado: " << calc.obtenerResultado() << endl;
    return 0;
}