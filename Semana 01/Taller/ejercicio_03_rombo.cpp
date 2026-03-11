#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

int main() {
    float D, d, lado;
    printf("ingrese el diagonal mayor lado del rombo: \n");
    scanf("%f", &D);
    printf("ingresa el diagonal menor del rombo: \n");
    scanf("%f", &d);
    printf("el area del rombo es:  %.2f\n", (D*d)/2);
    lado = sqrt(pow(D/2,2) + pow(d/2,2));
    printf("el lado del rombo es: %.2f\n", lado);
    printf("el perimetro del rombo es: %.2f\n", 4*lado);
    return 0;
}