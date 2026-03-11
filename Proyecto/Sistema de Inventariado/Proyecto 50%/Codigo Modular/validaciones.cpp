#include <iostream>
#include <cctype>
#include <algorithm>
#include "validaciones.h"

using namespace std;

bool esNumero(const string& cad) {
    for (char c : cad)
        if (!isdigit(c)) return false;
    return !cad.empty();
}

bool esSoloLetras(const string& cad) {
    if (cad.empty()) return false;
    bool hayLetra = false;
    for (char c : cad) {
        if (!isalpha(c) && c != ' ') return false;
        if (isalpha(c)) hayLetra = true;
    }
    return hayLetra;
}

bool esFechaValida(const string& cad) {
    if (cad.length() != 10) return false;
    return isdigit(cad[0]) && isdigit(cad[1]) &&
           isdigit(cad[2]) && isdigit(cad[3]) &&
           cad[4] == '-' &&
           isdigit(cad[5]) && isdigit(cad[6]) &&
           cad[7] == '-' &&
           isdigit(cad[8]) && isdigit(cad[9]);
}

int leerEntero(const string& msg) {
    string cad;
    do {
        cout << msg;
        cin >> cad;
    } while (!esNumero(cad));
    return stoi(cad);
}

double leerDouble(const string& msg) {
    string cad;
    bool valido;
    do {
        valido = true;
        cout << msg;
        cin >> cad;
        for (char c : cad)
            if (!isdigit(c) && c != '.') valido = false;
        // Opcional: verificar que haya al menos un dígito y un solo punto
    } while (!valido);
    return stod(cad);
}

string leerCadenaNumerica(const string& msg) {
    string cad;
    do {
        cout << msg;
        cin >> cad;
    } while (!esNumero(cad));
    return cad;
}

string leerNombre(const string& msg) {
    string cad;
    do {
        cout << msg;
        getline(cin, cad);
    } while (!esSoloLetras(cad));
    return cad;
}

string leerFecha(const string& msg) {
    string cad;
    do {
        cout << msg;
        cin >> cad;
    } while (!esFechaValida(cad));
    return cad;
}