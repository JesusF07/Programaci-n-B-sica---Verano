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
    // Inicializar la semilla para números aleatorios solo una vez
    static bool semillaInicializada = false;
    if (!semillaInicializada) {
        srand(time(0));
        semillaInicializada = true;
    }
    
    // Formato: F001-12345 (3 dígitos de serie + 5 dígitos aleatorios)
    stringstream ss;
    
    // Generar número de serie más aleatorio usando combinación de tiempo y rand
    int serie = rand() % 1000;  // 0-999
    int num1 = rand() % 10;
    int num2 = rand() % 10;
    int num3 = rand() % 10;
    int num4 = rand() % 10;
    int num5 = rand() % 10;
    
    ss << "F" << setw(3) << setfill('0') << serie << "-"
       << num1 << num2 << num3 << num4 << num5;
    
    return ss.str();
}

// ================= LOGIN =================
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

        if (user == "admin" && pass == "1234") {
            cout << "+--------------------------------------+\n";
            cout << "|         ACCESO CONCEDIDO             |\n";
            cout << "+--------------------------------------+\n";
            return;
        }
        cout << "| Usuario y/o contrasena incorrecta      |\n";
        cout << "+--------------------------------------+\n\n";
    }
}

// ================= VERIFICAR SI EL ARCHIVO EXISTE =================
bool archivoExiste(const string& nombreArchivo) {
    ifstream file(nombreArchivo);
    return file.good();
}

// ================= GUARDAR FACTURA =================
void guardarFactura(const Factura& f) {
    ofstream file("facturas.txt", ios::app);
    
    if (!file) {
        cout << "Error al abrir el archivo para guardar.\n";
        return;
    }

    file << f.numeroSerie << endl;
    file << f.rucCliente << endl;
    file << f.fecha << endl;
    file << f.nombreCliente << endl;
    file << f.direccionCliente << endl;
    file << f.cantidadProductos << endl;

    for (int i = 0; i < f.cantidadProductos; i++) {
        const Producto& p = f.productos[i];
        file << p.codigo << "|"
             << p.descripcion << "|"
             << p.unidad << "|"
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

    bool encontrado = false;
    
    while (file) {
        Factura f;
        
        // Leer número de serie
        if (!getline(file, f.numeroSerie)) break;
        if (f.numeroSerie == "----") continue; // Saltar separadores
        
        // Leer datos básicos
        getline(file, f.rucCliente);
        getline(file, f.fecha);
        getline(file, f.nombreCliente);
        getline(file, f.direccionCliente);
        
        // Leer cantidad de productos
        string cantStr;
        getline(file, cantStr);
        if (cantStr.empty()) break;
        
        try {
            f.cantidadProductos = stoi(cantStr);
        } catch (...) {
            // Si hay error, intentar leer el siguiente registro
            continue;
        }
        
        // Leer productos
        f.productos = new Producto[f.cantidadProductos];
        bool lecturaCorrecta = true;
        
        for (int i = 0; i < f.cantidadProductos; i++) {
            string linea;
            getline(file, linea);
            
            if (linea.empty()) {
                lecturaCorrecta = false;
                break;
            }
            
            stringstream ss(linea);
            Producto& p = f.productos[i];
            
            getline(ss, p.codigo, '|');
            getline(ss, p.descripcion, '|');
            getline(ss, p.unidad, '|');
            
            string cantidadStr, precioStr;
            getline(ss, cantidadStr, '|');
            getline(ss, precioStr, '|');
            
            try {
                p.cantidad = stoi(cantidadStr);
                p.precioUnitario = stod(precioStr);
            } catch (...) {
                lecturaCorrecta = false;
                break;
            }
        }
        
        // Leer separador
        string separador;
        getline(file, separador);
        
        if (lecturaCorrecta) {
            // Verificar si coincide con la búsqueda
            if ((op == 1 && f.rucCliente == buscado) ||
                (op == 2 && f.nombreCliente == buscado) ||
                (op == 3 && f.numeroSerie == buscado)) {
                imprimirFactura(f);
                encontrado = true;
            }
        }
        
        delete[] f.productos;
        
        if (encontrado) break;
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
    
    cin.ignore(); // Limpiar buffer

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