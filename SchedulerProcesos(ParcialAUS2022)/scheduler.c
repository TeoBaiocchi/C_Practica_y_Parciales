#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include <ctype.h>

#define MAX_PROCESOS 10
#define MAX_PROCESADORES 2

typedef struct proceso{
    int procesador;
    int proceso;
    int prioridad;
    char estado[10];
} Proceso;

static int idPrioridad = 0;
static int procesadoresEnUso[MAX_PROCESADORES] = {0}; //0 libre, 1 ocupado. Inicializado en 0 (los indices no especificados se llenan con 0)

Proceso* scheduling[10];



//Ingresa un proceso donde haya lugar disponible en el scheduler
//Devuelve la posicion donde lo ingreso, solamente para poder mostrarla luego en pantalla
int ingresaProceso();

//Cambia el estado del proceso, de ser posible (segun los procesadores disponibles), o lo elimina (Llamando a terminaProceso)
void asignaEstados(Proceso** cambiar);

//Libera la memoria del proceso, y asigna el puntero original a null (por eso necesita tomar un puntero a puntero)
void terminaProceso(Proceso** eliminar);

//Itera sobre el scheduler y envia cada proceso existente a asignaestado()
void recorreCola();

void mostrarScheduler();



//**Otras utilidades**
int enteroAleatorioUnico(); //Genera un entero y revisa todo el scheduler para ver que no este repetido. Si lo esta, genera otro y repite
void ingresarProcesos(int x); //Ingresa un numero x de procesos llamando a ingresaproceso()
void liberarMemoria(); //hace un free para todo el scheduler
void limpiarPantalla(); 
void bufferEnter(); //Presione enter para continuar / limpia buffer

//Funciones de formato de consola
void separador();
void verde();
void rojo();
void amarillo();
void blanco();
void negro();
void colorReset();
void header();
void menuPrincipal();
void funcionPreset();
void funcionManual();


/* Programa */

int main(){
    menuPrincipal();
    limpiarPantalla();
    printf("Liberando memoria... \n");
    printf("Programa cerrado.");
    return 0;
}

/*FUNCIONES PRINCIPALES*/

int ingresaProceso(){
    int i; 
    for(i = 0; i < MAX_PROCESOS; i++) {
        if(scheduling[i] == NULL) {
            //Si el puntero en la direccion i es nulo, es porque no esta inicializado, es decir, se puede insertar un proceso
            scheduling[i] = (Proceso*) malloc(sizeof(Proceso));

            scheduling[i]->prioridad = idPrioridad;
            idPrioridad++;

            strcpy(scheduling[i]->estado, "Nuevo");

            scheduling[i]->procesador = 0;

            scheduling[i]->proceso = enteroAleatorioUnico();
            
            return i;
        }
    }
    return -1;
}


void recorreCola() {
    separador();
    printf("Recorriendo cola... \n");
    int i;

    for(i = 0; i < MAX_PROCESOS; i++) {
        if(scheduling[i] != NULL) {
            asignaEstados(&scheduling[i]);
        }
    }

    verde(); printf("Scheduler actualizado.\n"); colorReset();
}


void asignaEstados(Proceso** cambiarAux) {
    Proceso* cambiar = *(cambiarAux);
    
    if(strcmp(cambiar->estado, "Terminado") == 0) {
        terminaProceso(cambiarAux);
        return;
    }
    
    if(strcmp(cambiar->estado, "Corriendo") == 0) {
        strcpy(cambiar->estado, "Terminado");
        return;
    }

    if(strcmp(cambiar->estado, "Listo") == 0) {
        for(int i = 0; i < MAX_PROCESADORES; i++) {
            if(procesadoresEnUso[i] == 0){
                strcpy(cambiar->estado, "Corriendo");
                cambiar->procesador = i+1;
                procesadoresEnUso[i] = 1; 
                return;
            }
        }
    }

    if(strcmp(cambiar->estado, "Nuevo") == 0) {
        strcpy(cambiar->estado, "Listo");
        return;
    }
}



void terminaProceso(Proceso ** eliminar) {
    int indice = ((*(eliminar))->procesador) - 1;
    procesadoresEnUso[indice] = 0;
    free(*eliminar);
    *eliminar = NULL;
}


void mostrarScheduler(){
    separador();
    printf("Imprimiendo Scheduler... \n");
    for(int i = 0; i < MAX_PROCESOS; i++){
        if(scheduling[i] /*!= NULL*/){
            printf("[%i] -> {%i;%i;%i;'%s'}\n", i, scheduling[i]->procesador, scheduling[i]->proceso, scheduling[i]->prioridad, scheduling[i]->estado);
        }
        else {
            negro(); printf("[%i] -> {Libre}\n", i); colorReset();
        }
    }
}


/* MENUES */

