#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
using namespace std;

// ================= PROTOTIPOS DE FUNCIONES DE VALIDACIÓN =================

// Validación de tipos de datos
bool esNumero(const string& cad);
bool esDecimal(const string& cad);
bool esSoloLetras(const string& cad);
bool esAlfanumerico(const string& cad);
bool esFechaValida(const string& cad);
bool esRUCValido(const string& ruc);
bool esEmailValido(const string& email);
bool esTelefonoValido(const string& telefono);

// Lectura con validación
int leerEntero(const string& msg);
int leerEnteroRango(const string& msg, int min, int max);
double leerDouble(const string& msg);
double leerDoubleRango(const string& msg, double min, double max);
string leerCadenaNumerica(const string& msg);
string leerCadenaNumericaLongitud(const string& msg, int longitud);
string leerNombre(const string& msg);
string leerNombreCompleto(const string& msg);
string leerFecha(const string& msg);
string leerRUC(const string& msg);
string leerEmail(const string& msg);
string leerTelefono(const string& msg);
string leerTexto(const string& msg);
string leerTextoNoVacio(const string& msg);

// Utilidades
string trim(const string& cad);
string toUpper(string cad);
string toLower(string cad);
bool confirmarAccion(const string& msg);

#endif