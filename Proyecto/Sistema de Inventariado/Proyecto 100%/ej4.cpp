#include<iostream>
#include<fstream>
using namespace std;

class archivo{
private:
    string nombreArchivo;
public:
    archivo(const string& nombre) : nombreArchivo(nombre){}
    void escribirArchivo(){
        ofstream archivo(nombreArchivo);
        if(!archivo){
            cout<<"No se pudo abrir el archivo"<<endl;
            return;
        }
        archivo<<"Hola Mundo"<<endl;
        archivo.close();
        cout<<"Archivo guardado correctamente"<<endl;
        }

    void leerArchivo(){
        ifstream archivo(nombreArchivo);
        if(!archivo){
            cout<<"No se pudo abrir el archivo"<<endl;
            return;
        }
        string linea;
        cout<<"Contenido del archivo"<<endl;
        while(getline(archivo,linea)){
            cout<<linea<<endl;
        }
        archivo.close();
    }
};


int main(){
    archivo miArchivo("datos.txt");
    miArchivo.escribirArchivo();
    miArchivo.leerArchivo();
    return 0;
}