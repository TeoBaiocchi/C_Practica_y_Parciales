#include<stdlib.h>
#include<stdio.h>

typedef struct char_string{
    char c;
    char *cadena;
} Char_string;
//Estructura que tiene un caracter, y una cadena (matriz de punteros a caracter)

int contarLargo(char * cadena);
int cantidad(Char_string *frase);
int *ocurrencias(Char_string *frase, int cantidad);

int main(){

    Char_string * estructura = (Char_string *) malloc(sizeof(Char_string));
    estructura -> cadena = (char*) malloc(sizeof(char)*255);
    printf("Ingrese una frase: ");
    scanf("%[^\n]", estructura -> cadena);
    getchar();
    //printf("\nRecibida la frase... ");
    int largo = contarLargo(estructura->cadena);
    estructura -> cadena = (char*) realloc(estructura -> cadena, sizeof(char)*largo);
    //printf("\nEl largo es %i, realocado el espacio...", largo-1);
    printf("\nBien, ahora ingrese la letra a buscar: ");
    scanf("%c", &(estructura->c));
    //printf("\nRecibida la letra %c...", estructura->c);
    int cant = cantidad(estructura);

    int *apariciones = ocurrencias(estructura, cant);
    printf("\nLa letra que ingresaste esta %i veces en la frase que ingresaste.\n", cant);
    printf("La letra que ingresaste aparece en las posiciones... \n");
    for(int i = 0; i < cant; i++){
        printf("-> %i <-\n", *(apariciones+i));
    }

    free(apariciones);
    free(estructura->cadena);
    free(estructura);
    return 0;
}

int* ocurrencias(Char_string *frase, int cantidad){
    int i = 0, j = 0;
    int *apariciones = (int*) malloc(sizeof(int)*cantidad);
    for(i = 0; *(frase->cadena+i) != '\0'; i++){
        if(*(frase->cadena+i) == frase->c){
            *(apariciones + j) = i+1;
            j++;
        }    
    }
    return apariciones;
}

int cantidad(Char_string * estructura){
    printf("\nBuscando la cantidad...");
    int i = 0, cant = 0;
    for(i = 0; *(estructura->cadena+i) != '\0'; i++){
        //printf("%c", *(estructura->cadena+i));
        if(*(estructura->cadena+i) == estructura->c){
            cant++;
        }    
    }
    return cant;
}

int contarLargo(char * cadena){
    int i;
    char c;
    //printf("\nContando el largo...  ");
    for(i = 0; c != '\0'; i++){
        c = *(cadena+i);
        //printf(" %c ", c);
    }
    printf("\n");
    return i+1;
}