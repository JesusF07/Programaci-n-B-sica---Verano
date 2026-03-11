#ifndef FACTURAS_H
#define FACTURAS_H

#include "estructuras.h"
#include <string>
using namespace std;

// ================= PROTOTIPOS =================
string generarNumeroSerie();
bool archivoExiste(const string& nombreArchivo);
void guardarFactura(const Factura& f);
void imprimirFactura(const Factura& f);
void buscarFactura();
void registrarFactura();

#endif