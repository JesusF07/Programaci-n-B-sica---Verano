#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

// ================= ESTRUCTURAS =================
struct Producto {
    string codigo;
    string descripcion;
    string unidad;
    int cantidad;
    double precioUnitario;
};

struct Factura {
    string numeroSerie;
    string rucCliente;
    string nombreCliente;
    string direccionCliente;
    string fecha;
    Producto* productos;
    int cantidadProductos;
};

struct Usuario {
    string username;
    string passwordHash;
};

// ================= FUNCIONES DE ENCRIPTACION SIMPLES =================

// Función simple de hash para contraseñas
string hashPassword(const string& password) {
    unsigned long hash = 5381;
    for (char c : password) {
        hash = ((hash << 5) + hash) + c;
    }
    
    stringstream ss;
    ss << hash;
    return ss.str();
}

// Función para validar contraseña
bool validarPassword(const string& password, const string& hash) {
    return hashPassword(password) == hash;
}

// Encriptación simple XOR (para datos no críticos)
string xorEncryptDecrypt(const string& input, char key = 'K') {
    string resultado = input;
    for (size_t i = 0; i < input.length(); i++) {
        resultado[i] = input[i] ^ key;
    }
    return resultado;
}

// ================= VALIDACIONES =================
bool esNumero(const string& cad) {
    if (cad.empty()) return false;
    for (char c : cad)
        if (!isdigit(c)) return false;
    return true;
}

bool esSoloLetras(const string& cad) {
    if (cad.empty()) return false;
    for (char c : cad)
        if (!isalpha(c) && c != ' ') return false;
    return true;
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
        cin.ignore();
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

// ================= FUNCION PARA GENERAR NUMERO DE SERIE =================
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

// ================= FUNCIONES DE ARCHIVO DE USUARIOS =================

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

int cargarUsuarios(Usuario*& usuarios) {
    ifstream file("usuarios.txt");
    if (!file) {
        // Crear usuario por defecto
        usuarios = new Usuario[1];
        usuarios[0].username = "admin";
        usuarios[0].passwordHash = hashPassword("1234");
        guardarUsuarios(usuarios, 1);
        return 1;
    }
    
    usuarios = new Usuario[10]; // Capacidad máxima 10 usuarios
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

// ================= LOGIN =================
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

// ================= FUNCION PARA CAMBIAR CONTRASENA =================
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
    
    // Buscar usuario
    int idx = -1;
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].username == user) {
            idx = i;
            break;
        }
    }
    
    if (idx == -1) {
        cout << "| Usuario no encontrado.\n";
        cout << "+--------------------------------------+\n";
        delete[] usuarios;
        return;
    }
    
    cout << "| Contrasena actual: ";
    string passActual;
    cin >> passActual;
    
    if (!validarPassword(passActual, usuarios[idx].passwordHash)) {
        cout << "| Contrasena actual incorrecta.\n";
        cout << "+--------------------------------------+\n";
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
        cout << "+--------------------------------------+\n";
        delete[] usuarios;
        return;
    }
    
    // Actualizar contraseña
    usuarios[idx].passwordHash = hashPassword(passNueva1);
    guardarUsuarios(usuarios, numUsuarios);
    
    cout << "+--------------------------------------+\n";
    cout << "| CONTRASENA CAMBIADA EXITOSAMENTE     |\n";
    cout << "+--------------------------------------+\n";
    
    delete[] usuarios;
}

// ================= VERIFICAR SI EL ARCHIVO EXISTE =================
bool archivoExiste(const string& nombreArchivo) {
    ifstream file(nombreArchivo);
    return file.good();
}

