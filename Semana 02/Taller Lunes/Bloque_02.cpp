#include <stdio.h>

void acceso(int edad){
    if (edad >= 18) {
        printf("Acceso permitido");
    } else {
        printf("Acceso denegado");
    }
}

int main(){
   
    int edad;
    int resultado;

    printf("Ingrese su edad: ");
    resultado=scanf("%d", &edad);

    //invalida el ingreso de letras
    //no es para validar el ingreso de decimales
    if(resultado!=1){
        printf("ingrese un numero valido");
    } else{
        acceso(edad);
    }
    
return 0;
}

