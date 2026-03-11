#include <stdio.h>

void temperatura(int x) {
    if(x > 30) {
        printf("Encender el ventilador\n");
    } else if(x <= 30) {
        printf("Apagar el ventilador\n");
    }
}

int main() {
    int n;
    int resultado;
    
    printf("Ingrese la temperatura: ");
    resultado = scanf("%d", &n);

    //invalida el ingreso de letras
    //no es para validar el ingreso de decimales
    if(resultado != 1) {
        printf("Ingrese un numero valido\n");
    } else {
        temperatura(n);
    }

    return 0;
}
 

