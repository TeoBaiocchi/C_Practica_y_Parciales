#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void recibirSenial(int sig) {
  printf("Recibida la Senial SIGUSR1.\n");
  _exit(0);
}

int main(int argc, char *argv[]) {

    if (argc != 3){
        printf("La cantidad de argumentos no es la esperada.\nIngrese siguiendo el formato: 'DD YYYY'");
        return -1;
    }

    int status;
    int pid = fork();

    if (pid == 0) {
        char *args[3];
        args[1] = argv[1];
        args[2] = argv[2];
        int ret = execv("/bin/cal", args);
        if (ret == -1){
            perror("execve");
            return -1;
        }
    } else {
        printf("Proceso padre esperando por hijo %d\n", pid);
        wait(&status);
    }
    printf("Hijo %d terminado\n", pid);
    pid = fork();
    if (pid == 0) {
        signal(SIGUSR1, recibirSenial);
        while(1);
    } else {
        printf("Proceso padre esperando por hijo %d\n", pid);
        wait(&status);
    }

    printf("Hijo %d terminado\n", pid);
    printf("Proceso padre %d terminado\n", getpid());
    return 0;
}
