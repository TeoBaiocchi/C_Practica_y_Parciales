/*Crear los ejercicios en archivos individuales, anteponiendo el nombre y
apellido del alumno, ej: luciano_diamand_ej1.c
1) Defina una estructura que permita almacenar la siguiente información:
i) dirección IP
ii) mascara de red
Crear una función que tome un puntero a dicha estructura y que devuelva
una cadena con el número de red.
Ej:
IP: 192.168.146.222
Mask: 255.255.255.0
Salida: 192.168.146.0
2) Definir la función expandir con el siguiente prototipo:
int **expandir(int **matriz, int filas, int cols);
que dada una matriz, la cantidad de filas y columnas de la misma, construya
otra matriz con una fila más y una columna más, completando los valores
nuevos de la matríz con 0.*/

//INCOMPLETO

#include<stdio.h>
#include<stdlib.h>

typedef struct direccion{
    char *IP;
    char *Mask;
} Direccion;

void ejercicio1();

char * obtenerRed(Direccion *extraer);

int main(){
    printf("Ejercicio 1: \n");
    ejercicio1();
    printf("Ejercicio 2: \n");
    //ejercicio2();

    return 0;
}

void ejercicio1(){
    Direccion * defecto = (Direccion *) malloc(sizeof(Direccion));
    defecto->IP = (char*) malloc(sizeof(char) * 18);
    defecto->Mask =(char*) malloc(sizeof(char) * 18);

    defecto->IP = "192.168.146.222";
    defecto->Mask = "255.255.255.0";

    char * red = obtenerRed(defecto);
    printf("La direccion de la estructura es %s \n", red);
}

char * obtenerRed(Direccion *extraer){
    char **segmentosIp;
    segmentosIp = (char**) malloc(sizeof(char*) * 5);
    int i;
    for(i = 0; i < 4; i++){
        *(segmentosIp+i) = (char*) malloc(sizeof(char) * 5);
    }
    int j = 0;
    for(i = 0; *(extraer->IP+i) != '\0' ; i++){
        if( *(extraer->IP +i) != '.'){
            *(*(segmentosIp+j)+i) = *(extraer->IP+i);
        } else {
            j++;
        }
    }

    j=0;
int    k=0;
    char * devolver = (char*) malloc(sizeof(char) * 20);
    for(i=0; *(extraer->Mask+i) != '\0'; i++){

        if(*(extraer->Mask+i) != '\0'){
            *(devolver+j) = *(*(segmentosIp+k));
            j++;
            *(devolver+j) = *(*(segmentosIp+k))+1;
            j++;
            *(devolver+j) = *(*(segmentosIp+k))+2;
            j++;
            k++;
        } else{
            i++;
            *(devolver+j) = '.';
            printf(" %c ", *(devolver+j));
            j++;
        }
    }

    return devolver;
}
/*typedef struct direccion{
    char *IP;
    char *Mask;
} Direccion;*/
