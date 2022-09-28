//INCOMPLETO

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define X 5

typedef struct{
    int n;
    double *coeficientes;
} Polinomio;


Polinomio * creaPolinomio(int orden);
//Crea un polinomio, y devuelve el puntero a el


int main(){

    Polinomio *pol = creaPolinomio(10);

    return 0;
}

Polinomio * creaPolinomio(int orden){
    Polinomio *pol = (Polinomio*) malloc(sizeof(Polinomio));
    pol->n = orden;
    pol->coeficientes = (double*)malloc(sizeof(double)*(orden));
    *(pol->coeficientes);
    return pol; 
}

