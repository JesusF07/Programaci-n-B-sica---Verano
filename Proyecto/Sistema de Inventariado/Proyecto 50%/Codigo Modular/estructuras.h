#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <string>

using namespace std;

struct Producto {
    string codigo;
    string descripcion;
    string unidad;
    int cantidad;
    double precioUnitario;
};

struct Factura {
    string rucCliente;
    string nombreCliente;
    string direccionCliente;
    string fecha;

    Producto* productos;     
    int cantidadProductos;   
    int capacidad;           
};

#endif