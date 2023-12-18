#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include<sys/wait.h>


int main(){

    //Limite arbitrario.
    char input[50];
    int banderaSalir = 0;
    int fd1[2];
    int fd2[2];
    int pid;
    int status;

    while(banderaSalir == 0){
        printf("Escriba aqui una operacion (de la forma 'entero + - / * entero') -> ");
        scanf("%[^\n]", input);
        while(getchar() != '\n');

        //2 Pipes, en el primero el padre escribira y el hijo leera.
        //En el 2do viceversa.
        pipe(fd1);
        pipe(fd2);
        pid = fork();
        if(pid != 0){ //PADRE
            //CICLO PIPE 1
            //Cierro lectura, para poder escribir. Escribo, y cierro escritura.
            close(fd1[0]);
            write(fd1[1], input, strlen(input)+1);
            close(fd1[1]);
            //Hecho esto espero que el hijo termine de procesar.
            wait(&status);
            //Fin pipe 1.

            //CICLO PIPE 2
            //Utilizo strings auxiliares para claridad
            char stringLeidoDeHijo[50];
            stringLeidoDeHijo[0] = '\0';
            //Cierro escritura, leo y cierro lectura.
            close(fd2[1]);
            read(fd2[0], stringLeidoDeHijo, 50);
            close(fd2[0]);
            //Fin pipe 2.
            printf("El resultado de la operacion es: '%s'\n", stringLeidoDeHijo);
        } else { //HIJO

            //Ciclo PIPE 1
            //Cierro escritura, leo, cierro lectura.
            close(fd1[1]);
            char stringLeidoDePadre[50];
            stringLeidoDePadre[0] = '\0';
            read(fd1[0], stringLeidoDePadre, 50);
            close(fd1[0]);
            //FIN PIPE 1

            //PARSEO Y OPERATORIA
            //Esto asume que la string ingresada va a ser exclusivamente como el enunciado plantea (x +-/* x)
            //Cualquier otra cosa rompera el programa.
            int nro1, nro2, resultado;
            char operador;
            char * sectorString = strtok(stringLeidoDePadre, " ");
            nro1 = atoi(sectorString);

            sectorString = strtok(NULL, " ");
            operador = sectorString[0];

            sectorString = strtok(NULL, " ");
            nro2 = atoi(sectorString);

            switch(operador){
            case '+':
                resultado = nro1 + nro2;
                break;
            case '-':
                resultado = nro1 - nro2;
                break;
            case '*':
                resultado = nro1 * nro2;
                break;
            case '/':
                resultado = nro1 / nro2;
                break;
            default:
                resultado = -1;
                break;
            }
            char resultadoString[50];
            sprintf(resultadoString, "%i", resultado);

            //Ciclo PIPE 2
            close(fd2[0]);
            write(fd2[1], resultadoString, strlen(resultadoString)+1);
            close(fd2[1]);
            //fin pipe 2
            //fin hijo.
            exit(0);
        }
        printf("Para realizar otra operacion, ingrese '0', de lo contrario saldra del programa -> ");
        int nro;
        scanf("%i", &nro);
        while(getchar() != '\n');
        if(nro != 0){
            banderaSalir = 1;
        }
    }
    return 0;
}



    
