#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "factura.h"
#include "validaciones.h"

using namespace std;

// ================= INICIALIZAR FACTURA =================
void inicializarFactura(Factura& f, int cap) {
    f.capacidad = cap;
    f.cantidadProductos = 0;
    f.productos = new Producto[cap];
}

// ================= LIBERAR FACTURA =================
void liberarFactura(Factura& f) {
    delete[] f.productos;
    f.productos = nullptr;
}

// ================= AGREGAR PRODUCTO =================
void agregarProducto(Factura& f, const Producto& p) {
    if (f.cantidadProductos < f.capacidad) {
        f.productos[f.cantidadProductos++] = p;
    }
}

// ================= IMPRIMIR FACTURA =================
void imprimirFactura(const Factura& f) {
    double total = 0;

    cout << "\n+==================================================================================+\n";
    cout << "| FACTURA ELECTRONICA                                                             |\n";
    cout << "+==================================================================================+\n";
    cout << "| Fecha      : " << f.fecha << endl;
    cout << "| Cliente    : " << f.nombreCliente << endl;
    cout << "| RUC        : " << f.rucCliente << endl;
    cout << "| Dirección  : " << f.direccionCliente << endl;
    cout << "+----------------------------------------------------------------------------------+\n";
    cout << "| Cant | Und | Código | Descripción                 | P.Unit | Subtotal           |\n";
    cout << "+----------------------------------------------------------------------------------+\n";

    for (int i = 0; i < f.cantidadProductos; i++) {
        double sub = f.productos[i].cantidad * f.productos[i].precioUnitario;
        total += sub;

        cout << "| " << setw(4) << f.productos[i].cantidad << " | "
             << setw(3) << f.productos[i].unidad << " | "
             << setw(6) << f.productos[i].codigo << " | "
             << left << setw(25) << f.productos[i].descripcion << right << " | "
             << setw(6) << fixed << setprecision(2) << f.productos[i].precioUnitario << " | "
             << setw(15) << sub << " |\n";
    }

    double igv = total * 0.18;

    cout << "+----------------------------------------------------------------------------------+\n";
    cout << "| OP. GRAVADA : " << setw(40) << total << " |\n";
    cout << "| IGV (18%)   : " << setw(40) << igv << " |\n";
    cout << "| TOTAL       : " << setw(40) << total + igv << " |\n";
    cout << "+==================================================================================+\n";
}

// ================= REGISTRAR FACTURA =================
void registrarFactura() {
    Factura f;
    string ruc, fecha, nombre, direccion;
    int cantProductos;

    cout << "\n--- REGISTRAR FACTURA ---\n";
    ruc = leerCadenaNumerica("RUC: ");
    fecha = leerFecha("Fecha (YYYY-MM-DD): ");
    cin.ignore(); // Limpiar el salto de línea después de leerFecha()
    nombre = leerNombre("Nombre del cliente: ");
    cout << "Dirección: ";
    getline(cin, direccion);
    cantProductos = leerEntero("Cantidad de productos: ");

    inicializarFactura(f, cantProductos);
    f.rucCliente = ruc;
    f.fecha = fecha;
    f.nombreCliente = nombre;
    f.direccionCliente = direccion;

    for (int i = 0; i < cantProductos; ++i) {
        Producto p;
        cout << "\nProducto " << i+1 << ":\n";
        cout << "Código: ";
        cin >> p.codigo;
        cin.ignore(); // Para poder leer descripción con getline
        cout << "Descripción: ";
        getline(cin, p.descripcion);
        cout << "Unidad (ej. Gr., L, Kg): ";
        cin >> p.unidad;
        p.cantidad = leerEntero("Cantidad: ");
        p.precioUnitario = leerDouble("Precio unitario: ");

        agregarProducto(f, p);
    }

    // Guardar en archivo
    ofstream archivo("facturas.txt", ios::app);
    if (archivo.is_open()) {
        archivo << f.rucCliente << "\n";
        archivo << f.fecha << "\n";
        archivo << f.nombreCliente << "\n";
        archivo << f.direccionCliente << "\n";
        archivo << f.cantidadProductos << "\n";
        for (int i = 0; i < f.cantidadProductos; ++i) {
            archivo << f.productos[i].codigo << "|"
                    << f.productos[i].descripcion << "|"
                    << f.productos[i].unidad << "|"
                    << f.productos[i].cantidad << "|"
                    << f.productos[i].precioUnitario << "\n";
        }
        archivo << "----\n";
        archivo.close();
        cout << "\nFactura guardada en facturas.txt\n";
    } else {
        cout << "Error al abrir archivo para guardar.\n";
    }

    imprimirFactura(f);
    liberarFactura(f);
}

// ================= BUSCAR FACTURA =================
void buscarFactura() {
    string rucBuscar;
    rucBuscar = leerCadenaNumerica("Ingrese RUC a buscar: ");

    ifstream archivo("facturas.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo facturas.txt\n";
        return;
    }

    string linea;
    bool encontrada = false;
    while (getline(archivo, linea)) {
        string ruc = linea;
        if (ruc != rucBuscar) {
            // Saltar esta factura hasta el separador
            while (getline(archivo, linea) && linea != "----");
            continue;
        }

        // Leer datos de la factura
        Factura f;
        getline(archivo, f.fecha);
        getline(archivo, f.nombreCliente);
        getline(archivo, f.direccionCliente);
        string cantStr;
        getline(archivo, cantStr);
        f.cantidadProductos = stoi(cantStr);
        f.capacidad = f.cantidadProductos;
        f.productos = new Producto[f.capacidad];

        for (int i = 0; i < f.cantidadProductos; ++i) {
            getline(archivo, linea);
            stringstream ss(linea);
            string campo;
            getline(ss, campo, '|'); f.productos[i].codigo = campo;
            getline(ss, campo, '|'); f.productos[i].descripcion = campo;
            getline(ss, campo, '|'); f.productos[i].unidad = campo;
            getline(ss, campo, '|'); f.productos[i].cantidad = stoi(campo);
            getline(ss, campo, '|'); f.productos[i].precioUnitario = stod(campo);
        }

        getline(archivo, linea); // Leer el "----"

        cout << "\n--- FACTURA ENCONTRADA ---\n";
        imprimirFactura(f);
        liberarFactura(f);
        encontrada = true;
        break;
    }

    if (!encontrada) {
        cout << "No se encontró factura con RUC " << rucBuscar << "\n";
    }
    archivo.close();
}