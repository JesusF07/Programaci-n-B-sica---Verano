#include <iostream>
using namespace std;

class Calculadora {
public:
    int sumar(int a, int b) {
        return a + b;
    }

    double sumar(double a, double b) {
        return a + b;
    }
};

int main() {
    Calculadora c;

    cout << c.sumar(5, 3) << endl;       // 8
    cout << c.sumar(2.5, 3.1) << endl;   // 5.6

    return 0;
}