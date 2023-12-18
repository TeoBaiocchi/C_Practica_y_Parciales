#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1
#define TAMANIO_INPUT 1024

int main(int argc, char *argv[]){

    int fd[2], bandera = 0, status;
    pipe(fd);
    char input[TAMANIO_INPUT];

    printf("- Ingrese multiples lineas, separadas por ENTER-\n- Para terminar, presione enter sin ingresar nada -\n- Entonces el programa devolvera cantidad de lineas, palabras, y caracteres -\n");
    
    int pid = fork();
    if (pid != 0) {
        // PADRE
        close(fd[READ]);
        while (bandera == 0) {

            memset(input, 0, TAMANIO_INPUT); //Limpiado de string, menester para poder detectar "Enter" sin errores
            printf("-> ");
            scanf("%[^\n]", input);
            while (getchar() != '\n');

            if(input[0] == 0) { //Deteccion de enter
                close(fd[WRITE]);
                wait(&status);
                bandera = 1;
            } else {
                write(fd[WRITE], input, strlen(input));
                write(fd[WRITE], "\n", 1);
            }
        }
    } else {
        // HIJO
        dup2(fd[READ], STDIN_FILENO);
        close(fd[READ]);
        close(fd[WRITE]);
        char *command[] = {"wc", "-l", "-w", "-c", NULL};
        execv("/usr/bin/wc", command);
        return 0;
    }
    return 0;
}

