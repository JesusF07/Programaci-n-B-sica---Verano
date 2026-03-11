#include <stdio.h>
#include <math.h>

int main() {
    float a, b, c, p, area;

    printf("Ingrese lado a: ");
    scanf("%f", &a);
    printf("Ingrese lado b: ");
    scanf("%f", &b);
    printf("Ingrese lado c: ");
    scanf("%f", &c);

    p = (a + b + c) / 2;
    area = sqrt(p * (p - a) * (p - b) * (p - c));

    printf("Semiperimetro: %.2f\n", p);
    printf("Area: %.2f\n", area);

    return 0;
}
