#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Nodo {
 int dato;
 struct nodo *sgte;
 } nodo;


 void apila(nodo **);

 int desapila(nodo **);

 /*void vaciaPila(nodo **);

 int tamanio(nodo *);*/

 int estaVacia(nodo **); //la uso para checkear si la lista esta vacia antes de apilar o desapilar

 int cima1(nodo *); //muestra el primer elemento sin eliminarlo

 void mostrarPila(nodo *);

 int main(){

    int a, b;

    nodo *cima = NULL;

    srand(time(NULL));

    do{

    printf("Presione 1 para ingresar o 2 para sacar (9 para salir): ");
    scanf("%d", &a);

    switch(a){

        case 1:
            apila(&cima);
            mostrarPila(cima);
            break;

        case 2:
            if(estaVacia(&cima) == 0){
                printf("La pila esta vacia, no se pueden quitar mas elementos\n");
            } else{
                desapila(&cima);
                mostrarPila(cima);
            }
            break;

        case 9:
            break;

        default:
            printf("Ingreso una opcion incorrecta, ingrese de nuevo\n");
            break;
    }

    /*printf("Desea ver el ultimo elemento de la tabla? 1 Si | 0 No: ");
    scanf("%d", &b);

    if(b == 1){
        printf("\n%d", cima1());
    }*/

    } while(a!=9);

    return 0;
 }

 void apila(nodo **cima){

    nodo *nuevoNodo;

    if(estaVacia(cima) == 0){

        nuevoNodo = (nodo *) malloc (sizeof(nodo));

        nuevoNodo->dato = rand() % 10;
        nuevoNodo->sgte = NULL;
        *cima = nuevoNodo;

    } else{

        nuevoNodo = (nodo *) malloc (sizeof(nodo));

        nuevoNodo->dato = rand() % 10;
        nuevoNodo->sgte = *cima;
        *cima = nuevoNodo;
    }

    return;

 }

 int desapila(nodo **cima){

    nodo *aux;

    aux = *cima;
    *cima = aux->sgte;
    free(aux);

 }

 void mostrarPila(nodo *cima){

    nodo *temp = cima;

    if(cima == NULL){
        printf("La lista esta vacia\n");
    } else{

        while(temp != NULL){

            printf("%d\n", temp->dato);

            temp = temp->sgte;
        }
    }

    return;

}

 int estaVacia(nodo **cima){

    if(*cima == NULL){
        return 0;
    } else{
        return 1;
    }

 }

 /*int cima1(nodo *cima){

    return cima->dato;
 }*/
