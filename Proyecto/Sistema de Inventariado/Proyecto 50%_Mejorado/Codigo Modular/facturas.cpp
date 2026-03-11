#include "facturas.h"
#include "validaciones.h"
#include "encriptacion.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace std;

// Función: generarNumeroSerie
// Propósito: Genera número de serie único para factura
string generarNumeroSerie() {
    static bool semillaInicializada = false;
    if (!semillaInicializada) {
        srand(time(0));
        semillaInicializada = true;
    }
    
    stringstream ss;
    int serie = rand() % 1000;
    
    ss << "F" << setw(3) << setfill('0') << serie << "-";
    for (int i = 0; i < 5; i++) {
        ss << (rand() % 10);
    }
    return ss.str();
}

// Función: archivoExiste
// Propósito: Verifica si un archivo existe
bool archivoExiste(const string& nombreArchivo) {
    ifstream file(nombreArchivo);
    return file.good();
}

// Función: guardarFactura
// Propósito: Guarda factura en archivo (datos sensibles encriptados)
void guardarFactura(const Factura& f) {
    ofstream file("facturas.txt", ios::app);
    if (!file) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    file << "=== FACTURA ===" << endl;
    file << "SERIE:" << f.numeroSerie << endl;
    file << "RUC:" << xorEncryptDecrypt(f.rucCliente) << endl;
    file << "FECHA:" << f.fecha << endl;
    file << "CLIENTE:" << xorEncryptDecrypt(f.nombreCliente) << endl;
    file << "DIRECCION:" << xorEncryptDecrypt(f.direccionCliente) << endl;
    file << "PRODUCTOS:" << f.cantidadProductos << endl;

    for (int i = 0; i < f.cantidadProductos; i++) {
        const Producto& p = f.productos[i];
        file << xorEncryptDecrypt(p.codigo) << "|"
             << xorEncryptDecrypt(p.descripcion) << "|"
             << xorEncryptDecrypt(p.unidad) << "|"
             << p.cantidad << "|"
             << fixed << setprecision(2) << p.precioUnitario << endl;
    }
    file << "----" << endl;
    file.close();
}

// Función: imprimirFactura
// Propósito: Muestra factura en pantalla con formato
void imprimirFactura(const Factura& f) {
    double total = 0;

    cout << "\n+==================================================================================+\n";
    cout << "|                     FACTURA ELECTRONICA                                           |\n";
    cout << "+==================================================================================+\n";
    cout << "| Numero Serie : " << f.numeroSerie << endl;
    cout << "| Fecha        : " << f.fecha << endl;
    cout << "| Cliente      : " << f.nombreCliente << endl;
    cout << "| RUC          : " << f.rucCliente << endl;
    cout << "| Direccion    : " << f.direccionCliente << endl;
    cout << "+----------------------------------------------------------------------------------+\n";
    cout << "| Cant | Und | Codigo | Descripcion                 | P.Unit | Subtotal           |\n";
    cout << "+----------------------------------------------------------------------------------+\n";

    for (int i = 0; i < f.cantidadProductos; i++) {
        Producto p = f.productos[i];
        double sub = p.cantidad * p.precioUnitario;
        total += sub;

        cout << "| " << setw(4) << p.cantidad << " | "
             << setw(3) << p.unidad << " | "
             << setw(6) << p.codigo << " | "
             << setw(25) << left << p.descripcion << right << " | "
             << setw(6) << fixed << setprecision(2) << p.precioUnitario << " | "
             << setw(15) << sub << " |\n";
    }

    double igv = total * 0.18;
    cout << "+----------------------------------------------------------------------------------+\n";
    cout << "| Op. Gravada : " << setw(63) << right << total << " |\n";
    cout << "| IGV (18%)   : " << setw(63) << right << igv << " |\n";
    cout << "| TOTAL       : " << setw(63) << right << total + igv << " |\n";
    cout << "+==================================================================================+\n";
}

// Función auxiliar: extraerValorSeguro
// Propósito: Extrae el valor después del prefijo de forma SEGURA
string extraerValorSeguro(const string& linea, const string& prefijo) {
    // Verificar que la línea comience con el prefijo
    if (linea.length() <= prefijo.length()) {
        return ""; // Línea demasiado corta
    }
    
    if (linea.substr(0, prefijo.length()) != prefijo) {
        return ""; // No comienza con el prefijo esperado
    }
    
    // Extraer el valor después del prefijo
    return linea.substr(prefijo.length());
}

