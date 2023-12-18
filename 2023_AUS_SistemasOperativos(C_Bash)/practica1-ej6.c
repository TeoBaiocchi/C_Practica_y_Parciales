#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("error cantidad argumentos");
        return -1;
    }

    struct stat sfile;
    DIR *d;
    struct dirent *dir;

    d = opendir(argv[2]);

    if(!d){
        return -1;
    }

    char * pathCompleto[2048];

    if(strcmp("-e", argv[1]) == 0){
        printf("Lista de archivos completa : \n");
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
    }

    if(strcmp("-d", argv[1]) == 0){
        printf("Lista de directorios: \n");    
        while ((dir = readdir(d)) != NULL) {
            strcpy(pathCompleto, "./");            
            strcat(pathCompleto, argv[2]);
            strcat(pathCompleto, "/");
            strcat(pathCompleto, dir->d_name);
            
            stat(pathCompleto, &sfile);
            if(S_ISDIR(sfile.st_mode) == 1){
                printf("%s\n", dir->d_name);
            }
        }
    }

    if(strcmp("-i", argv[1]) == 0){
        printf("Lista de archivos completa con Nro Inodo : \n");
        while ((dir = readdir(d)) != NULL) {
            printf("%s - inodo: %ld\n", dir->d_name, dir->d_ino);
        }
    }

    closedir(d);
    return 0;

}
