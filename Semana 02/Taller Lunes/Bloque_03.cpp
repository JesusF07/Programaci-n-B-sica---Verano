#include<stdio.h>

void notas(float n){
    if ((n >= 90) && (n<=100)){
        printf("excelente");
    } else if ((n>=70) && (n<90)){
        printf("aprobado");
    } else if ((n<70) && (n>=1)){
        printf("desaprobado");
    } else {
        printf("Debe ingresar un numero del 1 al 100");
    }
}

int main(){
    float n;
    int resultado;

    printf("escribe la nota: ");
    resultado=scanf("%f", &n);

    //invalida el ingreso de letras
    //no es para validar el ingreso de decimales
    if(resultado!=1){
        printf("Ingresa un numero valido");
    } else {
        notas(n);
    }

    return 0;
}