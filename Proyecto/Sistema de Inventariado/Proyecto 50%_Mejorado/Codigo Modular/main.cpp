/**
 SISTEMA DE FACTURACION ELECTRONICA
 Descripción: Sistema modular para gestión de facturas con encriptación de datos sensibles
 */

#include "estructuras.h"
#include "usuarios.h"
#include "facturas.h"
#include "menu.h"
#include <iostream>
using namespace std;

// ================= FUNCION PRINCIPAL =================
int main() {
    // Control de acceso al sistema
    login();

    int op;
    do {
        mostrarMenu();
        cin >> op;

        switch(op) {
            case 1:
                registrarFactura();      // Nueva factura
                break;
            case 2:
                buscarFactura();          // Buscar facturas existentes
                break;
            case 3:
                cambiarPassword();        // Cambiar contraseña
                break;
            case 0:
                cout << "\n+--------------------------------------+\n";
                cout << "|     ¡Gracias por usar el sistema!    |\n";
                cout << "+--------------------------------------+\n";
                break;
            default:
                cout << "\nOpcion no valida.\n";
        }

    } while (op != 0);

    return 0;
}