#ifndef FACTURA_H
#define FACTURA_H

#include "estructuras.h"

void inicializarFactura(Factura& f, int cap);
void liberarFactura(Factura& f);
void agregarProducto(Factura& f, const Producto& p);
void imprimirFactura(const Factura& f);
void registrarFactura();
void buscarFactura();

#endif