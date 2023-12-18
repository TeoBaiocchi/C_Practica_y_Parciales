#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define TAMANIO_INPUT 1024

int main(int argc, char argv[])
{
  FILE *stream = popen("wc -l -w -c", "w");
  char input[TAMANIO_INPUT];
  int bandera = 0;
  printf("- Ingrese multiples lineas, separadas por ENTER-\n- Para terminar, presione enter sin ingresar nada -\n");
  do
  {
    memset(input, 0, TAMANIO_INPUT);
    printf("-> ");
    scanf("%[^\n]", input);
    while (getchar() != '\n');
    
    if(input[0] == 0){
      bandera = 1; 
      }
    else {
      fprintf(stream, "%s\n", input);
    }

  } while (bandera == 0);
  printf("La cantidad de lineas, palabras y caracteres escritos son:\n");
  pclose(stream);
  return 0;
}