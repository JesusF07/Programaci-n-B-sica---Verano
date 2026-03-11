#include <stdio.h>

int main() {
    float a, b, c, r, p, area;

    printf("Ingrese lado a: ");
    scanf("%f", &a);
    printf("Ingrese lado b: ");
    scanf("%f", &b);
    printf("Ingrese lado c: ");
    scanf("%f", &c);
    printf("Ingrese el radio: ");
    scanf("%f", &r);

    p = (a + b + c) / 2;
    area = p * r;

    printf("Semiperimetro: %.2f\n", p);
    printf("Area: %.2f\n", area);

    return 0;
}
