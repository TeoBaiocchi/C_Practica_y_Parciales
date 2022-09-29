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

#include<stdio.h>
#include<stdlib.h>



typedef struct direccion{
    char *IP;
    char *Mask;
} Direccion;

void ejercicio1();
void mostrarIP(Direccion * mostrar);
char * obtenerIP(Direccion *extraer);

int main(){
    printf("Ejercicio 1: \n");
    ejercicio1();
    printf("Ejercicio 2: \n");
    //ejercicio2();

    return 0;
}

void ejercicio1(){
    Direccion * defecto = (Direccion *) malloc(sizeof(Direccion));
    defecto->IP = (char*) malloc(sizeof(char) * 17);
    defecto->Mask =(char*) malloc(sizeof(char) * 13);

    defecto->IP = "192.168.146.222";
    defecto->Mask ="255.255.255.0";

    printf("(metodo 1)");
    mostrarIP(defecto);
    char * IP = obtenerIP(defecto);
    printf("(metodo 2)La direccion IP de la estructura es %s \n", IP);
}

void mostrarIP(Direccion *mostrar){
        printf("La direccion IP de la estructura es: %s \n", mostrar->IP);        
}

char * obtenerIP(Direccion *extraer){
    return extraer->IP;
}