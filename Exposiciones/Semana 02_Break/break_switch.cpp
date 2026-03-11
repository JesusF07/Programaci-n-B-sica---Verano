#include <iostream>
using namespace std;

int main() {
    int opcion ;
    cout << "ingrese una opcion: ";
    cin >> opcion;
    switch (opcion) {
        case 1:
            cout << "Opcion 1" << endl;
            break;
        case 2:
            cout << "Opcion 2" << endl;
            break;
        default:
            cout << "Otra opcion" << endl;
    }
    return 0;
}
