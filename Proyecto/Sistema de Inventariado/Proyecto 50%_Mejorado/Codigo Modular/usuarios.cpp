#include "usuarios.h"
#include "encriptacion.h"
#include <iostream>
#include <fstream>
using namespace std;

// Función: guardarUsuarios
// Propósito: Guarda lista de usuarios en archivo
void guardarUsuarios(const Usuario* usuarios, int cantidad) {
    ofstream file("usuarios.txt");
    if (!file) {
        cout << "Error al guardar usuarios.\n";
        return;
    }
    
    for (int i = 0; i < cantidad; i++) {
        file << usuarios[i].username << endl;
        file << usuarios[i].passwordHash << endl;
    }
    file.close();
}

// Función: cargarUsuarios
// Propósito: Carga usuarios desde archivo, crea admin si no existe
int cargarUsuarios(Usuario*& usuarios) {
    ifstream file("usuarios.txt");
    if (!file) {
        usuarios = new Usuario[1];
        usuarios[0].username = "admin";
        usuarios[0].passwordHash = hashPassword("1234");
        guardarUsuarios(usuarios, 1);
        return 1;
    }
    
    usuarios = new Usuario[10];
    int count = 0;
    
    string linea;
    while (getline(file, linea) && count < 10) {
        if (linea.empty()) continue;
        usuarios[count].username = linea;
        if (getline(file, linea)) {
            usuarios[count].passwordHash = linea;
            count++;
        }
    }
    
    file.close();
    return count;
}

// Función: login
// Propósito: Controla acceso al sistema
void login() {
    Usuario* usuarios = nullptr;
    int numUsuarios = cargarUsuarios(usuarios);
    
    string user, pass;
    while (true) {
        cout << "+--------------------------------------+\n";
        cout << "|              LOGIN SISTEMA           |\n";
        cout << "+--------------------------------------+\n";
        cout << "| Usuario: ";
        cin >> user;
        cout << "| Clave: ";
        cin >> pass;

        bool accesoValido = false;
        for (int i = 0; i < numUsuarios; i++) {
            if (usuarios[i].username == user && 
                validarPassword(pass, usuarios[i].passwordHash)) {
                accesoValido = true;
                break;
            }
        }
        
        if (accesoValido) {
            cout << "+--------------------------------------+\n";
            cout << "|      ACCESO CONCEDIDO                |\n";
            cout << "+--------------------------------------+\n";
            delete[] usuarios;
            return;
        }
        
        cout << "+--------------------------------------+\n";
        cout << "| Usuario y/o contrasena incorrectos   |\n";
        cout << "+--------------------------------------+\n\n";
    }
}

// Función: cambiarPassword
// Propósito: Permite al usuario cambiar su contraseña
void cambiarPassword() {
    Usuario* usuarios = nullptr;
    int numUsuarios = cargarUsuarios(usuarios);
    
    if (numUsuarios == 0) {
        cout << "No hay usuarios registrados.\n";
        return;
    }
    
    cout << "\n+--------------------------------------+\n";
    cout << "|         CAMBIAR CONTRASENA           |\n";
    cout << "+--------------------------------------+\n";
    cout << "| Usuario: ";
    
    string user;
    cin >> user;
    
    int idx = -1;
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].username == user) {
            idx = i;
            break;
        }
    }
    
    if (idx == -1) {
        cout << "| Usuario no encontrado.\n";
        delete[] usuarios;
        return;
    }
    
    cout << "| Contrasena actual: ";
    string passActual;
    cin >> passActual;
    
    if (!validarPassword(passActual, usuarios[idx].passwordHash)) {
        cout << "| Contrasena actual incorrecta.\n";
        delete[] usuarios;
        return;
    }
    
    cout << "| Nueva contrasena: ";
    string passNueva1;
    cin >> passNueva1;
    
    cout << "| Confirmar nueva contrasena: ";
    string passNueva2;
    cin >> passNueva2;
    
    if (passNueva1 != passNueva2) {
        cout << "| Las contrasenas no coinciden.\n";
        delete[] usuarios;
        return;
    }
    
    usuarios[idx].passwordHash = hashPassword(passNueva1);
    guardarUsuarios(usuarios, numUsuarios);
    
    cout << "+--------------------------------------+\n";
    cout << "| CONTRASENA CAMBIADA EXITOSAMENTE     |\n";
    cout << "+--------------------------------------+\n";
    
    delete[] usuarios;
}