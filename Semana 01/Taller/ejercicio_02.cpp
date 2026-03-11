#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

int main() {
    float base, altura;
    printf("ingrese la base del rectangulo: \n");
    scanf("%f", &base);
    printf("ingrese la altura : \n");
    scanf("%f", &altura);
    printf("el area del rectangulo es: %.2f\n", base * altura);
    printf("el perimetro del rectangulo es: %.2f\n", 2*(base + altura));
    printf("la diagonaln del rectangulo es: %.4f\n", sqrt(pow(base,2) + pow(altura,2)));

    return 0;
}