void menuPrincipal(){
    int ingreso, salir = 0;
    while(salir != 1){
        limpiarPantalla();
        header();
        printf("\n-Presione 1 para ver el funcionamiento del programa automaticamente con un preset\n(El programa se corre solo)\n\n");
        printf("-Presione 2 para utilizar el programa a mano\n\n");
        printf("-Presione 3 para salir\n\n");
        rojo(); printf("-> "); colorReset();
        scanf("%i", &ingreso);
        bufferEnter();
        switch(ingreso){
            
            case 1: 
                limpiarPantalla();
                header();
                funcionPreset();
            break;
            
            case 2: 
                limpiarPantalla();
                funcionManual();
            break;
            
            case 3:
                salir = 1;
            break;

            default:
                limpiarPantalla();
        }
    }
}

void funcionManual(){
    int salir = 0, ingreso;
    while(salir != 1){
        limpiarPantalla();
        header();
        rojo();printf("->Programa en modo manual<-\n");colorReset();
        mostrarScheduler();
        printf("Ingrese un numero de procesos para agregrar, o 0 para actualizar el scheduler\n");
        printf("Para volver al menu principal, ingrese -1\n");
        rojo(); printf("-> "); colorReset();
        scanf("%i", &ingreso);
        bufferEnter();

        switch(ingreso){
            case 0:
                recorreCola();
                break;
            
            case (-1):
                salir = 1;

            default:
                ingresarProcesos(ingreso);
                break;
                }       
        }
    liberarMemoria();
}

void funcionPreset(){
    printf("Inicio del programa\n");
    rojo(); printf("PRESET\n"); colorReset();
    mostrarScheduler();
    ingresarProcesos(3);
    mostrarScheduler();
    recorreCola();   
    mostrarScheduler();
    recorreCola();
    mostrarScheduler();
    recorreCola();
    mostrarScheduler();
    recorreCola();
    ingresarProcesos(2);
    mostrarScheduler();
    recorreCola();
    ingresarProcesos(5);
    mostrarScheduler();
    recorreCola();
    mostrarScheduler();
    recorreCola();
    mostrarScheduler();
    recorreCola();
    mostrarScheduler();
    recorreCola();
    separador();
    printf("Fin del preset. Presione enter para volver al menu. \n");
    liberarMemoria();
    bufferEnter();
}


/* FUNCIONES DE UTILIDAD */

void ingresarProcesos(int x){
    separador();
    amarillo(); printf("Ingresando %i procesos... \n", x); colorReset();
    int ingresados[MAX_PROCESOS+1], i;
    
    for(i = 0; i < MAX_PROCESOS+1; i++){
        ingresados[i] = (-2);
        
        //Inicializo el array ingresados en -2 por motivos de control
        //El array ingresados luego es unicamente para mostrar en pantalla que lugares fueron reservados
    }
    printf(" ");
    for(i = 0; i < x; i++){
        ingresados[i] = ingresaProceso();
        if(ingresados[i] == (-1)){
            rojo(); printf("Se alcanzo el maximo (%d) de procesos. No pudieron ingresarse todos los solicitados.\n", MAX_PROCESOS); colorReset();
            printf("Presione enter para continuar. \n");
            bufferEnter();
            break;
        }
    }

    verde(); printf("Se ingresaron %d procesos en las posiciones: ", i);
    
    for(i = 0; ingresados[i] != (-2) && ingresados[i] != (-1); i++){

        if(i != 0){
            printf("-");
        }

        printf(" %i ", ingresados[i]);
    } 
    colorReset();
    printf("\n");
}

void liberarMemoria(){
        int i;
        idPrioridad = 0;
        for(i = 0; i < MAX_PROCESADORES; i++){
            procesadoresEnUso[i] = 0;
        }
        for(i = 0; i < MAX_PROCESOS; i++){
        free(scheduling[i]);
        scheduling[i] = NULL;
    }
}

int enteroAleatorioUnico(){
    srand(time(NULL));
    int repetido = 1, nro;

    while(repetido == 1) {
        nro = rand()%9998+1;
        repetido = 0;

        for(int i = 0; i < MAX_PROCESOS; i++){
            if(scheduling[i] != NULL){
                if(scheduling[i]->proceso == nro){
                    repetido = 1;
                }
            }
        }
    }
    return nro;
}


/*FORMATO DE TEXTO y PANTALLA*/


void separador(){
    negro();
    printf("---------------------------------\n");
    colorReset();
}

void header(){
    verde(); printf("--> Panel de operacion del Scheduler <--\n");
    separador();
    amarillo(); printf("Maximo de procesos manejados = %d\n", MAX_PROCESOS);
    separador();
    separador();
}

void verde(){
    printf("\033[1;32m");
}

void rojo(){
    printf("\033[1;31m");
}

void amarillo(){
    printf("\033[1;33m");
}

void blanco(){
    printf("\033[1;37m");
}
void negro(){
    printf("\033[1;30m");
}

void colorReset(){
    printf("\033[0m");
}


void limpiarPantalla(){
  #if defined(linux) || defined(unix) || defined(APPLE)
    system("clear");
  #endif

  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #endif
 }


void bufferEnter(){
  int c;
  while ((c = getchar()) != '\n' && c != EOF){}
}