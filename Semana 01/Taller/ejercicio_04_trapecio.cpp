#include <iostream>
#include <stdio.h>

int main () {
    float B, b, h;
    printf("ingrese la base mayor: ");
    scanf("%f", &B);
    printf("ingrese la base menor: ");
    scanf("%f", &b);
    printf("ingrese la altura: ");
    scanf("%f",&h);
    printf("el area del trapecio es: %.2f\n", ((B+b)*h)/2);

    return 0;
}