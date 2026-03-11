/**
 * ARCHIVO: validaciones.cpp
 * DESCRIPCIÓN: Implementación completa de todas las funciones de validación
 * AUTOR: Sistema de Facturación
 * FECHA: 2024
 */

#include "validaciones.h"
#include <iostream>
#include <cctype>
#include <sstream>
#include <algorithm>
using namespace std;

// ================= FUNCIONES DE VALIDACIÓN BÁSICAS =================

// Función: trim
// Propósito: Elimina espacios en blanco al inicio y final de una cadena
// Parámetros: cad - cadena a procesar
// Retorno: cadena sin espacios al inicio ni final
string trim(const string& cad) {
    if (cad.empty()) return cad;
    
    size_t inicio = cad.find_first_not_of(" \t\n\r");
    size_t fin = cad.find_last_not_of(" \t\n\r");
    
    if (inicio == string::npos) return "";
    return cad.substr(inicio, fin - inicio + 1);
}

// Función: toUpper
// Propósito: Convierte una cadena a mayúsculas
// Parámetros: cad - cadena a convertir
// Retorno: cadena en mayúsculas
string toUpper(string cad) {
    for (char& c : cad) {
        c = toupper(c);
    }
    return cad;
}

// Función: toLower
// Propósito: Convierte una cadena a minúsculas
// Parámetros: cad - cadena a convertir
// Retorno: cadena en minúsculas
string toLower(string cad) {
    for (char& c : cad) {
        c = tolower(c);
    }
    return cad;
}

// Función: esNumero
// Propósito: Verifica si una cadena contiene solo dígitos
// Parámetros: cad - cadena a validar
// Retorno: true si solo contiene dígitos, false en caso contrario
bool esNumero(const string& cad) {
    string limpia = trim(cad);
    if (limpia.empty()) return false;
    
    for (char c : limpia) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Función: esDecimal
// Propósito: Verifica si una cadena es un número decimal válido
// Parámetros: cad - cadena a validar
// Retorno: true si es decimal válido, false en caso contrario
bool esDecimal(const string& cad) {
    string limpia = trim(cad);
    if (limpia.empty()) return false;
    
    bool puntoEncontrado = false;
    
    for (size_t i = 0; i < limpia.length(); i++) {
        char c = limpia[i];
        
        if (c == '.') {
            if (puntoEncontrado) return false; // Solo un punto permitido
            puntoEncontrado = true;
        } else if (!isdigit(c)) {
            return false;
        }
    }
    
    return true;
}

// Función: esSoloLetras
// Propósito: Verifica si una cadena contiene solo letras y espacios
// Parámetros: cad - cadena a validar
// Retorno: true si solo contiene letras y espacios, false en caso contrario
bool esSoloLetras(const string& cad) {
    string limpia = trim(cad);
    if (limpia.empty()) return false;
    
    for (char c : limpia) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}

// Función: esAlfanumerico
// Propósito: Verifica si una cadena contiene solo letras, números y espacios
// Parámetros: cad - cadena a validar
// Retorno: true si es alfanumérica, false en caso contrario
bool esAlfanumerico(const string& cad) {
    string limpia = trim(cad);
    if (limpia.empty()) return false;
    
    for (char c : limpia) {
        if (!isalnum(c) && c != ' ') return false;
    }
    return true;
}

// ================= VALIDACIONES ESPECÍFICAS =================

// Función: esFechaValida
// Propósito: Verifica formato AAAA-MM-DD y que sea una fecha válida
// Parámetros: cad - fecha a validar
// Retorno: true si es fecha válida, false en caso contrario
bool esFechaValida(const string& cad) {
    string limpia = trim(cad);
    
    // Verificar longitud y formato
    if (limpia.length() != 10) return false;
    
    // Verificar posiciones de los guiones
    if (limpia[4] != '-' || limpia[7] != '-') return false;
    
    // Verificar que los demás caracteres sean dígitos
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(limpia[i])) return false;
    }
    
    // Extraer año, mes, día
    int anio = stoi(limpia.substr(0, 4));
    int mes = stoi(limpia.substr(5, 2));
    int dia = stoi(limpia.substr(8, 2));
    
    // Validar rangos básicos
    if (anio < 1900 || anio > 2100) return false;
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;
    
    // Validar días por mes
    if (mes == 2) {
        // Febrero
        bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        if (bisiesto && dia > 29) return false;
        if (!bisiesto && dia > 28) return false;
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        // Meses con 30 días
        if (dia > 30) return false;
    }
    // Meses con 31 días ya validados con dia > 31
    
    return true;
}

