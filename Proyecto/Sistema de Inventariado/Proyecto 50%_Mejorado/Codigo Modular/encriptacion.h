#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H

#include <string>
#include <sstream>
using namespace std;

// ================= PROTOTIPOS =================
string hashPassword(const string& password);
bool validarPassword(const string& password, const string& hash);
string xorEncryptDecrypt(const string& input, char key = 'K');

#endif