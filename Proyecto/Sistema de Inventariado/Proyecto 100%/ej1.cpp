#include <iostream>
#include <string>
using namespace std;
//clase base
class automovil{
private:
    string marca;
    string color;
    int ano;
public:
    //constructor con lista de inicializacion
    automovil(string m,string c, int a) : marca(m),color(c),ano(a){}
        
    string getmarca(){
        return marca;
    }
    string getcolor(){
        return color;
    }
    int getano(){
        return ano;
    }
    void setmarca(string m){
        marca=m;
    }
};

int main(){
    automovil a1("Honda","Gris",2030);
    cout<<"Marca: "<<a1.getmarca()<<endl;
    cout<<"Color: "<<a1.getcolor()<<endl;
    cout<<"Ano: "<<a1.getano()<<endl;
    a1.setmarca("Mercedes");
    cout<<"Marca: "<<a1.getmarca()<<endl;
}