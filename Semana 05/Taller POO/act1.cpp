#include <iostream>
#include <string>
using namespace std;
/*
Reflexión: ¿Qué significa decir que un objeto es una “instancia” de una clase?
Para mí, decir que un objeto es una instancia de una clase significa
que la clase es el molde o plantilla, y el objeto es algo real que se crea a partir de ese molde.
*/
class celular {
    protected:
        string marca;
        string modelo;
        int bateria;
        
        celular (string mar, string mod, int b){
            marca = mar;
            modelo = mod;
            bateria = b;
        }
};

class cel1: public celular {
    public:
        cel1(string mar, string mod, int b) : celular(mar,mod,b){};
        void mostrarinfo(){
            cout<<"Marca: "<<marca<<endl;
            cout<<"Modelo: "<<modelo<<endl;
            cout<<"Bateria: "<<bateria<<"%"<<endl;
        }
};

class cel2: public celular {
    public:
        cel2(string mar, string mod, int b) : celular(mar,mod,b){};
        void mostrarinfo(){
            cout<<"Marca: "<<marca<<endl;
            cout<<"Modelo: "<<modelo<<endl;
            cout<<"Bateria: "<<bateria<<"%"<<endl;
        }
};

int main(){
    cel1 android("Samsung","Galaxy s25 Ultra",100);
    cel2 apple("Apple","Iphone 17 Pro Max", 80);
    android.mostrarinfo();
    cout<<endl;
    apple.mostrarinfo();

    return 0;
}