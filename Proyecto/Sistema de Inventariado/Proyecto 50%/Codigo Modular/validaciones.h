#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

using namespace std;

bool esNumero(const string& cad);
bool esSoloLetras(const string& cad);
bool esFechaValida(const string& cad);

int leerEntero(const string& msg);
double leerDouble(const string& msg);
string leerCadenaNumerica(const string& msg);
string leerNombre(const string& msg);
string leerFecha(const string& msg);

#endif