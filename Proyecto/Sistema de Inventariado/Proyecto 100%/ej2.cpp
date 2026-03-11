#include <iostream>
using namespace std;

enum class DiasSemana{
    LUNES = 1,
    MARTES,
    MIERCOLES,
    JUEVES,
    VIERNES,
    SABADO,
    DOMINGO
};

class Calendario{
public:

    void mostrarDia(int dia){

        switch(dia){

            case (int)DiasSemana::LUNES:
                cout<<"Hoy es Lunes"<<endl;
                break;

            case (int)DiasSemana::MARTES:
                cout<<"Hoy es Martes"<<endl;
                break;

            case (int)DiasSemana::MIERCOLES:
                cout<<"Hoy es Miercoles"<<endl;
                break;

            case (int)DiasSemana::JUEVES:
                cout<<"Hoy es Jueves"<<endl;
                break;

            case (int)DiasSemana::VIERNES:
                cout<<"Hoy es Viernes"<<endl;
                break;

            case (int)DiasSemana::SABADO:
                cout<<"Hoy es Sabado"<<endl;
                break;

            case (int)DiasSemana::DOMINGO:
                cout<<"Hoy es Domingo"<<endl;
                break;

            default:
                cout<<"Dia invalido"<<endl;
        }
    }
};

int main(){

    Calendario cal;
    int opcion;

    cout<<"Ingrese un numero (1-7): ";
    cin>>opcion;

    cal.mostrarDia(opcion);

}