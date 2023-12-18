#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

    int fd;
    int espacioResultado = 2048;
    int leidoTotal = 0;
    int banderaOutput = 0;
    
    char buff[2048];
    char * path;
    char * resultado = malloc(espacioResultado);
    
    resultado[0] = '\0';
    
    for(int nro = 1; nro < argc; nro++){
        //Leemos todos los argumentos ingresados

        path = argv[nro];

        if(strcmp("-o", path) == 0){
            banderaOutput = 1;
            path = argv[nro+1];
            break;
        }

        fd = open(path, O_RDONLY);
        int leido = read(fd, buff, 2048);
        buff[leido+1] = '\0';        
        close(fd);

        leidoTotal += leido;
        if(leidoTotal >= espacioResultado - 1){
            espacioResultado = espacioResultado * 2;
            resultado = realloc(resultado, espacioResultado);
        }
        strcat(resultado, buff);
    }

    resultado[strlen(resultado)+1] = EOF;
    
    if(banderaOutput == 1){
        //Misma verificacion. Tengo que escribir en el archivo que quedo en el path
        printf("Se escribio la concatenacion en el archivo indicado.");
        fd = open(path, O_WRONLY);
        write(fd, resultado, strlen(resultado)+1);
        close(fd);
    } else {
        printf("La concatenacion del contenido de todos los archivos ingresados es:\n%s", resultado);
    }

}
