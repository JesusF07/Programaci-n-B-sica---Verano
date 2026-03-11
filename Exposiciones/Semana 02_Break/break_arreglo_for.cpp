#include <iostream>
using namespace std;

int main() {

    int numeros[5] = {3, 8, 2, -1, 6};
    int i = 0;

    while (i < 5) {
        if (numeros[i] < 0) {
            cout << "Se encontro un numero negativo." << endl;
            break;
        }
        i++;
    }

    return 0;
}
