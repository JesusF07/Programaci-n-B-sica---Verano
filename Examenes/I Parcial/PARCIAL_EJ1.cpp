#include <iostream>
using namespace std;

int es_numero_primo(int numero) {
    int divisor;

    if (numero <= 1)
        return 0;

    for (divisor = 2; divisor <= numero / 2; divisor++) {
        if (numero % divisor == 0)
            return 0;
    }

    return 1;
}

int main() {
    int cantidadNumeros;
    int numeroActual;
    int contador;

    int maximo;
    int minimo;

    int cantidadPrimos = 0;

    int sumaParesPositivos = 0;
    int cantidadParesPositivos = 0;

    int mayorConMasDigitosImpares;
    int existeMayorConMasDigitosImpares = 0;

    int temporal;
    int digito;
    int cantidadDigitosPares;
    int cantidadDigitosImpares;

    cout << "Ingrese la cantidad de numeros (N >= 1): ";
    cin >> cantidadNumeros;

    if (cantidadNumeros < 1) {
        cout << "Cantidad invalida";
        return 0;
    }

    cout << "Ingrese el numero 1: ";
    cin >> numeroActual;

    maximo = numeroActual;
    minimo = numeroActual;

    if (es_numero_primo(numeroActual) == 1)
        cantidadPrimos++;

    if (numeroActual > 0 && numeroActual % 2 == 0) {
        sumaParesPositivos += numeroActual;
        cantidadParesPositivos++;
    }

    // --- Analisis SOLO si tiene 3 o mas digitos ---
    temporal = numeroActual;
    if (temporal < 0)
        temporal = -temporal;

    if (temporal >= 100) {
        cantidadDigitosPares = 0;
        cantidadDigitosImpares = 0;

        while (temporal > 0) {
            digito = temporal % 10;
            if (digito % 2 == 0)
                cantidadDigitosPares++;
            else
                cantidadDigitosImpares++;
            temporal = temporal / 10;
        }

        if (cantidadDigitosImpares > cantidadDigitosPares) {
            mayorConMasDigitosImpares = numeroActual;
            existeMayorConMasDigitosImpares = 1;
        }
    }

    for (contador = 2; contador <= cantidadNumeros; contador++) {
        cout << "Ingrese el numero " << contador << ": ";
        cin >> numeroActual;

        if (numeroActual > maximo)
            maximo = numeroActual;

        if (numeroActual < minimo)
            minimo = numeroActual;

        if (es_numero_primo(numeroActual) == 1)
            cantidadPrimos++;

        if (numeroActual > 0 && numeroActual % 2 == 0) {
            sumaParesPositivos += numeroActual;
            cantidadParesPositivos++;
        }

        temporal = numeroActual;
        if (temporal < 0)
            temporal = -temporal;

        if (temporal >= 100) {
            cantidadDigitosPares = 0;
            cantidadDigitosImpares = 0;

            while (temporal > 0) {
                digito = temporal % 10;
                if (digito % 2 == 0)
                    cantidadDigitosPares++;
                else
                    cantidadDigitosImpares++;
                temporal = temporal / 10;
            }

            if (cantidadDigitosImpares > cantidadDigitosPares) {
                if (existeMayorConMasDigitosImpares == 0 ||
                    numeroActual > mayorConMasDigitosImpares) {
                    mayorConMasDigitosImpares = numeroActual;
                    existeMayorConMasDigitosImpares = 1;
                }
            }
        }
    }

    cout << "\nMaximo: " << maximo;
    cout << "\nMinimo: " << minimo;

    if (cantidadPrimos > 0)
        cout << "\nCantidad de numeros primos: " << cantidadPrimos;
    else
        cout << "\nCantidad de numeros primos: NO EXISTE";

    if (cantidadParesPositivos > 0)
        cout << "\nPromedio de pares positivos: "
             << (float)sumaParesPositivos / cantidadParesPositivos;
    else
        cout << "\nPromedio de pares positivos: NO EXISTE";

    if (existeMayorConMasDigitosImpares == 1)
        cout << "\nMayor numero con mas digitos impares que pares (>=3 digitos): "
             << mayorConMasDigitosImpares;
    else
        cout << "\nMayor numero con mas digitos impares que pares: NO EXISTE";

    return 0;
}