// Función: esRUCValido
// Propósito: Valida un RUC peruano (11 dígitos)
// Parámetros: ruc - RUC a validar
// Retorno: true si es RUC válido, false en caso contrario
bool esRUCValido(const string& ruc) {
    string limpia = trim(ruc);
    
    // El RUC debe tener 11 dígitos
    if (limpia.length() != 11) return false;
    
    // Verificar que todos sean dígitos
    for (char c : limpia) {
        if (!isdigit(c)) return false;
    }
    
    // Los primeros 2 dígitos deben ser 10, 15, 17, 20 (simplificado)
    string prefijo = limpia.substr(0, 2);
    if (prefijo != "10" && prefijo != "15" && prefijo != "17" && prefijo != "20") {
        return false;
    }
    
    return true;
}

// Función: esEmailValido
// Propósito: Valida un email (formato básico)
// Parámetros: email - email a validar
// Retorno: true si el formato es válido, false en caso contrario
bool esEmailValido(const string& email) {
    string limpia = trim(email);
    
    // Verificar presencia de @ y .
    size_t arroba = limpia.find('@');
    size_t punto = limpia.find('.', arroba + 2);
    
    if (arroba == string::npos || arroba == 0) return false;
    if (punto == string::npos || punto == arroba + 1) return false;
    if (limpia.find('@', arroba + 1) != string::npos) return false;
    
    return true;
}

// Función: esTelefonoValido
// Propósito: Valida un teléfono (9 dígitos para celular, 7 para fijo)
// Parámetros: telefono - teléfono a validar
// Retorno: true si es válido, false en caso contrario
bool esTelefonoValido(const string& telefono) {
    string limpia = trim(telefono);
    
    if (!esNumero(limpia)) return false;
    
    // Celular: 9 dígitos, Fijo: 7 dígitos
    return (limpia.length() == 9 || limpia.length() == 7);
}

// ================= FUNCIONES DE LECTURA CON VALIDACIÓN =================

// Función: leerEntero
// Propósito: Lee y valida entrada de número entero
// Parámetros: msg - mensaje a mostrar
// Retorno: número entero válido
int leerEntero(const string& msg) {
    string cad;
    do {
        cout << msg;
        cin >> cad;
        if (!esNumero(cad)) {
            cout << "Error: Debe ingresar solo números.\n";
        }
    } while (!esNumero(cad));
    return stoi(cad);
}

// Función: leerEnteroRango
// Propósito: Lee y valida número entero dentro de un rango
// Parámetros: msg - mensaje, min - valor mínimo, max - valor máximo
// Retorno: número entero dentro del rango
int leerEnteroRango(const string& msg, int min, int max) {
    int valor;
    do {
        valor = leerEntero(msg);
        if (valor < min || valor > max) {
            cout << "Error: El valor debe estar entre " << min << " y " << max << ".\n";
        }
    } while (valor < min || valor > max);
    return valor;
}

// Función: leerDouble
// Propósito: Lee y valida entrada de número decimal
// Parámetros: msg - mensaje a mostrar
// Retorno: número decimal válido
double leerDouble(const string& msg) {
    string cad;
    do {
        cout << msg;
        cin >> cad;
        if (!esDecimal(cad)) {
            cout << "Error: Debe ingresar un número válido (use . para decimales).\n";
        }
    } while (!esDecimal(cad));
    return stod(cad);
}

// Función: leerDoubleRango
// Propósito: Lee y valida número decimal dentro de un rango
// Parámetros: msg - mensaje, min - valor mínimo, max - valor máximo
// Retorno: número decimal dentro del rango
double leerDoubleRango(const string& msg, double min, double max) {
    double valor;
    do {
        valor = leerDouble(msg);
        if (valor < min || valor > max) {
            cout << "Error: El valor debe estar entre " << min << " y " << max << ".\n";
        }
    } while (valor < min || valor > max);
    return valor;
}

// Función: leerCadenaNumerica
// Propósito: Lee y valida entrada de solo números (como string)
// Parámetros: msg - mensaje a mostrar
// Retorno: cadena de solo números
string leerCadenaNumerica(const string& msg) {
    string cad;
    do {
        cout << msg;
        cin >> cad;
        cad = trim(cad);
        if (!esNumero(cad)) {
            cout << "Error: Debe ingresar solo números.\n";
        }
    } while (!esNumero(cad));
    return cad;
}

// Función: leerCadenaNumericaLongitud
// Propósito: Lee y valida cadena numérica con longitud específica
// Parámetros: msg - mensaje, longitud - longitud requerida
// Retorno: cadena numérica de la longitud especificada
string leerCadenaNumericaLongitud(const string& msg, int longitud) {
    string cad;
    do {
        cad = leerCadenaNumerica(msg);
        if ((int)cad.length() != longitud) {
            cout << "Error: Debe tener exactamente " << longitud << " dígitos.\n";
        }
    } while ((int)cad.length() != longitud);
    return cad;
}

