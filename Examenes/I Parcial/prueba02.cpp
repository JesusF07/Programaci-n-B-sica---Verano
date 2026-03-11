#include <iostream>
using namespace std;

int main() {
    // Variables generales
    int opcion;
    int diaCerrado = 0;

    // Variables de registro de transacciones
    int units, transactionCode;
    float unitPrice;

    // Variables de reporte
    float ingresoNeto = 0;
    int ventasValidas = 0;
    int devoluciones = 0;
    int transInvalidas = 0;
    float mayorIng = 0;
    float menorIng = 0;
    float sumaVentas = 0; // Para promedio

    // Menu principal
    do {
        cout << "-------MENU-----------\n";
        cout << "1) Registrar transaccion\n";
        cout << "2) Reporte de ventas del dia\n";
        cout << "3) Reporte por transaccion (A/B/C/D)\n";
        cout << "4) Cerrar dia\n";
        cout << "5) Salir\n";
        cout << "Elija opcion: ";
        cin >> opcion;

        if(opcion == 1) {
            if(diaCerrado) {
                cout << "NO SE PUEDEN REGISTRAR MAS TRANSACCIONES. DIA CERRADO.\n";
            } else {
                cout << "Ingrese units unitPrice transactionCode: ";
                cin >> units >> unitPrice >> transactionCode;

                if(units == 0 || unitPrice <= 0) {
                    // Transaccion invalida
                    transInvalidas++;
                } else {
                    // Transaccion valida
                    float ingreso = units * unitPrice;
                    ingresoNeto += ingreso;

                    if(units > 0) {
                        ventasValidas++;
                        sumaVentas += ingreso;
                    } else if(units < 0) {
                        devoluciones++;
                    }

                    // Actualizar mayor y menor ingreso
                    if((ventasValidas + devoluciones + transInvalidas) == 1) {
                        mayorIng = ingreso;
                        menorIng = ingreso;
                    } else {
                        if(ingreso > mayorIng) mayorIng = ingreso;
                        if(ingreso < menorIng) menorIng = ingreso;
                    }
                }
            }
        }
        else if(opcion == 2) {
            cout << "INGRESO_NETO=" << ingresoNeto << endl;
            cout << "VENTAS_VALIDAS=" << ventasValidas << endl;
            cout << "DEVOLUCIONES=" << devoluciones << endl;
            cout << "TRANS_INVALIDAS=" << transInvalidas << endl;
            cout << "MAYOR_ING=" << mayorIng << endl;
            cout << "MENOR_ING=" << menorIng << endl;
            if(ventasValidas > 0)
                cout << "PROM_VENTA=" << sumaVentas / ventasValidas << endl;
            else
                cout << "PROM_VENTA=NO EXISTE\n";
        }
        else if(opcion == 3) {
            int code;
            cout << "Ingrese transactionCode a analizar: ";
            cin >> code;

            // Sumar digitos absolutos
            int suma = 0, temp = code < 0 ? -code : code;
            int digitos = 0;
            int t = temp;
            if(t == 0) digitos = 1; // Caso 0 tiene 1 digito
            while(t > 0) {
                suma += t % 10;
                t /= 10;
                digitos++;
            }

            if(suma % 2 == 0 && suma % 4 == 0)
                cout << "A\n";
            else if(suma % 2 == 1 && suma % 6 == 0)
                cout << "B\n";
            else if(digitos == 3)
                cout << "C\n";
            else
                cout << "D\n";
        }
        else if(opcion == 4) {
            diaCerrado = 1;
            cout << "DIA CERRADO. NO SE PERMITEN MAS TRANSACCIONES.\n";
        }
        else if(opcion == 5) {
            cout << "SALIENDO DEL SISTEMA...\n";
        }
        else {
            cout << "OPCION INVALIDA\n";
        }

    } while(opcion != 5);

    return 0;
}
