#include <stdio.h>

int main() {
    float a, b, c, R, p, area;

    printf("Ingrese lado a: ");
    scanf("%f", &a);
    printf("Ingrese lado b: ");
    scanf("%f", &b);
    printf("Ingrese lado c: ");
    scanf("%f", &c);
    printf("Ingrese el radio: ");
    scanf("%f", &R);

    p = (a + b + c) / 2;
    area = p * R;

    printf("Area: %.2f\n", area);

    return 0;
}
