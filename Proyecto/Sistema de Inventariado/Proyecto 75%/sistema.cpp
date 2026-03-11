#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

// ================= VALIDACIONES =================
class Validador {
public:
    static bool esNumero(const string& cad) {
        for (char c : cad)
            if (!isdigit(c)) return false;
        return !cad.empty();
    }

    static bool esSoloLetras(const string& cad) {
        for (char c : cad)
            if (!isalpha(c) && c != ' ') return false;
        return !cad.empty();
    }

    static bool esFechaValida(const string& cad) {
        return cad.length() == 10 &&
               isdigit(cad[0]) && isdigit(cad[1]) &&
               isdigit(cad[2]) && isdigit(cad[3]) &&
               cad[4] == '-' &&
               isdigit(cad[5]) && isdigit(cad[6]) &&
               cad[7] == '-' &&
               isdigit(cad[8]) && isdigit(cad[9]);
    }

    static int leerEntero(const string& msg) {
        string cad;
        do {
            cout << msg;
            cin >> cad;
        } while (!esNumero(cad));
        return stoi(cad);
    }

    static double leerDouble(const string& msg) {
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

    static string leerCadenaNumerica(const string& msg) {
        string cad;
        do {
            cout << msg;
            cin >> cad;
        } while (!esNumero(cad));
        return cad;
    }

    static string leerNombre(const string& msg) {
        string cad;
        do {
            cout << msg;
            getline(cin, cad);
        } while (!esSoloLetras(cad));
        return cad;
    }

    static string leerFecha(const string& msg) {
        string cad;
        do {
            cout << msg;
            cin >> cad;
        } while (!esFechaValida(cad));
        return cad;
    }
};

// ================= PRODUCTO =================
class Producto {
private:
    string codigo;
    string descripcion;
    string unidad;
    int cantidad;
    double precioUnitario;

public:
    void leer() {
        cout << "Codigo: ";
        cin >> codigo;
        cin.ignore();

        cout << "Descripcion: ";
        getline(cin, descripcion);

        cout << "Unidad: ";
        cin >> unidad;

        cantidad = Validador::leerEntero("Cantidad: ");
        precioUnitario = Validador::leerDouble("Precio Unitario: ");
    }

    double subtotal() const {
        return cantidad * precioUnitario;
    }

    void guardar(ofstream& file) const {
        file << codigo << "|"
             << descripcion << "|"
             << unidad << "|"
             << cantidad << "|"
             << precioUnitario << endl;
    }

    void cargar(ifstream& file) {
        getline(file, codigo, '|');
        getline(file, descripcion, '|');
        getline(file, unidad, '|');
        file >> cantidad;
        file.ignore();
        file >> precioUnitario;
        file.ignore();
    }

    void imprimir() const {
        cout << setw(5) << cantidad << "  "
             << setw(4) << unidad << " "
             << setw(7) << codigo << "  "
             << setw(25) << left << descripcion << right
             << setw(9) << fixed << setprecision(2) << precioUnitario
             << setw(12) << subtotal() << endl;
    }
};

// ================= FACTURA =================
class Factura {
private:
    string rucCliente;
    string nombreCliente;
    string direccionCliente;
    string fecha;
    vector<Producto> productos;

public:
    void leer() {
        cin.ignore();
        rucCliente = Validador::leerCadenaNumerica("RUC Cliente: ");
        fecha = Validador::leerFecha("Fecha (AAAA-MM-DD): ");
        cin.ignore();
        nombreCliente = Validador::leerNombre("Nombre Cliente: ");

        cout << "Direccion Cliente: ";
        getline(cin, direccionCliente);

        int n = Validador::leerEntero("Cantidad de productos: ");
        productos.clear();

        for (int i = 0; i < n; i++) {
            cout << "\nProducto " << i + 1 << endl;
            Producto p;
            p.leer();
            productos.push_back(p);
        }
    }

