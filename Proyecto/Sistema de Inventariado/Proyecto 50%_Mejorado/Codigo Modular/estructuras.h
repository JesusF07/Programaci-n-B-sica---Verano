#ifndef ESTRUCTURAS_H  // Evita inclusión múltiple
#define ESTRUCTURAS_H

#include <string>
using namespace std;

// ================= ESTRUCTURA PRODUCTO =================
struct Producto {
    string codigo;
    string descripcion;
    string unidad;
    int cantidad;
    double precioUnitario;
};

// ================= ESTRUCTURA FACTURA =================
struct Factura {
    string numeroSerie;
    string rucCliente;
    string nombreCliente;
    string direccionCliente;
    string fecha;
    Producto* productos;    // Puntero a arreglo dinámico
    int cantidadProductos;
};

// ================= ESTRUCTURA USUARIO =================
struct Usuario {
    string username;
    string passwordHash;
};

#endif