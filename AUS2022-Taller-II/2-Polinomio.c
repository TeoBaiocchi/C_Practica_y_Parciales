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

/* asigna el n_ésimo coeficiente del Polinomio */
void setCoef(int n, double c, Polinomio * P);

/* retorna el n_ésimo coeficiente del Polinomio */
double getCoef(int n, Polinomio * P);

/* libera la memoria asociada con el polinomio */
void destruyePolinomio( Polinomio *p );


int main(){

    Polinomio *pol = creaPolinomio(4);
    setCoef(0, 3, pol); // tiene que dar 1
    setCoef(1, 5, pol);
    setCoef(2, 6, pol);
    setCoef(3, 12.5, pol);
    setCoef(4, 0, pol); // tiene que dar 0
    return 0;
}


Polinomio * creaPolinomio(int orden){
    Polinomio *pol = (Polinomio*) malloc(sizeof(Polinomio));
    pol->n = orden;
    pol->coeficientes = (double*)malloc(sizeof(double)*(orden));
    return pol; 
}

void destruyePolinomio(Polinomio *p){
    free((p->coeficientes));
    free(p);
}


void setCoef(int n, double c, Polinomio * P){
    *((P->coeficientes) + n) = c;
}

double getCoef(int n, Polinomio *P){
    return *((P->coeficientes) + n);
}