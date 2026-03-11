#include <iostream>
using namespace std;

class Calculadora {
public:
    double dividir(double a, double b) {
        if (b == 0) {
            throw "No se puede dividir entre cero";
        }
        return a / b;
    }
};

int main() {
    Calculadora calc;

    try {
        double resultado = calc.dividir(10, 0);
        cout << "Resultado: " << resultado << endl;
    }
    catch (const char* mensaje) {
        cout << "Error: " << mensaje << endl;
    }

    return 0;
}