#include <iostream>
using namespace std;

int main() {
    int x = 1;
    while (x <= 5) {
        cout << x << endl;
        if (x == 2) {
            break;
        }
        x++;
    }
    return 0;
}

