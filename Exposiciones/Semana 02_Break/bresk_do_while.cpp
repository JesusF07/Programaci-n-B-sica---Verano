#include <iostream>
using namespace std;

int main() {
    int n = 1;
    do {
        cout << n << endl;
        if (n == 4) {
            break;
        }
        n++;
    } while (n <= 6);
    return 0;
}
