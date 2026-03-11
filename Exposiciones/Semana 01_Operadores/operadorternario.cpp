#include <iostream>
using namespace std;

int edad;
string estado;

int main(){
    cout << "Ingrese su edad: ";
    cin >> edad;
    estado=edad>=18?"es mayor de edad":"no es mayor de edad";
    cout<<estado;

    return 0;
}