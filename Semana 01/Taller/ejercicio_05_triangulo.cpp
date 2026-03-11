#include <stdio.h>

int main() {
    float a, b, c, h, area, perimetro;

    printf("Ingrese lado 1: ");
    scanf("%f", &a);
    printf("Ingrese lado 2: ");
    scanf("%f", &c);
    printf("Ingrese la base: ");
    scanf("%f", &b);
    printf("Ingrese la altura: ");
    scanf("%f", &h);

    area = (b * h) / 2;
    perimetro = a + b + c;

    printf("Area: %.2f\n", area);
    printf("Perimetro: %.2f\n", perimetro);

    return 0;
}