// Función: leerNombre
// Propósito: Lee y valida nombre (solo letras, una palabra)
// Parámetros: msg - mensaje a mostrar
// Retorno: nombre válido
string leerNombre(const string& msg) {
    string cad;
    do {
        cout << msg;
        cin >> cad;
        cad = trim(cad);
        if (!esSoloLetras(cad)) {
            cout << "Error: El nombre debe contener solo letras.\n";
        }
    } while (!esSoloLetras(cad));
    return cad;
}

// Función: leerNombreCompleto
// Propósito: Lee y valida nombre completo (puede incluir espacios)
// Parámetros: msg - mensaje a mostrar
// Retorno: nombre completo válido
string leerNombreCompleto(const string& msg) {
    string cad;
    do {
        cout << msg;
        cin.ignore();
        getline(cin, cad);
        cad = trim(cad);
        if (!esSoloLetras(cad)) {
            cout << "Error: El nombre debe contener solo letras y espacios.\n";
        }
        if (cad.empty()) {
            cout << "Error: El nombre no puede estar vacío.\n";
        }
    } while (!esSoloLetras(cad) || cad.empty());
    return cad;
}

// Función: leerFecha
// Propósito: Lee y valida fecha formato AAAA-MM-DD
// Parámetros: msg - mensaje a mostrar
// Retorno: fecha válida
string leerFecha(const string& msg) {
    string cad;
    do {
        cout << msg;
        cin >> cad;
        cad = trim(cad);
        if (!esFechaValida(cad)) {
            cout << "Error: Fecha inválida. Use formato AAAA-MM-DD.\n";
        }
    } while (!esFechaValida(cad));
    return cad;
}

// Función: leerRUC
// Propósito: Lee y valida RUC peruano (11 dígitos)
// Parámetros: msg - mensaje a mostrar
// Retorno: RUC válido
string leerRUC(const string& msg) {
    string cad;
    do {
        cad = leerCadenaNumericaLongitud(msg, 11);
        if (!esRUCValido(cad)) {
            cout << "Error: RUC inválido. Verifique los primeros dígitos.\n";
        }
    } while (!esRUCValido(cad));
    return cad;
}

// Función: leerEmail
// Propósito: Lee y valida email
// Parámetros: msg - mensaje a mostrar
// Retorno: email válido
string leerEmail(const string& msg) {
    string cad;
    do {
        cout << msg;
        cin >> cad;
        cad = trim(cad);
        if (!esEmailValido(cad)) {
            cout << "Error: Email inválido. Use formato usuario@dominio.com\n";
        }
    } while (!esEmailValido(cad));
    return cad;
}

// Función: leerTelefono
// Propósito: Lee y valida teléfono
// Parámetros: msg - mensaje a mostrar
// Retorno: teléfono válido
string leerTelefono(const string& msg) {
    string cad;
    do {
        cad = leerCadenaNumerica(msg);
        if (!esTelefonoValido(cad)) {
            cout << "Error: Teléfono inválido. Debe tener 7 o 9 dígitos.\n";
        }
    } while (!esTelefonoValido(cad));
    return cad;
}

// Función: leerTexto
// Propósito: Lee cualquier texto sin validación específica
// Parámetros: msg - mensaje a mostrar
// Retorno: texto ingresado
string leerTexto(const string& msg) {
    string cad;
    cout << msg;
    cin.ignore();
    getline(cin, cad);
    return trim(cad);
}

// Función: leerTextoNoVacio
// Propósito: Lee texto asegurando que no esté vacío
// Parámetros: msg - mensaje a mostrar
// Retorno: texto no vacío
string leerTextoNoVacio(const string& msg) {
    string cad;
    do {
        cout << msg;
        cin.ignore();
        getline(cin, cad);
        cad = trim(cad);
        if (cad.empty()) {
            cout << "Error: El texto no puede estar vacío.\n";
        }
    } while (cad.empty());
    return cad;
}

// Función: confirmarAccion
// Propósito: Solicita confirmación Sí/No
// Parámetros: msg - mensaje a mostrar
// Retorno: true si confirma (S/s), false en caso contrario
bool confirmarAccion(const string& msg) {
    string respuesta;
    cout << msg << " (S/N): ";
    cin >> respuesta;
    respuesta = toUpper(trim(respuesta));
    return (respuesta == "S" || respuesta == "SI" || respuesta == "YES" || respuesta == "Y");
}