    void guardar() const {
        ofstream file("facturas.txt", ios::app);

        file << rucCliente << endl;
        file << fecha << endl;
        file << nombreCliente << endl;
        file << direccionCliente << endl;
        file << productos.size() << endl;

        for (const auto& p : productos)
            p.guardar(file);

        file << "----" << endl;
    }

    bool cargar(ifstream& file) {
        if (!getline(file, rucCliente)) return false;
        getline(file, fecha);
        getline(file, nombreCliente);
        getline(file, direccionCliente);

        int n;
        file >> n;
        file.ignore();

        productos.clear();
        for (int i = 0; i < n; i++) {
            Producto p;
            p.cargar(file);
            productos.push_back(p);
        }

        string sep;
        getline(file, sep);
        return true;
    }

    void imprimir() const {
        double total = 0;

        cout << "\n+==================================================================================+\n";
        cout << "| FACTURA ELECTRONICA                                                             |\n";
        cout << "+==================================================================================+\n";
        cout << "| Fecha      : " << fecha << endl;
        cout << "| Cliente    : " << nombreCliente << endl;
        cout << "| RUC        : " << rucCliente << endl;
        cout << "| Dirección  : " << direccionCliente << endl;
        cout << "+----------------------------------------------------------------------------------+\n";
        cout << "| Cant | Und | Código | Descripción                 | P.Unit | Subtotal           |\n";
        cout << "+----------------------------------------------------------------------------------+\n";

        for (const auto& p : productos) {
            p.imprimir();
            total += p.subtotal();
        }

        double igv = total * 0.18;

        cout << "+----------------------------------------------------------------------------------+\n";
        cout << "OP. GRAVADA : " << total << endl;
        cout << "IGV (18%)   : " << igv << endl;
        cout << "TOTAL       : " << total + igv << endl;
        cout << "+==================================================================================+\n";
    }

    bool coincideRuc(const string& ruc) const { return rucCliente == ruc; }
    bool coincideNombre(const string& nombre) const { return nombreCliente == nombre; }
};

// ================= SISTEMA =================
class SistemaFacturacion {
private:
    void mostrarLoginUI() {
        cout << "+--------------------------------------+\n";
        cout << "|              LOGIN SISTEMA           |\n";
        cout << "+--------------------------------------+\n";
    }

    void mostrarMenuUI() {
        cout << "\n+--------------------------------------+\n";
        cout << "|           MENU PRINCIPAL             |\n";
        cout << "+--------------------------------------+\n";
        cout << "| 1. Registrar factura                |\n";
        cout << "| 2. Buscar factura                   |\n";
        cout << "| 0. Salir                             |\n";
        cout << "+--------------------------------------+\n";
        cout << "Opcion: ";
    }

public:
    // ================= LOGIN =================
    void login() {
        string user, pass;

        while (true) {
            mostrarLoginUI();
            cout << "| Usuario : ";
            cin >> user;
            cout << "| Clave   : ";
            cin >> pass;

            if (user == "admin" && pass == "1234") return;
            cout << "Usuario y/o contrasena incorrecta\n\n";
        }
    }

    // ================= REGISTRAR FACTURA =================
    void registrarFactura() {
        Factura f;
        f.leer();
        f.guardar();
        cout << "Factura registrada correctamente.\n";
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
            buscado = Validador::leerCadenaNumerica("RUC: ");
        else if (op == 2)
            buscado = Validador::leerNombre("Nombre: ");
        else
            return;

        Factura f;
        while (f.cargar(file)) {
            if ((op == 1 && f.coincideRuc(buscado)) ||
                (op == 2 && f.coincideNombre(buscado))) {
                f.imprimir();
                return;
            }
        }

        cout << "Factura no encontrada.\n";
    }

    void menu() {
        int op;
        do {
            mostrarMenuUI();
            cin >> op;

            if (op == 1) registrarFactura();
            else if (op == 2) buscarFactura();

        } while (op != 0);
    }
};

// ================= MAIN =================
int main() {
    SistemaFacturacion sistema;
    sistema.login();
    sistema.menu();
    return 0;
}