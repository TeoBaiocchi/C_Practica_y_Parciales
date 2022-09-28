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
    
    printf("Tamanio: %d\n", pol->n);
    printf("coeficientes: ");
    for(int i = 0; i <= pol->n; i++){
        printf(" %d (%i a la %i), ", *(pol->coeficientes), X, i);
    }
    return 0;
}

Polinomio * creaPolinomio(int orden){
    Polinomio *pol = (Polinomio*) malloc(sizeof(Polinomio));
    pol->n = orden;
    pol->coeficientes = (double*)malloc(sizeof(double)*(pol->n));
     *(pol->coeficientes) = 1; // x a la 0 = 1
    for(int i = 1; i <= orden; i++){
        double aux = 1;
        for(int j = 0; j<=i; j++){
            aux = aux * X;
        }
        *((pol->coeficientes)+i) = aux;
    }
    return pol; 
}