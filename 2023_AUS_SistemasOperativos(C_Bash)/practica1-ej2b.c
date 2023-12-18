#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int cmpfunc(const void *a, const void *b) { 
  return (*(int *)a - *(int *)b);
}

int busqueda(int, int *, int);
void buscar_lista(int, int *, int);
int *crear_lista(int);

int main(int argc, char *argv[]) {
  srand(time(NULL));
  if (argc != 2) {
    printf("Cantidad de argumentos no admitida. Finalizando.");
    return -1;
  }

  int longLista = atoi(argv[1]);
  if (longLista < 1) {
    printf("Longitud no admitida. Finalizando...");
    return -1;
  }

  int *lista = crear_lista(longLista);
  unsigned int numero;
  printf("Se genero automaticamente una lista ordenada de la longitud ingresada:\n{ ");
  for (int i = 0; i < longLista; i++) {
    printf("%d ", lista[i]);
  }
  printf("}\n");
  printf("Ingrese el numero a buscar en la lista ->");
  scanf("%u", &numero);
  buscar_lista(numero, lista, longLista);
  free(lista);
  return 0;
}

int *crear_lista(int longitud) {
  int *lista = malloc(sizeof(int) * longitud);
  for (int i = 0; i < longitud; i++) {
    lista[i] = rand() % 100;
  }
  qsort(lista, longitud, sizeof(int), cmpfunc);
  return lista;
}

void buscar_lista(int numero, int *lista, int longitudLista) {
  int resultado = busqueda(longitudLista, lista, numero);
  if (resultado == 1) {
    printf("Se encontro el numero en la lista!\n");
  } else
    printf("El numero pareciera no estar en la lista.\n");
}

int busqueda(int longitud, int *lista, int numero) {
   int * item = (int*) bsearch (&numero, lista, longitud, sizeof (int), cmpfunc);
   if( item != NULL ) {
      return 1;
   } else {
      return 0;
   }
}