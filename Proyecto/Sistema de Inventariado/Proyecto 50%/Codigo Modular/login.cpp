#include <iostream>
#include <string>
#include "login.h"

using namespace std;

void login() {
    string user, pass;

    while (true) {
        cout << "+--------------------------------------+\n";
        cout << "|              LOGIN SISTEMA           |\n";
        cout << "+--------------------------------------+\n";
        cout << "| Usuario : ";
        cin >> user;
        cout << "| Clave   : ";
        cin >> pass;

        if (user == "admin" && pass == "1234") return;
        cout << "Usuario y/o contrasena incorrecta\n\n";
    }
}