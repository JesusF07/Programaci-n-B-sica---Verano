#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <iomanip>
using namespace std;

class login{
private:
    string usuario;
    int contrasena;
public:
    //constructur con lista inializada
    login(string u, int c) : usuario(u), contrasena(c){}
    //metodo que verifica el login
    bool verificarlogin(string u, int c){
        return (usuario==u && contrasena==c);
    }
    //metodo que verifica datos
    bool iniciarSesion(){
    string u;
    int c;
    cout<<"+==============================+\n";
    cout<<"|            LOGIN             |\n";
    cout<<"+==============================+\n";
    cout<<"| Ingrese usuario: ";
    cin>>u;
    cout<<"| Ingrese contrasena: ";
    cin>>c;
    bool acceso = verificarlogin(u,c);
    cout<<(acceso?"Acceso permitido":"Acceso denegado")<<endl;
    return acceso;
    }
};

class producto{
private:
    int codigo;
    string descripcion;
    string unidad;
    float precio;
    int cantidad;
public:
    void ingresarProducto(){
        cout<<"Ingresar codigo: "<<endl;
        cin>>codigo;
        cin.ignore();
        cout<<"Ingresar descripcion: "<<endl;
        getline(cin,descripcion);
        cout<<"Ingresar unidad: "<<endl;
        cin>>unidad;
        cout<<"Ingresar precio: "<<endl;
        cin>>precio;
        cout<<"Ingresar cantidad: "<<endl;
        cin>>cantidad;  
    }

    float subtotal(){
        return precio*cantidad;
    }

    void mostrarProducto(){
        cout<<"Codigo: "<<codigo<<endl;
        cout<<"Descripcion: "<<descripcion<<endl;
        cout<<"Unidad: "<<unidad<<endl;
        cout<<"Precio: "<<precio<<endl;
        cout<<"Cantidad: "<<cantidad<<endl; 
        cout<<"Subtotal: "<<subtotal()<<endl;
    }

    int getCantidad() { return cantidad; }
    string getUnidad() { return unidad; }
    int getCodigo() { return codigo; }
    string getDescripcion() { return descripcion; }
    float getPrecio() { return precio; }
    
    void guardar(ofstream &archivo) {
        archivo<<codigo<<endl
               <<descripcion<<endl
               <<unidad<<endl
               <<precio<<endl
               <<cantidad<<endl;
    }

    void leer(ifstream &archivo) {
        archivo>>codigo;archivo.ignore();
        getline(archivo, descripcion);
        archivo >> unidad; archivo.ignore();
        archivo >> precio;
        archivo >> cantidad; archivo.ignore();
    };
};

class factura{
private:
    int numeroSerie;
    string fecha;
    string cliente;
    int ruc;
    string direccion;

    void generarNumeroSerie() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1000, 9999);
        numeroSerie = dist(gen);
    }
public:
    factura(string f,string c,int r,string d) : fecha(f),cliente(c),ruc(r),direccion(d){
        generarNumeroSerie();
    }
    vector<producto>productos;

    void ingresarFactura(){
        cout<<"Fecha:(dd/mm/yyyy) ";
        cin>>fecha;
        cin.ignore();
        cout<<"Cliente: ";
        getline(cin,cliente);
        cout<<"RUC: ";
        cin>>ruc;
        cin.ignore();
        cout<<"Direccion: ";
        getline(cin,direccion);

        int n;
        cout<<"Ingresar cantidad de productos:"<<endl;
        cin>>n;
        for(int i=0;i<n;i++){
            producto p;
            p.ingresarProducto();
            productos.push_back(p);
        }
    }
    void mostrarFactura() {
    // --- ENCABEZADO ---
    cout << "+==================================================================================+\n";
    cout << "|                              FACTURA ELECTRONICA                                 |\n";
    cout << "+==================================================================================+\n";
    cout << "| Numero de serie: " << numeroSerie << endl;
    cout << "| Cliente       : " << cliente << endl;
    cout << "| Fecha         : " << fecha << endl;
    cout << "| RUC           : " << ruc << endl;
    cout << "| Direccion     : " << direccion << endl;
    cout << "+==================================================================================+\n";

    // --- TABLA DE PRODUCTOS ---
    cout << "+----------------------------------------------------------------------------------+\n";
    cout << "| Cant | Und | Codigo | Descripcion                 | P.Unit     | Subtotal         |\n";
    cout << "+----------------------------------------------------------------------------------+\n";
    for (int i = 0; i < productos.size(); i++) {
        cout << "| "
             << setw(4) << productos[i].getCantidad() << " "
             << "| " << setw(3) << productos[i].getUnidad() << " "
             << "| " << setw(6) << productos[i].getCodigo() << " "
             << "| " << left << setw(25) << productos[i].getDescripcion() << right
             << "| " << setw(10) << fixed << setprecision(2) << productos[i].getPrecio() << " "
             << "| " << setw(14) << fixed << setprecision(2) << productos[i].subtotal() << " |\n";
    }
    cout << "+----------------------------------------------------------------------------------+\n";

    // --- RESUMEN DE TOTALES ---
    float total = 0;
    for (int i = 0; i < productos.size(); i++)
        total += productos[i].subtotal();
    float igv = total * 0.18f;

    cout << "+----------------------------------------------------------------------------------+\n";
    cout << "| Op. Gravada : " << setw(63) << right << fixed << setprecision(2) << total << " |\n";
    cout << "| IGV (18%)   : " << setw(63) << right << fixed << setprecision(2) << igv << " |\n";
    cout << "| TOTAL       : " << setw(63) << right << fixed << setprecision(2) << total + igv << " |\n";
    cout << "+==================================================================================+\n";
}

    int getRUC() { return ruc; }

    void guardarEnArchivo(ofstream &archivo) {
        archivo << numeroSerie << endl
                << fecha << endl
                << cliente << endl
                << ruc << endl
                << direccion << endl
                << productos.size() << endl;
        for(int i = 0; i < productos.size(); i++)
            productos[i].guardar(archivo);
    }

    void leerDeArchivo(ifstream &archivo) {
        archivo >> numeroSerie; archivo.ignore();
        getline(archivo, fecha);
        getline(archivo, cliente);
        archivo >> ruc; archivo.ignore();
        getline(archivo, direccion);
        int n;
        archivo >> n; archivo.ignore();
        productos.clear();
        for(int i = 0; i < n; i++) {
            producto p;
            p.leer(archivo);
            productos.push_back(p);
        }
    }
}; 

