#include <stdlib.h>
#include <stdio.h>
#define BUFFER 101

typedef struct char_string {

    char c;
    char * cadena;

} Char_string;

int cantidad(Char_string *);
int * ocurrencias(Char_string *, int);
int contar_longitud(char*);
void imprimir(int *);


int main(){

    Char_string * ejercicio = (Char_string *) malloc(sizeof(Char_string));
    if(ejercicio != NULL){
    
    ejercicio->cadena = (char *) malloc(sizeof(char)* BUFFER);

    if(ejercicio->cadena != NULL){

    printf("Ingrese una frase:");
    scanf("%[^\n]", ejercicio->cadena);
    int longitud = contar_longitud(ejercicio->cadena);
    ejercicio->cadena = realloc(ejercicio->cadena, (sizeof(char)*longitud));
    getchar();
    
    printf("Ingrese un caracter a buscar:");
    scanf("%c", &(ejercicio->c));
    
    int apariciones = cantidad(ejercicio); // por facilidad a la hora de mostrar las cosas el último valor del arreglo es -1
    int * ocur = ocurrencias(ejercicio, apariciones);
    if(ocur != NULL){
    printf("La cantidad de veces que aparece la letra %c es %i.\n", ejercicio->c, apariciones);
    printf("Las posiciones en las que aparece el caracter %c son: \n", ejercicio->c);
    imprimir(ocur);
    }
    free(ocur);
    free(ejercicio->cadena);
    free(ejercicio);
    }else{
        free(ejercicio);
        printf("FALLO!");
    }
    }else{

        printf("FALLO!");
    }

    return 0;
}

int contar_longitud(char * frase){

    int i;
    for(i = 0; *(frase+i)!= '\0'; i++){}
    
    return i+1;

}

int cantidad(Char_string * ejercicio){
    
    int contador = 0;
    for(int i = 0; *(ejercicio->cadena + i) != '\0'; i++){
        if(*(ejercicio->cadena + i) == ejercicio->c){
            contador++;
        }
    }
    return contador;
}

int * ocurrencias(Char_string * ejercicio, int apariciones){

    int * ocur = malloc(sizeof(int) * (apariciones + 1));
    if(ocur == NULL){
        printf("Cagamos!!!\n");
        return NULL;
    }
    int i, j = 0;
    for(i = 0; j<apariciones; i++){
        if(*(ejercicio->cadena + i) == ejercicio->c){
            *(ocur + j) = i;
            j++;
        }
    }
    *(ocur + j) = -1;
    return ocur;
}

void imprimir(int * ocur){
    int i = 0;
    while(*(ocur + i) != -1){
        printf("->%d\n", *(ocur + i));
        i++;
    }
}