// ================= GUARDAR FACTURA (VERSIÓN SIMPLIFICADA) =================
void guardarFactura(const Factura& f) {
    ofstream file("facturas.txt", ios::app);
    
    if (!file) {
        cout << "Error al abrir el archivo para guardar.\n";
        return;
    }

    // Guardar en formato texto legible (pero con datos encriptados)
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

// ================= IMPRIMIR FACTURA =================
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

// ================= BUSCAR FACTURA =================
void buscarFactura() {
    if (!archivoExiste("facturas.txt")) {
        cout << "\nNo existen facturas registradas.\n";
        return;
    }

    ifstream file("facturas.txt");
    if (!file) {
        cout << "Error al abrir el archivo de facturas.\n";
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
        buscado = leerCadenaNumerica("RUC: ");
    } else if (op == 2) {
        buscado = leerNombre("Nombre: ");
    } else if (op == 3) {
        cout << "Numero de Serie: ";
        getline(cin, buscado);
    } else {
        cout << "Opcion no valida.\n";
        return;
    }

    string linea;
    bool encontrado = false;
    
    while (getline(file, linea)) {
        if (linea == "=== FACTURA ===") {
            Factura f;
            
            // Leer serie
            getline(file, linea);
            f.numeroSerie = linea.substr(6); // Después de "SERIE:"
            
            // Leer RUC
            getline(file, linea);
            f.rucCliente = xorEncryptDecrypt(linea.substr(4)); // Después de "RUC:"
            
            // Leer fecha
            getline(file, linea);
            f.fecha = linea.substr(6); // Después de "FECHA:"
            
            // Leer cliente
            getline(file, linea);
            f.nombreCliente = xorEncryptDecrypt(linea.substr(8)); // Después de "CLIENTE:"
            
            // Leer dirección
            getline(file, linea);
            f.direccionCliente = xorEncryptDecrypt(linea.substr(10)); // Después de "DIRECCION:"
            
            // Leer cantidad productos
            getline(file, linea);
            f.cantidadProductos = stoi(linea.substr(10)); // Después de "PRODUCTOS:"
            
            // Leer productos
            f.productos = new Producto[f.cantidadProductos];
            
            for (int i = 0; i < f.cantidadProductos; i++) {
                getline(file, linea);
                stringstream ss(linea);
                string campo;
                
                getline(ss, campo, '|');
                f.productos[i].codigo = xorEncryptDecrypt(campo);
                
                getline(ss, campo, '|');
                f.productos[i].descripcion = xorEncryptDecrypt(campo);
                
                getline(ss, campo, '|');
                f.productos[i].unidad = xorEncryptDecrypt(campo);
                
                getline(ss, campo, '|');
                f.productos[i].cantidad = stoi(campo);
                
                getline(ss, campo, '|');
                f.productos[i].precioUnitario = stod(campo);
            }
            
            // Leer separador
            getline(file, linea);
            
            // Verificar si coincide con la búsqueda
            if ((op == 1 && f.rucCliente == buscado) ||
                (op == 2 && f.nombreCliente == buscado) ||
                (op == 3 && f.numeroSerie == buscado)) {
                imprimirFactura(f);
                encontrado = true;
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
    }
}

// ================= REGISTRAR FACTURA =================
void registrarFactura() {
    Factura f;
    
    cout << "\n+--------------------------------------+\n";
    cout << "|      REGISTRAR NUEVA FACTURA         |\n";
    cout << "+--------------------------------------+\n";
    
    cin.ignore();

    f.numeroSerie = generarNumeroSerie();
    cout << "| Numero de Serie generado: " << f.numeroSerie << endl;
    cout << "+--------------------------------------+\n";
    
    f.rucCliente = leerCadenaNumerica("| RUC Cliente: ");
    f.fecha = leerFecha("| Fecha (AAAA-MM-DD): ");
    f.nombreCliente = leerNombre("| Nombre Cliente: ");

    cout << "| Direccion Cliente: ";
    getline(cin, f.direccionCliente);

    int n = leerEntero("| Cantidad de productos: ");
    f.cantidadProductos = n;
    f.productos = new Producto[n];

    for (int i = 0; i < n; i++) {
        cout << "\n+--------------------------------------+\n";
        cout << "| Producto " << i + 1 << endl;
        cout << "+--------------------------------------+\n";
        
        cout << "| Codigo: ";
        cin >> f.productos[i].codigo;
        cin.ignore();

        cout << "| Descripcion: ";
        getline(cin, f.productos[i].descripcion);

        cout << "| Unidad: ";
        cin >> f.productos[i].unidad;

        f.productos[i].cantidad = leerEntero("| Cantidad: ");
        f.productos[i].precioUnitario = leerDouble("| Precio Unitario: ");
    }

    guardarFactura(f);
    
    cout << "\n+--------------------------------------+\n";
    cout << "| FACTURA REGISTRADA EXITOSAMENTE      |\n";
    cout << "| Numero: " << f.numeroSerie << "           |\n";
    cout << "+--------------------------------------+\n";
    
    delete[] f.productos;
}

// ================= MOSTRAR MENU =================
void mostrarMenu() {
    cout << "\n+--------------------------------------+\n";
    cout << "|         SISTEMA DE FACTURACION       |\n";
    cout << "+--------------------------------------+\n";
    cout << "| 1. Registrar factura                 |\n";
    cout << "| 2. Buscar factura                    |\n";
    cout << "| 3. Cambiar contrasena                |\n";
    cout << "| 0. Salir                             |\n";
    cout << "+--------------------------------------+\n";
    cout << "Opcion: ";
}

// ================= MAIN =================
int main() {
    login();

    int op;
    do {
        mostrarMenu();
        cin >> op;

        switch(op) {
            case 1:
                registrarFactura();
                break;
            case 2:
                buscarFactura();
                break;
            case 3:
                cambiarPassword();
                break;
            case 0:
                cout << "\n+--------------------------------------+\n";
                cout << "|     ¡Gracias por usar el sistema!    |\n";
                cout << "+--------------------------------------+\n";
                break;
            default:
                cout << "\nOpcion no valida. Intente nuevamente.\n";
        }

    } while (op != 0);

    return 0;
}