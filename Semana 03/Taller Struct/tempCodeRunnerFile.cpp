#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ================= ESTRUCTURA =================

struct Producto {
    int codigo;
    string nombre;
    float precio;
    int stock;
};

const int MAX = 5;
Producto productos[MAX];
int cantidad = 0;

// ================= UTILIDADES =================

void limpiarEntrada() {
    cin.clear();
    cin.ignore(1000, '\n');
}

bool codigoExiste(int cod) {
    for (int i = 0; i < cantidad; i++)
        if (productos[i].codigo == cod)
            return true;
    return false;
}

bool nombreExiste(const string& nom) {
    for (int i = 0; i < cantidad; i++)
        if (productos[i].nombre == nom)
            return true;
    return false;
}

int leerOpcionMenu() {
    int op;
    while (true) {
        cout << "Opcion: ";
        if (cin >> op) return op;
        else {
            cout << "Entrada invalida. Ingrese solo numeros.\n";
            limpiarEntrada();
        }
    }
}

// ================= ARCHIVOS =================

void guardarEnArchivo() {
    ofstream archivo("productos.txt");
    for (int i = 0; i < cantidad; i++)
        archivo << productos[i].codigo << " "
                << productos[i].nombre << " "
                << productos[i].precio << " "
                << productos[i].stock << endl;
    archivo.close();
}

void cargarDesdeArchivo() {
    ifstream archivo("productos.txt");
    if (!archivo.is_open()) return;

    cantidad = 0;
    while (archivo >> productos[cantidad].codigo
                  >> productos[cantidad].nombre
                  >> productos[cantidad].precio
                  >> productos[cantidad].stock) {
        cantidad++;
        if (cantidad == MAX) break;
    }
    archivo.close();
}

// ================= FUNCIONES =================

void registrarProducto() {
    if (cantidad >= MAX) { cout << "Inventario lleno.\n"; return; }

    Producto p;
    do {
        cout << "Codigo (entero positivo y unico): ";
        if (!(cin >> p.codigo) || p.codigo <= 0 || codigoExiste(p.codigo)) {
            cout << "Codigo invalido o repetido.\n";
            limpiarEntrada();
        } else break;
    } while (true);

    do {
        cout << "Nombre (sin espacios y unico): ";
        cin >> p.nombre;
        if (p.nombre.empty()) cout << "El nombre no puede estar vacio.\n";
        else if (nombreExiste(p.nombre)) cout << "El nombre ya existe. Ingrese otro.\n";
        else break;
    } while (true);

    do {
        cout << "Precio (> 0): ";
        if (!(cin >> p.precio) || p.precio <= 0) {
            cout << "Precio invalido.\n";
            limpiarEntrada();
        } else break;
    } while (true);

    do {
        cout << "Stock (>= 0): ";
        if (!(cin >> p.stock) || p.stock < 0) {
            cout << "Stock invalido.\n";
            limpiarEntrada();
        } else break;
    } while (true);

    productos[cantidad++] = p;
    guardarEnArchivo();
    cout << "Producto registrado correctamente.\n";
}

void mostrarProductos() {
    if (cantidad == 0) { cout << "No hay productos registrados.\n"; return; }
    for (int i = 0; i < cantidad; i++) {
        cout << "\nCodigo: " << productos[i].codigo;
        cout << "\nNombre: " << productos[i].nombre;
        cout << "\nPrecio: " << productos[i].precio;
        cout << "\nStock: " << productos[i].stock;
        cout << "\n---------------------------";
    }
}

void buscarPorCodigo() {
    int cod;
    cout << "Ingrese codigo: ";
    if (!(cin >> cod)) { limpiarEntrada(); cout << "Entrada invalida.\n"; return; }

    for (int i = 0; i < cantidad; i++) {
        if (productos[i].codigo == cod) {
            cout << "Producto encontrado:\n";
            cout << "Nombre: " << productos[i].nombre << "\n";
            cout << "Precio: " << productos[i].precio << "\n";
            cout << "Stock: " << productos[i].stock << "\n";
            return;
        }
    }
    cout << "No encontrado.\n";
}

void buscarPorNombre() {
    string nom;
    cout << "Ingrese nombre: ";
    cin >> nom;

    for (int i = 0; i < cantidad; i++) {
        if (productos[i].nombre == nom) {
            cout << "Producto encontrado:\n";
            cout << "Codigo: " << productos[i].codigo << "\n";
            cout << "Precio: " << productos[i].precio << "\n";
            cout << "Stock: " << productos[i].stock << "\n";
            return;
        }
    }
    cout << "No encontrado.\n";
}

