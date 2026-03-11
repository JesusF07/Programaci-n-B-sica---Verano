#include <stdio.h>
#include <cmath>

int main() {
    float lado;
    printf("Ingrese el lado del cuadrado:\n");
    scanf("%f", &lado);
    printf("el area del cuadrado es: %.2f\n", lado*lado);
    printf("el perimetro del cuadrado es: %.2f\n", lado*4);
    printf("el diagonal del cuadrado es: %.4f\n", lado*sqrt(2));
    return 0;

}

