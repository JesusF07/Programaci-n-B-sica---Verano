#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    vector<int> p;
    int n,nota;
    cout<<"Ingrese la cantidad de alumnos:"<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        cout<<"Nota del alumno #"<<i+1<<": "<<i<<endl;
        cin>>nota;
        p.push_back(nota);
    }
    for(int i=0;i<n;i++){
    cout<<"Alumno #"<<i+1<<": "<<p[i]<<endl;
    }
}