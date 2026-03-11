#include <iostream>
#include "login.h"
#include "factura.h"

using namespace std;

int main() {
    login();

    int op;
    do {
        cout << "\n1. Registrar factura\n";
        cout << "2. Buscar factura\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        if (op == 1) registrarFactura();
        else if (op == 2) buscarFactura();

    } while (op != 0);

    return 0;
}