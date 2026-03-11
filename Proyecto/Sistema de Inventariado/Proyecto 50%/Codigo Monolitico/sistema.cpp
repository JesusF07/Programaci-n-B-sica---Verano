#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>

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
    string rucCliente;
    string nombreCliente;
    string direccionCliente;
    string fecha;
    vector<Producto> productos;
};

// ================= VALIDACIONES =================
bool esNumero(const string& cad) {
    for (char c : cad)
        if (!isdigit(c)) return false;
    return !cad.empty();
}

bool esSoloLetras(const string& cad) {
    for (char c : cad)
        if (!isalpha(c) && c != ' ') return false;
    return !cad.empty();
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

        if (user == "admin" && pass == "1234") return;
        cout << "Usuario y/o contrasena incorrecta\n\n";
    }
}

// ================= GUARDAR FACTURA =================
void guardarFactura(const Factura& f) {
    ofstream file("facturas.txt", ios::app);

    file << f.rucCliente << endl;
    file << f.fecha << endl;
    file << f.nombreCliente << endl;
    file << f.direccionCliente << endl;
    file << f.productos.size() << endl;

    for (const auto& p : f.productos) {
        file << p.codigo << "|"
             << p.descripcion << "|"
             << p.unidad << "|"
             << p.cantidad << "|"
             << p.precioUnitario << endl;
    }
    file << "----" << endl;
}

// ================= IMPRIMIR FACTURA =================
void imprimirFactura(const Factura& f) {
    double total = 0;

    cout << "\n+==================================================================================+\n";
    cout << "| FACTURA ELECTRONICA                                                             |\n";
    cout << "+==================================================================================+\n";
    cout << "| Fecha      : " << f.fecha << endl;
    cout << "| Cliente    : " << f.nombreCliente << endl;
    cout << "| RUC        : " << f.rucCliente << endl;
    cout << "| Direccidn  : " << f.direccionCliente << endl;
    cout << "+----------------------------------------------------------------------------------+\n";
    cout << "| Cant | Und | Codigo | Descripcion                 | P.Unit | Subtotal           |\n";
    cout << "+----------------------------------------------------------------------------------+\n";

    for (const auto& p : f.productos) {
        double sub = p.cantidad * p.precioUnitario;
        total += sub;

        cout << setw(5) << p.cantidad << "  "
             << setw(4) << p.unidad << " "
             << setw(7) << p.codigo << "  "
             << setw(25) << left << p.descripcion << right
             << setw(9) << fixed << setprecision(2) << p.precioUnitario
             << setw(12) << sub << endl;
    }

    double igv = total * 0.18;

    cout << "+----------------------------------------------------------------------------------+\n";
    cout << "OP. GRAVADA : " << total << endl;
    cout << "IGV (18%)   : " << igv << endl;
    cout << "TOTAL       : " << total + igv << endl;
    cout << "+==================================================================================+\n";
}

// ================= BUSCAR FACTURA =================
void buscarFactura() {
    ifstream file("facturas.txt");
    if (!file) {
        cout << "No existen facturas registradas.\n";
        return;
    }

    cout << "1. Buscar por RUC\n";
    cout << "2. Buscar por Nombre\n";
    cout << "Opcion: ";
    int op;
    cin >> op;
    cin.ignore();

    string buscado;
    if (op == 1)
        buscado = leerCadenaNumerica("RUC: ");
    else if (op == 2)
        buscado = leerNombre("Nombre: ");
    else
        return;

    while (true) {
        Factura f;
        if (!getline(file, f.rucCliente)) break;
        getline(file, f.fecha);
        getline(file, f.nombreCliente);
        getline(file, f.direccionCliente);

        int n;
        file >> n;
        file.ignore();

        f.productos.clear();
        for (int i = 0; i < n; i++) {
            Producto p;
            getline(file, p.codigo, '|');
            getline(file, p.descripcion, '|');
            getline(file, p.unidad, '|');
            file >> p.cantidad;
            file.ignore();
            file >> p.precioUnitario;
            file.ignore();
            f.productos.push_back(p);
        }

        string separador;
        getline(file, separador);

        if ((op == 1 && f.rucCliente == buscado) ||
            (op == 2 && f.nombreCliente == buscado)) {
            imprimirFactura(f);
            return;
        }
    }

    cout << "Factura no encontrada.\n";
}

// ================= REGISTRAR FACTURA =================
void registrarFactura() {
    Factura f;
    cin.ignore();

    f.rucCliente = leerCadenaNumerica("RUC Cliente: ");
    f.fecha = leerFecha("Fecha (AAAA-MM-DD): ");
    cin.ignore();
    f.nombreCliente = leerNombre("Nombre Cliente: ");

    cout << "Direccion Cliente: ";
    getline(cin, f.direccionCliente);

    int n = leerEntero("Cantidad de productos: ");

    for (int i = 0; i < n; i++) {
        Producto p;
        cout << "\nProducto " << i + 1 << endl;
        cout << "Codigo: ";
        cin >> p.codigo;
        cin.ignore();

        cout << "Descripcion: ";
        getline(cin, p.descripcion);

        cout << "Unidad: ";
        cin >> p.unidad;

        p.cantidad = leerEntero("Cantidad: ");
        p.precioUnitario = leerDouble("Precio Unitario: ");

        f.productos.push_back(p);
    }

    guardarFactura(f);
    cout << "Factura registrada correctamente.\n";
}

// ================= MAIN =================
int main() {
    login();

    int op;
    do {
        cout << "\n1. Registrar factura\n";
        cout << "2. Buscar factura\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        if (op == 1) registrarFactura();
        else if (op == 2) buscarFactura();

    } while (op != 0);

    return 0;
}