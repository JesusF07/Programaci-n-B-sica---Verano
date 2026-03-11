#include <iostream>
#include <string>
using namespace std;
//clase padre
class celular {
    protected:
        string marca;
        string modelo;
        int anio;
        string color;
        string operador1;
        string operador2;
    public:
    //constructor
        celular(string n, string x, int y, string z, string op1){
            marca=n;
            modelo=x;
            anio=y;
            color=z;
            operador1=op1;
            operador2="no tiene";
        }
    //constructor sobrecargado
        celular(string n, string x, int y, string z,string op1, string op2){
            marca=n;
            modelo=x;
            anio=y;
            color=z;
            operador1=op1;
            operador2=op2;
        }
     void estado(){
            cout<<"Esta encendiendo......"<<endl;
        }
    void mostrar_datos(){
        cout<<"Marca: "<<marca<<endl;
        cout<<"Modelo: "<<modelo<<endl;
        cout<<"Anio: "<<anio<<endl;
        cout<<"Color: "<<color<<endl;
        cout<<"Operador 1: "<<operador1<<endl;
        cout<<"Operador 2: "<<operador2<<endl;
    }
};
//clases hijas
class celular_android : public celular {
    public:
        celular_android(string n, string x, int y, string z,string op1) : celular(n,x,y,z,op1){}
        celular_android(string n, string x, int y, string z,string op1, string op2) : celular(n,x,y,z,op1,op2){}

        void mostrar_logo_android(){
            cout<<"muestra el logo de android"<<endl;
        }
};
class celular_ios : public celular {
    public:
        celular_ios(string n, string x, int y, string z, string op1) : celular(n,x,y,z,op1){}
        celular_ios(string n, string x, int y, string z, string op1, string op2) : celular(n,x,y,z,op1,op2){}

        void mostrar_logo_apple(){
            cout<<"muestra el logo de apple"<<endl;
        }
};

 int main(){
    celular_android cel_samsung("samsung", "galaxy a15", 2023, "negro","movistar");
    celular_android cel_samsung2("samsung", "galaxy s25 ultra", 2025, "azul marino", "movistar", "claro");
    celular_ios cel_apple("apple", "iphone 17 pro max", 2025, "blanco" ,"movistar");
    cel_samsung.mostrar_datos();
    cel_samsung.estado();
    cel_samsung.mostrar_logo_android();
    cout<<endl;
    cel_samsung2.mostrar_datos();
    cel_samsung2.estado();
    cel_samsung2.mostrar_logo_android();
    cout<<endl;
    cel_apple.mostrar_datos();
    cel_apple.estado();
    cel_apple.mostrar_logo_apple();
}