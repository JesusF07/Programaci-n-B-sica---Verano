#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

class login{
public:

    bool verificarlogin(string u, int c, string &tipoUsuario){

        ifstream archivo("usuarios.txt");

        string user,tipo;
        int pass;

        while(archivo >> user >> pass >> tipo){

            if(user == u && pass == c){
                tipoUsuario = tipo;
                return true;
            }

        }

        return false;
    }

    bool iniciarSesion(string &tipoUsuario){

        string u;
        int c;

        cout<<"+==============================+\n";
        cout<<"|            LOGIN             |\n";
        cout<<"+==============================+\n";

        cout<<"| Ingrese usuario: ";
        cin>>u;

        cout<<"| Ingrese contrasena: ";
        cin>>c;

        bool acceso = verificarlogin(u,c,tipoUsuario);

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

        cout<<"Ingresar codigo: ";
        cin>>codigo;
        cin.ignore();

        cout<<"Ingresar descripcion: ";
        getline(cin,descripcion);

        cout<<"Ingresar unidad: ";
        cin>>unidad;

        cout<<"Ingresar precio: ";
        cin>>precio;

        cout<<"Ingresar cantidad: ";
        cin>>cantidad;
    }

    float subtotal(){
        return precio*cantidad;
    }

    int getCantidad(){ return cantidad; }
    string getUnidad(){ return unidad; }
    int getCodigo(){ return codigo; }
    string getDescripcion(){ return descripcion; }
    float getPrecio(){ return precio; }

    void guardar(ofstream &archivo){

        archivo<<codigo<<endl;
        archivo<<descripcion<<endl;
        archivo<<unidad<<endl;
        archivo<<precio<<endl;
        archivo<<cantidad<<endl;
    }

    void leer(ifstream &archivo){

        archivo>>codigo;
        archivo.ignore();

        getline(archivo,descripcion);

        archivo>>unidad;
        archivo>>precio;
        archivo>>cantidad;
        archivo.ignore();
    }
};

class factura{

private:

    int numeroSerie;
    string fecha;
    string cliente;
    long long ruc;
    string direccion;

    void generarNumeroSerie(){

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1000,9999);

        numeroSerie = dist(gen);
    }

public:

    vector<producto> productos;

    factura(string f,string c,long long r,string d){
        fecha=f;
        cliente=c;
        ruc=r;
        direccion=d;
        generarNumeroSerie();
    }

    void ingresarFactura(){

        cout<<"Fecha (dd/mm/yyyy): ";
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

        cout<<"Cantidad de productos: ";
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

    long long getRUC(){
        return ruc;
    }

    void guardarEnArchivo(ofstream &archivo){

        archivo<<numeroSerie<<endl;
        archivo<<fecha<<endl;
        archivo<<cliente<<endl;
        archivo<<ruc<<endl;
        archivo<<direccion<<endl;

        archivo<<productos.size()<<endl;

        for(int i=0;i<productos.size();i++)
            productos[i].guardar(archivo);
    }

    void leerDeArchivo(ifstream &archivo){

        archivo>>numeroSerie;
        archivo.ignore();

        getline(archivo,fecha);
        getline(archivo,cliente);

        archivo>>ruc;
        archivo.ignore();

        getline(archivo,direccion);

        int n;

        archivo>>n;
        archivo.ignore();

        productos.clear();

        for(int i=0;i<n;i++){

            producto p;

            p.leer(archivo);

            productos.push_back(p);
        }
    }
};

class gestorFacturas{

private:

    vector<factura> listaFacturas;

    string archivoFacturas="facturas.txt";

public:

    gestorFacturas(){
        leerFacturasDesdeArchivo();
    }

    void registrarFactura(factura f){

        listaFacturas.push_back(f);

        guardarFacturasEnArchivo();
    }

    void buscarFacturasPorRUC(long long rucBuscado){

        bool encontrada=false;

        for(int i=0;i<listaFacturas.size();i++){

            if(listaFacturas[i].getRUC()==rucBuscado){

                listaFacturas[i].mostrarFactura();

                encontrada=true;
            }
        }

        if(!encontrada)

        cout<<"No se encontraron facturas"<<endl;
    }

    void guardarFacturasEnArchivo(){

        ofstream archivo(archivoFacturas);

        archivo<<listaFacturas.size()<<endl;

        for(int i=0;i<listaFacturas.size();i++)

        listaFacturas[i].guardarEnArchivo(archivo);
    }

    void leerFacturasDesdeArchivo(){

        ifstream archivo(archivoFacturas);

        if(!archivo) return;

        int n;

        archivo>>n;
        archivo.ignore();

        listaFacturas.clear();

        for(int i=0;i<n;i++){

            factura f("","",0,"");

            f.leerDeArchivo(archivo);

            listaFacturas.push_back(f);
        }
    }
};

class menu{

private:

    string tipoUsuario;

    gestorFacturas gestor;

public:

    menu(string tipo){
        tipoUsuario=tipo;
    }

    void mostrarMenu(){

        cout<<"+===========================+\n";
        cout<<"|           MENU            |\n";
        cout<<"+===========================+\n";

        cout<<"1. Buscar factura"<<endl;

        if(tipoUsuario=="admin")
        cout<<"2. Registrar factura"<<endl;

        cout<<"3. Salir"<<endl;
    }

    void registrarFactura(){

        factura f("","",0,"");

        f.ingresarFactura();

        gestor.registrarFactura(f);

        cout<<"Factura registrada"<<endl;
    }

    void buscarFactura(){

        long long ruc;

        cout<<"Ingrese RUC: ";
        cin>>ruc;

        gestor.buscarFacturasPorRUC(ruc);
    }

    void ejecutarMenu(){

        int opcion;

        do{

            mostrarMenu();

            cout<<"Opcion: ";
            cin>>opcion;

            switch(opcion){

                case 1:
                    buscarFactura();
                    break;

                case 2:

                    if(tipoUsuario=="admin")
                    registrarFactura();
                    else
                    cout<<"No tiene permisos"<<endl;

                    break;

                case 3:
                    cout<<"Saliendo..."<<endl;
                    break;

                default:
                    cout<<"Opcion invalida"<<endl;
            }

        }while(opcion!=3);
    }
};

int main(){

    login sistema;

    string tipoUsuario;

    if(sistema.iniciarSesion(tipoUsuario)){

        menu menuPrincipal(tipoUsuario);

        menuPrincipal.ejecutarMenu();
    }

}