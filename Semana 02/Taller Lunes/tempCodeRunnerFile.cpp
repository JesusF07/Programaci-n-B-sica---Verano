#include <iostream>
using namespace std;

void menu(){
    cout<<"-------MENU-----------"<<endl;
    cout<<"1. SUMA"<<endl;
    cout<<"2. RESTA"<<endl;
    cout<<"3. MULTIPLICACION"<<endl;
    cout<<"4. DIVISION"<<endl;
    cout<<"5. SALIR"<<endl;
}

void numeros(float &a, float &b){
    cout<<"Ingrese el primer numero: ";
    cin>>a;
    cout<<"Ingrese el segundo numero: ";
    cin>>b;
}

void suma(float a, float b){
    cout<<"La suma de "<<a<<" + "<<b<<" es: "<<a+b<<endl;
}

void resta(float a, float b){
    cout<<"La resta de "<<a<<" - "<<b<<" es: "<<a-b<<endl;
}

void multiplicacion(float a, float b){
    cout<<"La multiplicacion de "<<a<<" * "<<b<<" es: "<<a*b<<endl;
}

void division(float a, float b){
    if(b == 0 ){
        cout<<"ERROR: No se puede dividir entre 0"<<endl;
    } else {
        cout<<"La division de "<<a<<" / "<<b<<" es: "<<a/b<<endl;
    }
}

void operar(int opcion, float a, float b){
    switch(opcion){
        case 1 : suma(a,b);break;
        case 2 : resta(a,b);break;
        case 3 : multiplicacion(a,b);break;
        case 4 : division(a,b);break;
        case 5 : cout<<"SALIR";break;
        default: cout<<"Opcion invalida";
    }
}

int main() {
    int opcion;
    float a, b;

    do{
        menu();
        cout<<"Elige una opcion: ";
        cin>>opcion;

        if((opcion>=1) && (opcion<=4)){
            numeros(a, b);
            operar(opcion, a, b);
        } else if (opcion !=5){
             cout<<"Opcion invalida"<<endl;
        }

    } while (opcion != 5);

    return 0;
}