// Función: buscarFactura (VERSIÓN DEFINITIVA - SIN ERRORES)
// Propósito: Busca y muestra facturas por diferentes criterios
void buscarFactura() {
    if (!archivoExiste("facturas.txt")) {
        cout << "\nNo existen facturas registradas.\n";
        return;
    }

    ifstream file("facturas.txt");
    if (!file) {
        cout << "Error al abrir archivo.\n";
        return;
    }

    cout << "\n+--------------------------------------+\n";
    cout << "|         BUSCAR FACTURA               |\n";
    cout << "+--------------------------------------+\n";
    cout << "| 1. Buscar por RUC                    |\n";
    cout << "| 2. Buscar por Nombre                 |\n";
    cout << "| 3. Buscar por Numero de Serie        |\n";
    cout << "+--------------------------------------+\n";
    cout << "Opcion: ";
    
    int op;
    cin >> op;
    cin.ignore();

    string buscado;
    if (op == 1) {
        cout << "RUC: ";
        getline(cin, buscado);
    } else if (op == 2) {
        cout << "Nombre: ";
        getline(cin, buscado);
    } else if (op == 3) {
        cout << "Numero de Serie: ";
        getline(cin, buscado);
    } else {
        cout << "Opcion no valida.\n";
        return;
    }

    string linea;
    bool encontrado = false;
    int facturaActual = 0;
    
    while (getline(file, linea)) {
        // Buscar inicio de factura
        if (linea.find("=== FACTURA ===") != string::npos) {
            facturaActual++;
            Factura f;
            bool lecturaOK = true;
            string valor;
            
            // ===== LEER SERIE =====
            if (!getline(file, linea) || linea.empty()) continue;
            valor = extraerValorSeguro(linea, "SERIE:");
            if (valor.empty()) continue;
            f.numeroSerie = valor;
            
            // ===== LEER RUC =====
            if (!getline(file, linea) || linea.empty()) continue;
            valor = extraerValorSeguro(linea, "RUC:");
            if (valor.empty()) continue;
            f.rucCliente = xorEncryptDecrypt(valor);
            
            // ===== LEER FECHA =====
            if (!getline(file, linea) || linea.empty()) continue;
            valor = extraerValorSeguro(linea, "FECHA:");
            if (valor.empty()) continue;
            f.fecha = valor;
            
            // ===== LEER CLIENTE =====
            if (!getline(file, linea) || linea.empty()) continue;
            valor = extraerValorSeguro(linea, "CLIENTE:");
            if (valor.empty()) continue;
            f.nombreCliente = xorEncryptDecrypt(valor);
            
            // ===== LEER DIRECCION =====
            if (!getline(file, linea) || linea.empty()) continue;
            valor = extraerValorSeguro(linea, "DIRECCION:");
            if (valor.empty()) continue;
            f.direccionCliente = xorEncryptDecrypt(valor);
            
            // ===== LEER PRODUCTOS =====
            if (!getline(file, linea) || linea.empty()) continue;
            valor = extraerValorSeguro(linea, "PRODUCTOS:");
            if (valor.empty()) continue;
            
            try {
                f.cantidadProductos = stoi(valor);
            } catch (...) {
                continue;
            }
            
            // ===== LEER PRODUCTOS =====
            f.productos = new Producto[f.cantidadProductos];
            
            for (int i = 0; i < f.cantidadProductos; i++) {
                if (!getline(file, linea) || linea.empty()) {
                    lecturaOK = false;
                    break;
                }
                
                stringstream ss(linea);
                string campo;
                
                try {
                    // Código
                    if (!getline(ss, campo, '|')) { lecturaOK = false; break; }
                    f.productos[i].codigo = xorEncryptDecrypt(campo);
                    
                    // Descripción
                    if (!getline(ss, campo, '|')) { lecturaOK = false; break; }
                    f.productos[i].descripcion = xorEncryptDecrypt(campo);
                    
                    // Unidad
                    if (!getline(ss, campo, '|')) { lecturaOK = false; break; }
                    f.productos[i].unidad = xorEncryptDecrypt(campo);
                    
                    // Cantidad
                    if (!getline(ss, campo, '|')) { lecturaOK = false; break; }
                    f.productos[i].cantidad = stoi(campo);
                    
                    // Precio
                    if (!getline(ss, campo, '|')) { lecturaOK = false; break; }
                    f.productos[i].precioUnitario = stod(campo);
                    
                } catch (const exception& e) {
                    lecturaOK = false;
                    break;
                }
            }
            
            // Leer separador
            getline(file, linea);
            
            if (lecturaOK) {
                // Verificar si coincide con la búsqueda
                bool coincide = false;
                
                switch(op) {
                    case 1: // Buscar por RUC
                        if (f.rucCliente == buscado) coincide = true;
                        break;
                    case 2: // Buscar por Nombre
                        if (f.nombreCliente == buscado) coincide = true;
                        break;
                    case 3: // Buscar por Numero de Serie
                        if (f.numeroSerie == buscado) coincide = true;
                        break;
                }
                
                if (coincide) {
                    cout << "\n" << string(50, '=') << endl;
                    cout << "Factura encontrada #" << facturaActual << endl;
                    imprimirFactura(f);
                    encontrado = true;
                }
            }
            
            delete[] f.productos;
            if (encontrado) break;
        }
    }
    
    file.close();
    
    if (!encontrado) {
        cout << "\n+--------------------------------------+\n";
        cout << "|     Factura no encontrada            |\n";
        cout << "+--------------------------------------+\n";
    } else {
        cout << "\n+--------------------------------------+\n";
        cout << "|     Busqueda completada              |\n";
        cout << "+--------------------------------------+\n";
    }
}

