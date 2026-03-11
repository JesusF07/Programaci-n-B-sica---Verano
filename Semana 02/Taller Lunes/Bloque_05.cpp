#include <iostream>
using namespace std;

void saludo(int h) {
    if (h>= 6 && h <= 11) {
        cout << "Buenos dias" << endl;
    }
    else if (h>= 12 && h <= 18) {
        cout << "Buenas tardes" << endl;
    }
    else if (h >= 19 && h <= 23) {
        cout << "Buenas noches" << endl;
    }
    else {
        cout << "Hora no valida" << endl;
    }
}

int main() {
    int h;

    cout << "Ingrese la hora (0-23): ";
    cin >> h;

    saludo(h);

    return 0;
}

