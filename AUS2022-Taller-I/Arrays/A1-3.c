#include <stdio.h>
#include <stdlib.h>

#define N 9

void limpiarPantalla(){
  #if defined(linux) || defined(unix) || defined(APPLE)
    system("clear");
  #endif

  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #endif
}

void bufferEnter(){
  //fflush(stdin);
  int c;
  while ((c = getchar()) != '\n' && c != EOF){} 
}

int main(){

    int enteros[N], i, posypar = 0, poseimpar = 0, negypar = 0, negeimpar = 0;
    printf("Cargue 10 valores para una matriz \n");
    for (i=0; i<=N; i++) {
       printf("Posicion [%d]: ", i);
       scanf("%d", &enteros[i]);
        if(enteros[i] >= 0) {
           if(enteros[i] % 2 == 0)
                 posypar++;
            else poseimpar++;
       } 
        else if (enteros[i] % 2 == 0) {
            negypar++;
       } 
        else negeimpar++;

       limpiarPantalla();
   }
    printf("Valores validados. Presione enter para mostrar los resultados.");
    fflush(stdin);
    bufferEnter();
    //bufferEnter();
    limpiarPantalla();
    printf("La matriz tiene %d valores pares positivos, %d valores pares negativos\n%d valores impares positivos, %d valores impares negativos", posypar, negypar, poseimpar, negeimpar);
    printf("\nPresione enter para salir del programa.");
    bufferEnter();
}