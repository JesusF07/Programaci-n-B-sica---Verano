#include <iostream>
using namespace std;

int main() {
    int numeros[5] = {4, 6, 8, 0, 9};
    int i = 0;

    do {
        if (numeros[i] == 0) {
            break;
        }
        cout << numeros[i] << endl;
        i++;
    } while (i < 5);

    return 0;
}
