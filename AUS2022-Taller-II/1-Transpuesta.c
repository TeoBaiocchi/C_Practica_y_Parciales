#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){


    int filas = 3, columnas = 5;
    printf("Ingrese la cantidad de filas: \n");
    printf("Ingrese la cantidad de columnas: \n");
    //No hago el scanf por motivos de practicidad
    
    int **matriz, **transpuesta;  //La matriz es bidimensional, entonces la pensamos como
    // una lista de punteros, que apuntan a listas de punteros que apuntan a un entero
    
    matriz = (int**) malloc(sizeof(int*) * filas);  //Reservas la primera dimension (son punteros)
    transpuesta = (int**) malloc(sizeof(int*) * columnas);
    printf("\n---Original---\n");
    for(int i = 0; i < filas; i++){ 
         //Ahora tenes que iterar sobre tu primera dimension Para reservar el espacio para los enteros a los que van a apuntar
        *(matriz + i) = (int*) malloc(sizeof(int)*columnas);

        for(int j=0; j<columnas; j++){
            *(*(matriz + i) + j) = (i+j); //lleno con valor arbitrario
            printf(" %i ", *(*(matriz + i) + j));
        }
        printf("\n");
    }
    printf("\n---Transpuesta---\n");
    for(int i = 0; i < columnas; i++){ 
        *(transpuesta + i) = (int*) malloc(sizeof(int)*filas);
        for(int j = 0; j < filas; j++){
            *(*(transpuesta+i)+j) = *(*(matriz + j)+i);
            printf(" %i ", *(*(transpuesta + i) + j));
        }
        printf("\n");
    }

    
    return 0;
}