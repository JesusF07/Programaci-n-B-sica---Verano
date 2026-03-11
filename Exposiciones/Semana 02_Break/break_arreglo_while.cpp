#include <iostream>
using namespace std;

int main() {
    int edades[5] = {18, 25, 40, 65, 30};
    int i = 0;

    while (i < 5) {
        if (edades[i] > 60) {
            break;
        }
        cout << edades[i] << endl;
        i++;
    }

    return 0;
}
