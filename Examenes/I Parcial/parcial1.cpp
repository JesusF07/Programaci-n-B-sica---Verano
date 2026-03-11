#include <iostream>
#include <iomanip> // para setprecision
using namespace std;

int main() {

    int opcion;
    int units, transactionCode;
    float unitPrice;
    float ingreso;

    float ingresoNeto = 0;
    int ventasValidas = 0;
    int devoluciones = 0;
    int transInvalidas = 0;

    float mayorIng = 0;
    float menorIng = 0;
    int primerValido = 1;

    float sumaVentas = 0;

    long long codigos = 0;      // almacena códigos válidos concatenados
    int cantidadCodigos = 0;

    int diaCerrado = 0;

    cout << fixed << setprecision(2);

    do {
        cout << "\n----- MENU -----\n";
        cout << "1) Registrar transaccion\n";
        cout << "2) Reporte de ventas del dia\n";
        cout << "3) Reporte por transaccion\n";
        cout << "4) Cerrar dia\n";
        cout << "5) Salir\n";
        cout << "Ingrese opcion: ";
        cin >> opcion;

        if (opcion == 1) {

            if (diaCerrado == 1) {
                cout << "NO SE PUEDEN REGISTRAR MAS TRANSACCIONES. DIA CERRADO.\n";
            } else {

                cout << "Ingrese cantidad de unidades: ";
                cin >> units;
                cout << "Ingrese precio unitario: ";
                cin >> unitPrice;
                cout << "Ingrese codigo de transaccion (3 digitos): ";
                cin >> transactionCode;

                if (units != 0 && unitPrice > 0) {

                    ingreso = units * unitPrice;
                    ingresoNeto += ingreso;

                    // Actualizar mayor y menor ingreso
                    if (primerValido == 1) {
                        mayorIng = ingreso;
                        menorIng = ingreso;
                        primerValido = 0;
                    } else {
                        if (ingreso > mayorIng) mayorIng = ingreso;
                        if (ingreso < menorIng) menorIng = ingreso;
                    }

                    // Guardar código concatenado
                    codigos = codigos * 1000 + (transactionCode < 0 ? -transactionCode : transactionCode);
                    cantidadCodigos++;

                    // Contar ventas o devoluciones
                    if (units > 0) {
                        ventasValidas++;
                        sumaVentas += ingreso;
                    } else {
                        devoluciones++;
                    }

                    cout << "Transaccion registrada con exito. Ingreso=" << ingreso << "\n";

                } else {
                    transInvalidas++;
                    cout << "Transaccion invalida. No se registro.\n";
                }
            }

        } else if (opcion == 2) {
            cout << "\n----- REPORTE DEL DIA -----\n";
            cout << "INGRESO NETO = " << ingresoNeto << endl;
            cout << "VENTAS VALIDAS = " << ventasValidas << endl;
            cout << "DEVOLUCIONES = " << devoluciones << endl;
            cout << "TRANS INVALIDAS = " << transInvalidas << endl;
            cout << "MAYOR INGRESO = " << mayorIng << endl;
            cout << "MENOR INGRESO = " << menorIng << endl;

            if (ventasValidas > 0)
                cout << "PROMEDIO VENTA = " << (sumaVentas / ventasValidas) << endl;
            else
                cout << "PROMEDIO VENTA = NO EXISTE\n";

        } else if (opcion == 3) {

            cout << "\n----- REPORTE POR TRANSACCION -----\n";
            long long temp = codigos;
            int i = 0;

            while (i < cantidadCodigos) {

                int code = temp % 1000; // tomar últimos 3 dígitos
                temp /= 1000;

                int absCode = code;
                int suma = 0;
                int digitos = 0;

                while (absCode > 0) {
                    suma += absCode % 10;
                    absCode /= 10;
                    digitos++;
                }

                // Clasificación según reglas
                if (suma % 2 == 0 && suma % 4 == 0)
                    cout << "Codigo " << code << " => A\n";
                else if (suma % 2 != 0 && suma % 6 == 0)
                    cout << "Codigo " << code << " => B\n";
                else if (digitos == 3)
                    cout << "Codigo " << code << " => C\n";
                else
                    cout << "Codigo " << code << " => D\n";

                i++;
            }

        } else if (opcion == 4) {
            diaCerrado = 1;
            cout << "Dia cerrado. No se podran registrar mas transacciones.\n";
        } else if (opcion == 5) {
            cout << "Saliendo del programa...\n";
        } else {
            cout << "Opcion invalida. Ingrese un numero entre 1 y 5.\n";
        }

    } while (opcion != 5);

    return 0;
}
