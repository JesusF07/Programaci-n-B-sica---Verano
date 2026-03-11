/*
==================== BITÁCORA IA ====================
Herramienta IA usada: ChatGPT
Objetivo del uso: Comprender estructuras, punteros, referencias, memoria dinámica y agregar persistencia en archivos.

Preguntas que hice a la IA (resumen):
1) Cómo guardar y cargar un arreglo dinámico de structs en archivos de texto.
2) Cómo mantener consistencia de IDs y disponibilidad al guardar/cargar.
3) Cómo integrar persistencia sin romper las funciones existentes.
4) Cómo manejar errores de archivo y creación automática si no existe.

Qué sugerencias acepté y por qué:
- Guardar libros y usuarios en archivos separados (.txt): acepté para cumplir con la opción extra de la rúbrica.
- Leer datos al inicio y guardar al agregar: acepté porque asegura que los cambios no se pierdan.

Qué sugerencias rechacé y por qué:
- Guardar préstamos en archivo: rechacé porque no era obligatorio y complicaría el código innecesariamente.

Test manual diseñado por mí:
Entrada (pasos/comandos):
- Cerrar y abrir el programa varias veces.
- Agregar libros y usuarios, listar para verificar persistencia.
- Prestar y devolver libros, luego reiniciar y verificar disponibilidad.
Salida esperada:
- Los libros y usuarios agregados persisten entre ejecuciones.
- Los libros devueltos aparecen como disponibles.
====================================================
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>
#include <fstream>

using namespace std;

// ---------------------- Structs ----------------------
struct Libro {
    int id;
    string titulo;
    string autor;
    int anio;
    bool disponible;
};

struct Usuario {
    int id;
    string nombre;
    string carrera;
};

struct Prestamo {
    int idUsuario;
    int idLibro;
};

// ------------------- Funciones Prototipo -------------------
void agregarLibro(Libro *&libros, int &cantidadLibros, int &capacidadLibros);
void listarLibros(Libro *libros, int cantidadLibros);
void agregarUsuario(Usuario *&usuarios, int &cantidadUsuarios, int &capacidadUsuarios);
void listarUsuarios(Usuario *usuarios, int cantidadUsuarios);
Libro* buscarLibroPorId(Libro *libros, int cantidadLibros, int idLibro);
Usuario* buscarUsuarioPorId(Usuario *usuarios, int cantidadUsuarios, int idUsuario);
void prestarLibro(Libro *libros, int cantidadLibros, Usuario *usuarios, int cantidadUsuarios, Prestamo *&prestamos, int &cantidadPrestamos, int &capacidadPrestamos);
void devolverLibro(Libro *libros, int cantidadLibros, Prestamo *&prestamos, int &cantidadPrestamos);
void buscarLibros(Libro *libros, int cantidadLibros, const string &texto);
string minusculas(const string &texto);
void expandirLibros(Libro *&libros, int &capacidadLibros);
void expandirUsuarios(Usuario *&usuarios, int &capacidadUsuarios);
void expandirPrestamos(Prestamo *&prestamos, int &capacidadPrestamos);
void guardarLibrosEnArchivo(Libro *libros, int cantidadLibros, const string &nombreArchivo);
void cargarLibrosDesdeArchivo(Libro *&libros, int &cantidadLibros, int &capacidadLibros, const string &nombreArchivo);
void guardarUsuariosEnArchivo(Usuario *usuarios, int cantidadUsuarios, const string &nombreArchivo);
void cargarUsuariosDesdeArchivo(Usuario *&usuarios, int &cantidadUsuarios, int &capacidadUsuarios, const string &nombreArchivo);

// ------------------- Función Principal -------------------
int main() {
    int capacidadLibros = 5, cantidadLibros = 0;
    int capacidadUsuarios = 3, cantidadUsuarios = 0;
    int capacidadPrestamos = 5, cantidadPrestamos = 0;

    Libro *libros = new Libro[capacidadLibros];
    Usuario *usuarios = new Usuario[capacidadUsuarios];
    Prestamo *prestamos = new Prestamo[capacidadPrestamos];

    // Cargar datos desde archivos
    cargarLibrosDesdeArchivo(libros, cantidadLibros, capacidadLibros, "libros.txt");
    cargarUsuariosDesdeArchivo(usuarios, cantidadUsuarios, capacidadUsuarios, "usuarios.txt");

    int opcion = 0;
    do {
        cout << "\n=== MENU BIBLIOTECA ===\n";
        cout << "1. Agregar libro\n";
        cout << "2. Listar libros\n";
        cout << "3. Agregar usuario\n";
        cout << "4. Listar usuarios\n";
        cout << "5. Prestar libro\n";
        cout << "6. Devolver libro\n";
        cout << "7. Buscar libro\n";
        cout << "0. Salir\n";
        cout << "Ingrese opcion: ";
        cin >> opcion;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = -1;
        }

        switch(opcion) {
            case 1: 
                agregarLibro(libros, cantidadLibros, capacidadLibros); 
                guardarLibrosEnArchivo(libros, cantidadLibros, "libros.txt"); 
                break;
            case 2: listarLibros(libros, cantidadLibros); break;
            case 3: 
                agregarUsuario(usuarios, cantidadUsuarios, capacidadUsuarios); 
                guardarUsuariosEnArchivo(usuarios, cantidadUsuarios, "usuarios.txt"); 
                break;
            case 4: listarUsuarios(usuarios, cantidadUsuarios); break;
            case 5: prestarLibro(libros, cantidadLibros, usuarios, cantidadUsuarios, prestamos, cantidadPrestamos, capacidadPrestamos); break;
            case 6: devolverLibro(libros, cantidadLibros, prestamos, cantidadPrestamos); break;
            case 7: {
                cin.ignore();
                string texto;
                cout << "Ingrese texto para buscar: ";
                getline(cin, texto);
                buscarLibros(libros, cantidadLibros, texto);
                break;
            }
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida, intente nuevamente.\n";
        }
    } while(opcion != 0);

    // Guardar datos antes de salir
    guardarLibrosEnArchivo(libros, cantidadLibros, "libros.txt");
    guardarUsuariosEnArchivo(usuarios, cantidadUsuarios, "usuarios.txt");

    delete[] libros;
    delete[] usuarios;
    delete[] prestamos;

    return 0;
}

// ------------------- Funciones -------------------

void expandirLibros(Libro *&libros, int &capacidadLibros) {
    int nuevaCapacidad = capacidadLibros * 2;
    Libro *nuevoArreglo = new Libro[nuevaCapacidad];
    for(int i=0; i<capacidadLibros; i++)
        nuevoArreglo[i] = libros[i];
    delete[] libros;
    libros = nuevoArreglo;
    capacidadLibros = nuevaCapacidad;
}

void expandirUsuarios(Usuario *&usuarios, int &capacidadUsuarios) {
    int nuevaCapacidad = capacidadUsuarios * 2;
    Usuario *nuevoArreglo = new Usuario[nuevaCapacidad];
    for(int i=0; i<capacidadUsuarios; i++)
        nuevoArreglo[i] = usuarios[i];
    delete[] usuarios;
    usuarios = nuevoArreglo;
    capacidadUsuarios = nuevaCapacidad;
}

void expandirPrestamos(Prestamo *&prestamos, int &capacidadPrestamos) {
    int nuevaCapacidad = capacidadPrestamos * 2;
    Prestamo *nuevoArreglo = new Prestamo[nuevaCapacidad];
    for(int i=0; i<capacidadPrestamos; i++)
        nuevoArreglo[i] = prestamos[i];
    delete[] prestamos;
    prestamos = nuevoArreglo;
    capacidadPrestamos = nuevaCapacidad;
}

void agregarLibro(Libro *&libros, int &cantidadLibros, int &capacidadLibros) {
    if(cantidadLibros >= capacidadLibros) expandirLibros(libros, capacidadLibros);
    Libro nuevoLibro;
    cout << "ID libro: "; cin >> nuevoLibro.id;
    for(int i=0;i<cantidadLibros;i++){
        if(libros[i].id==nuevoLibro.id){
            cout<<"ID ya existe. Libro no agregado.\n"; return;
        }
    }
    cin.ignore();
    cout << "Titulo: "; getline(cin, nuevoLibro.titulo);
    cout << "Autor: "; getline(cin, nuevoLibro.autor);
    cout << "Anio: "; cin >> nuevoLibro.anio;
    nuevoLibro.disponible = true;
    libros[cantidadLibros++] = nuevoLibro;
    cout << "Libro agregado exitosamente.\n";
}

void listarLibros(Libro *libros, int cantidadLibros) {
    cout << "\n--- LISTA DE LIBROS ---\n";
    for(int i=0;i<cantidadLibros;i++){
        cout << "ID: " << libros[i].id
             << ", Titulo: " << libros[i].titulo
             << ", Autor: " << libros[i].autor
             << ", Anio" << libros[i].anio
             << ", Disponible: " << (libros[i].disponible ? "Si":"No") << "\n";
    }
}

void agregarUsuario(Usuario *&usuarios, int &cantidadUsuarios, int &capacidadUsuarios) {
    if(cantidadUsuarios >= capacidadUsuarios) expandirUsuarios(usuarios, capacidadUsuarios);
    Usuario nuevoUsuario;
    cout << "ID usuario: "; cin >> nuevoUsuario.id;
    for(int i=0;i<cantidadUsuarios;i++){
        if(usuarios[i].id==nuevoUsuario.id){
            cout<<"ID ya existe. Usuario no agregado.\n"; return;
        }
    }
    cin.ignore();
    cout << "Nombre: "; getline(cin, nuevoUsuario.nombre);
    cout << "Carrera: "; getline(cin, nuevoUsuario.carrera);
    usuarios[cantidadUsuarios++] = nuevoUsuario;
    cout << "Usuario agregado exitosamente.\n";
}

void listarUsuarios(Usuario *usuarios, int cantidadUsuarios) {
    cout << "\n--- LISTA DE USUARIOS ---\n";
    for(int i=0;i<cantidadUsuarios;i++){
        cout << "ID: " << usuarios[i].id
             << ", Nombre: " << usuarios[i].nombre
             << ", Carrera: " << usuarios[i].carrera << "\n";
    }
}

Libro* buscarLibroPorId(Libro *libros, int cantidadLibros, int idLibro) {
    for(int i=0;i<cantidadLibros;i++){
        if(libros[i].id==idLibro) return &libros[i];
    }
    return nullptr;
}

Usuario* buscarUsuarioPorId(Usuario *usuarios, int cantidadUsuarios, int idUsuario) {
    for(int i=0;i<cantidadUsuarios;i++){
        if(usuarios[i].id==idUsuario) return &usuarios[i];
    }
    return nullptr;
}

void prestarLibro(Libro *libros, int cantidadLibros, Usuario *usuarios, int cantidadUsuarios, Prestamo *&prestamos, int &cantidadPrestamos, int &capacidadPrestamos) {
    int idUsuario, idLibro;
    cout << "ID Usuario: "; cin >> idUsuario;
    Usuario *usuario = buscarUsuarioPorId(usuarios, cantidadUsuarios, idUsuario);
    if(!usuario){ cout << "Usuario no existe.\n"; return; }

    cout << "ID Libro: "; cin >> idLibro;
    Libro *libro = buscarLibroPorId(libros, cantidadLibros, idLibro);
    if(!libro){ cout << "Libro no existe.\n"; return; }
    if(!libro->disponible){ cout << "Libro no disponible.\n"; return; }

    if(cantidadPrestamos >= capacidadPrestamos) expandirPrestamos(prestamos, capacidadPrestamos);
    Prestamo nuevoPrestamo { idUsuario, idLibro };
    prestamos[cantidadPrestamos++] = nuevoPrestamo;
    libro->disponible = false;
    cout << "Prestamo registrado correctamente.\n";
}

void devolverLibro(Libro *libros, int cantidadLibros, Prestamo *&prestamos, int &cantidadPrestamos) {
    int idLibro;
    cout << "ID Libro a devolver: "; cin >> idLibro;
    int indicePrestamo = -1;
    for(int i=0;i<cantidadPrestamos;i++){
        if(prestamos[i].idLibro==idLibro){
            indicePrestamo = i;
            break;
        }
    }
    if(indicePrestamo==-1){ cout << "No existe prestamo activo para este libro.\n"; return; }

    Libro *libro = buscarLibroPorId(libros, cantidadLibros, idLibro);
    if(libro) libro->disponible = true;

    for(int i=indicePrestamo;i<cantidadPrestamos-1;i++)
        prestamos[i] = prestamos[i+1];
    cantidadPrestamos--;
    cout << "Libro devuelto correctamente.\n";
}

string minusculas(const string &texto) {
    string resultado = texto;
    transform(resultado.begin(), resultado.end(), resultado.begin(), [](unsigned char c){ return tolower(c); });
    return resultado;
}

void buscarLibros(Libro *libros, int cantidadLibros, const string &texto) {
    string textoMinus = minusculas(texto);
    cout << "\n--- RESULTADOS DE BUSQUEDA ---\n";
    bool encontrado = false;
    for(int i=0;i<cantidadLibros;i++){
        if(minusculas(libros[i].titulo).find(textoMinus)!=string::npos || minusculas(libros[i].autor).find(textoMinus)!=string::npos){
            cout << "ID: " << libros[i].id
                 << ", Titulo: " << libros[i].titulo
                 << ", Autor: " << libros[i].autor
                 << ", Año: " << libros[i].anio
                 << ", Disponible: " << (libros[i].disponible ? "Si":"No") << "\n";
            encontrado = true;
        }
    }
    if(!encontrado) cout << "No se encontraron libros.\n";
}

// ------------------- Persistencia -------------------

void guardarLibrosEnArchivo(Libro *libros, int cantidadLibros, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if(!archivo){ cout << "Error al abrir archivo para guardar libros.\n"; return; }
    for(int i=0;i<cantidadLibros;i++){
        archivo << libros[i].id << "," << libros[i].titulo << "," << libros[i].autor << "," 
                << libros[i].anio << "," << libros[i].disponible << "\n";
    }
}

void cargarLibrosDesdeArchivo(Libro *&libros, int &cantidadLibros, int &capacidadLibros, const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if(!archivo) return; // no existe archivo
    string linea;
    while(getline(archivo,linea)){
        if(cantidadLibros >= capacidadLibros) expandirLibros(libros, capacidadLibros);
        Libro libro;
        size_t pos = 0, inicio = 0;
        int campo = 0;
        while((pos = linea.find(',', inicio)) != string::npos){
            string token = linea.substr(inicio, pos - inicio);
            switch(campo){
                case 0: libro.id = stoi(token); break;
                case 1: libro.titulo = token; break;
                case 2: libro.autor = token; break;
                case 3: libro.anio = stoi(token); break;
            }
            inicio = pos + 1;
            campo++;
        }
        libro.disponible = stoi(linea.substr(inicio));
        libros[cantidadLibros++] = libro;
    }
}

void guardarUsuariosEnArchivo(Usuario *usuarios, int cantidadUsuarios, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if(!archivo){ cout << "Error al abrir archivo para guardar usuarios.\n"; return; }
    for(int i=0;i<cantidadUsuarios;i++){
        archivo << usuarios[i].id << "," << usuarios[i].nombre << "," << usuarios[i].carrera << "\n";
    }
}

void cargarUsuariosDesdeArchivo(Usuario *&usuarios, int &cantidadUsuarios, int &capacidadUsuarios, const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if(!archivo) return;
    string linea;
    while(getline(archivo,linea)){
        if(cantidadUsuarios >= capacidadUsuarios) expandirUsuarios(usuarios, capacidadUsuarios);
        Usuario usuario;
        size_t pos = 0, inicio = 0;
        int campo = 0;
        while((pos = linea.find(',', inicio)) != string::npos){
            string token = linea.substr(inicio, pos - inicio);
            switch(campo){
                case 0: usuario.id = stoi(token); break;
                case 1: usuario.nombre = token; break;
            }
            inicio = pos + 1;
            campo++;
        }
        usuario.carrera = linea.substr(inicio);
        usuarios[cantidadUsuarios++] = usuario;
    }
}
