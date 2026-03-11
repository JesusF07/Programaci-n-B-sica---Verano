#include <iostream>
using namespace std;

// Función que retorna el mayor de dos números
int mayor(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int main() {
    int num1, num2, resultado;

    cout << "Ingrese el primer numero: ";
    cin >> num1;

    cout << "Ingrese el segundo numero: ";
    cin >> num2;

    resultado = mayor(num1, num2);

    cout << "El numero mayor es: " << resultado << endl;

    return 0;
}