void actualizarProducto() {
    if (cantidad == 0) { cout << "No hay productos registrados.\n"; return; }

    int cod;
    cout << "Ingrese el codigo del producto a actualizar: ";
    if (!(cin >> cod)) { limpiarEntrada(); cout << "Entrada invalida.\n"; return; }

    for (int i = 0; i < cantidad; i++) {
        if (productos[i].codigo == cod) {
            cout << "\nProducto encontrado:\n";
            cout << "Nombre: " << productos[i].nombre << "\n";
            cout << "Precio: " << productos[i].precio << "\n";
            cout << "Stock: " << productos[i].stock << "\n";

            string nuevoNombre;
            do {
                cout << "Nuevo nombre (sin espacios y unico): ";
                cin >> nuevoNombre;
                if (nuevoNombre.empty()) cout << "Nombre vacio.\n";
                else if (nuevoNombre != productos[i].nombre && nombreExiste(nuevoNombre))
                    cout << "Nombre ya existe.\n";
                else { productos[i].nombre = nuevoNombre; break; }
            } while (true);

            float nuevoPrecio;
            do {
                cout << "Nuevo precio (>0): ";
                if (!(cin >> nuevoPrecio) || nuevoPrecio <= 0) { cout << "Precio invalido.\n"; limpiarEntrada(); }
                else { productos[i].precio = nuevoPrecio; break; }
            } while (true);

            int nuevoStock;
            do {
                cout << "Nuevo stock (>=0): ";
                if (!(cin >> nuevoStock) || nuevoStock < 0) { cout << "Stock invalido.\n"; limpiarEntrada(); }
                else { productos[i].stock = nuevoStock; break; }
            } while (true);

            guardarEnArchivo();
            cout << "Producto actualizado correctamente.\n";
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}

void eliminarProducto() {
    if (cantidad == 0) { cout << "No hay productos registrados.\n"; return; }

    int cod;
    cout << "Ingrese el codigo del producto a eliminar: ";
    if (!(cin >> cod)) { limpiarEntrada(); cout << "Entrada invalida.\n"; return; }

    for (int i = 0; i < cantidad; i++) {
        if (productos[i].codigo == cod) {
            for (int j = i; j < cantidad - 1; j++)
                productos[j] = productos[j + 1];
            cantidad--;
            guardarEnArchivo();
            cout << "Producto eliminado correctamente.\n";
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}

void mayorStock() {
    if (cantidad == 0) return;
    int pos = 0;
    for (int i = 1; i < cantidad; i++)
        if (productos[i].stock > productos[pos].stock)
            pos = i;
    cout << "Producto con mayor stock: " << productos[pos].nombre << " (" << productos[pos].stock << ")\n";
}

void productoMasCaro() {
    if (cantidad == 0) return;
    int pos = 0;
    for (int i = 1; i < cantidad; i++)
        if (productos[i].precio > productos[pos].precio)
            pos = i;
    cout << "Producto mas caro: " << productos[pos].nombre << " (S/ " << productos[pos].precio << ")\n";
}

void valorTotalInventario() {
    float total = 0;
    for (int i = 0; i < cantidad; i++)
        total += productos[i].precio * productos[i].stock;
    cout << "Valor total del inventario: S/ " << total << "\n";
}

void ordenarPorPrecio() {
    if (cantidad < 2) { cout << "No hay suficientes productos para ordenar.\n"; return; }
    for (int i = 0; i < cantidad - 1; i++)
        for (int j = i + 1; j < cantidad; j++)
            if (productos[i].precio < productos[j].precio) swap(productos[i], productos[j]);
    cout << "Productos ordenados por precio (mayor a menor):\n";
    mostrarProductos();
}

void ordenarPorNombre() {
    if (cantidad < 2) { cout << "No hay suficientes productos para ordenar.\n"; return; }
    for (int i = 0; i < cantidad - 1; i++)
        for (int j = i + 1; j < cantidad; j++)
            if (productos[i].nombre > productos[j].nombre) swap(productos[i], productos[j]);
    cout << "Productos ordenados por nombre (A-Z):\n";
    mostrarProductos();
}

// ================= MAIN =================

int main() {
    cargarDesdeArchivo();
    int opcion;

    do {
        cout << "\nMENU\n";
        cout << "1. Registrar producto\n";
        cout << "2. Mostrar productos\n";
        cout << "3. Buscar por codigo\n";
        cout << "4. Buscar por nombre\n";
        cout << "5. Producto con mayor stock\n";
        cout << "6. Producto mas caro\n";
        cout << "7. Valor total del inventario\n";
        cout << "8. Salir\n";
        cout << "9. Ordenar productos por precio (mayor a menor)\n";
        cout << "10. Ordenar productos por nombre (A-Z)\n";
        cout << "11. Actualizar producto\n";
        cout << "12. Eliminar producto\n";

        opcion = leerOpcionMenu();

        switch (opcion) {
            case 1: registrarProducto(); break;
            case 2: mostrarProductos(); break;
            case 3: buscarPorCodigo(); break;
            case 4: buscarPorNombre(); break;
            case 5: mayorStock(); break;
            case 6: productoMasCaro(); break;
            case 7: valorTotalInventario(); break;
            case 8:
                guardarEnArchivo();
                cout << "Datos guardados. Saliendo...\n";
                break;
            case 9: ordenarPorPrecio(); break;
            case 10: ordenarPorNombre(); break;
            case 11: actualizarProducto(); break;
            case 12: eliminarProducto(); break;
            default:
                cout << "Opcion fuera de rango.\n";
        }

    } while (opcion != 8);

    return 0;
}
