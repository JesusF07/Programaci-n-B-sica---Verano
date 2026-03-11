#ifndef USUARIOS_H
#define USUARIOS_H

#include "estructuras.h"

// ================= PROTOTIPOS =================
void guardarUsuarios(const Usuario* usuarios, int cantidad);
int cargarUsuarios(Usuario*& usuarios);
void login();
void cambiarPassword();

#endif