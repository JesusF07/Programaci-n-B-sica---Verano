#include "encriptacion.h"

// Función: hashPassword
// Propósito: Genera un hash numérico a partir de una contraseña
// Parámetros: password - contraseña en texto plano
// Retorno: Hash en formato string
string hashPassword(const string& password) {
    unsigned long hash = 5381;
    for (char c : password) {
        hash = ((hash << 5) + hash) + c;  // Algoritmo djb2
    }
    
    stringstream ss;
    ss << hash;
    return ss.str();
}

// Función: validarPassword
// Propósito: Compara una contraseña con su hash
// Parámetros: password - texto plano, hash - hash almacenado
// Retorno: true si coinciden, false si no
bool validarPassword(const string& password, const string& hash) {
    return hashPassword(password) == hash;
}

// Función: xorEncryptDecrypt
// Propósito: Encripta/Desencripta usando XOR (misma función para ambos)
// Parámetros: input - texto a procesar, key - clave de encriptación
// Retorno: Texto procesado
string xorEncryptDecrypt(const string& input, char key) {
    string resultado = input;
    for (size_t i = 0; i < input.length(); i++) {
        resultado[i] = input[i] ^ key;  // Operación XOR bit a bit
    }
    return resultado;
}