// Función: registrarFactura
// Propósito: Captura datos del cliente y productos para nueva factura
void registrarFactura() {
    Factura f;
    
    cout << "\n+--------------------------------------+\n";
    cout << "|      REGISTRAR NUEVA FACTURA         |\n";
    cout << "+--------------------------------------+\n";
    
    f.numeroSerie = generarNumeroSerie();
    cout << "| Numero de Serie generado: " << f.numeroSerie << endl;
    cout << "+--------------------------------------+\n";
    
    // Usar las funciones de validación
    cout << "| RUC Cliente (11 digitos): ";
    cin >> f.rucCliente;
    cin.ignore();
    
    cout << "| Fecha (AAAA-MM-DD): ";
    getline(cin, f.fecha);
    
    cout << "| Nombre Cliente: ";
    getline(cin, f.nombreCliente);
    
    cout << "| Direccion Cliente: ";
    getline(cin, f.direccionCliente);

    cout << "| Cantidad de productos: ";
    cin >> f.cantidadProductos;
    cin.ignore();
    
    if (f.cantidadProductos <= 0) {
        cout << "Error: Debe ingresar al menos 1 producto.\n";
        return;
    }
    
    f.productos = new Producto[f.cantidadProductos];

    for (int i = 0; i < f.cantidadProductos; i++) {
        cout << "\n+--------------------------------------+\n";
        cout << "| Producto " << i + 1 << endl;
        cout << "+--------------------------------------+\n";
        
        cout << "| Codigo: ";
        getline(cin, f.productos[i].codigo);
        
        cout << "| Descripcion: ";
        getline(cin, f.productos[i].descripcion);
        
        cout << "| Unidad: ";
        getline(cin, f.productos[i].unidad);
        
        cout << "| Cantidad: ";
        cin >> f.productos[i].cantidad;
        
        cout << "| Precio Unitario: S/. ";
        cin >> f.productos[i].precioUnitario;
        cin.ignore();
        
        // Validaciones básicas
        if (f.productos[i].cantidad <= 0) {
            cout << "Error: Cantidad debe ser mayor a 0. Se asignara 1.\n";
            f.productos[i].cantidad = 1;
        }
        
        if (f.productos[i].precioUnitario <= 0) {
            cout << "Error: Precio debe ser mayor a 0. Se asignara 1.0.\n";
            f.productos[i].precioUnitario = 1.0;
        }
    }

    guardarFactura(f);
    
    cout << "\n+--------------------------------------+\n";
    cout << "| FACTURA REGISTRADA EXITOSAMENTE      |\n";
    cout << "| Numero: " << f.numeroSerie << endl;
    cout << "+--------------------------------------+\n";
    
    delete[] f.productos;
}