class gestorFacturas {
private:
    vector<factura> listaFacturas;
    const string archivoFacturas = "facturas.txt";

public:
    gestorFacturas(){
    leerFacturasDesdeArchivo();
    }

    void registrarFactura(factura f) {
        listaFacturas.push_back(f);
        guardarFacturasEnArchivo();
    }

    void buscarFacturasPorRUC(int rucBuscado) {
        bool encontrada = false;
        for(int i = 0; i < listaFacturas.size(); i++) {
            if(listaFacturas[i].getRUC() == rucBuscado) {
                cout << "\nFactura encontrada:\n";
                listaFacturas[i].mostrarFactura();
                encontrada = true;
            }
        }
        if(!encontrada)
            cout << "No se encontraron facturas para el RUC " << rucBuscado << endl;
    }

    void guardarFacturasEnArchivo() {
        ofstream archivo(archivoFacturas);
        if(!archivo) { cout << "Error al guardar facturas\n"; return; }
        archivo << listaFacturas.size() << endl;
        for(int i = 0; i < listaFacturas.size(); i++)
            listaFacturas[i].guardarEnArchivo(archivo);
        archivo.close();
    }

    void leerFacturasDesdeArchivo() {
        ifstream archivo(archivoFacturas);
        if(!archivo) return;
        int n;
        archivo >> n; archivo.ignore();
        listaFacturas.clear();
        for(int i = 0; i < n; i++) {
            factura f("","",0,""); // constructor dummy
            f.leerDeArchivo(archivo);
            listaFacturas.push_back(f);
        }
        archivo.close();
    }
};

class menu{
private:
    enum Opciones{BuscarFactura = 1,RegistrarFactura,Salir};
    gestorFacturas gestor;

    void mostrarMenu(){
        cout<<"+===========================+\n";
        cout<<"|           MENU            |\n";
        cout<<"+===========================+\n";
        cout<<"| 1. Buscar Factura"<<endl;
        cout<<"| 2. Registrar Factura"<<endl;
        cout<<"| 3. Salir"<<endl;
        cout<<"+===========================+\n";

        }
    void registrarFactura() {
        factura f("","",0,""); // constructor dummy
        f.ingresarFactura();
        gestor.registrarFactura(f);
        cout << "Factura registrada con exito.\n";
    }

    void buscarFacturaPorRUC() {
        int ruc;
        cout << "Ingrese RUC: ";
        cin >> ruc;
        gestor.buscarFacturasPorRUC(ruc);
    }

    void procesarOpcion(int opcion) {
        switch(opcion){
            case BuscarFactura:
                buscarFacturaPorRUC();
                break;
            case RegistrarFactura:
                registrarFactura();
                break;
            case Salir:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
        }
    }
public:
    void ejecutarMenu(){
        int opcion;
        do{
            mostrarMenu();
            cout<<"Elige una opcion"<<endl;
            cin>>opcion;
            procesarOpcion(opcion);
        }while(opcion!= Salir);
    }
};

int main(){
    login sistema("administrador",123456789);
    if(sistema.iniciarSesion()){
    menu menuPrincipal;
    menuPrincipal.ejecutarMenu();
    }
}