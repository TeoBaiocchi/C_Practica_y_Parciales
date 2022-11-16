#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUENO 0
#define MALO 1

typedef struct Legislador{
   char *nombre;
   struct Legislador *siguiente;
} legislador;

void inserta(int, char *, legislador**);
void suprime(int, char*, legislador**);
void mostrar(legislador*);
int miembro(char*, legislador**, legislador**);


//Funciones extra, utilidades y menues
void limpiarPantalla();
void bufferEnter();
void separador();
void verde();
void rojo();
void amarillo();
void blanco();
void negro();
void colorReset();
void header();
void busqueda(legislador*, legislador*);
void menuPrincipal(legislador*, legislador*);
void comandaEliminar(legislador*, legislador*);
void ingresoBueno(legislador*, legislador*);
void ingresoMalo(legislador*, legislador*);


int main(){
    legislador* chicos_buenos;
    legislador* chicos_malos;
    chicos_malos = NULL;
    chicos_buenos = NULL;

    //Algunos valores por defecto...
    inserta(BUENO, "arthur", &chicos_buenos);
    inserta(BUENO, "hosea", &chicos_buenos);
    inserta(MALO, "dutch", &chicos_malos);
    inserta(BUENO, "john", &chicos_buenos);
    inserta(BUENO, "lenny", &chicos_buenos);
    inserta(BUENO, "sadie", &chicos_buenos);
    inserta(MALO, "micah", &chicos_malos);

    menuPrincipal(chicos_buenos, chicos_malos);
    return 0;
}


void menuPrincipal(legislador * chicos_buenos, legislador * chicos_malos){
    int ingreso, salir = 0;
    while(salir != 1){
        limpiarPantalla();
        header();
        printf("\n-Presione 1 para buscar un legislador existente\n");
        printf("-Presione 2 para ingresar un legislador de voto favorable\n");
        printf("-Presione 3 para ingresar un legislador de voto desfavorable\n");
        printf("-Presione 4 para borrar legisladores\n");
        printf("-Presione 5 para ver las listas\n");
        printf("-Presione 6 para salir\n");
        rojo(); printf("-> "); colorReset();
        scanf("%i", &ingreso);
        bufferEnter();
        switch(ingreso){

            case 1:
                limpiarPantalla();
                busqueda(chicos_buenos, chicos_malos);
            break;

            case 2:
                limpiarPantalla();
                //comandaIngreso(chicos_buenos, chicos_malos);
            break;

            case 3:
                limpiarPantalla();
                ingresoMalo(chicos_buenos, chicos_malos);
            break;

            case 4:
                limpiarPantalla();
                comandaEliminar(chicos_buenos, chicos_malos);
            break;

            case 5:
                limpiarPantalla();
                verde(); printf("---Chicos Buenos---\n");
                mostrar(chicos_buenos);
                printf("\n");
                rojo(); printf("---Chicos Malos---\n");
                mostrar(chicos_malos);
                colorReset();
                printf("\nPresione enter para continuar");
                bufferEnter();
            break;

            case 6:
                salir = 1;
            break;



            default:
                limpiarPantalla();
        }
    }
}

void ingresoMalo(legislador * chicos_buenos, legislador * chicos_malos){
    header();
    printf("Ingrese el nombre del legislador de voto desfavorable: ");
    char aux[50];
    scanf("%[^\n]", aux);
    bufferEnter();
    int encontrado;
    encontrado = miembro(aux, &chicos_buenos, &chicos_malos);
    printf("\n %i \n", encontrado);
    switch(encontrado){
        case BUENO:
            suprime(BUENO, aux, &chicos_buenos);
            inserta(MALO, aux, &chicos_malos);
        break;

        case MALO:
            printf("Ya esta ingresado en sistema. No se efectuo cambio.\n");
        break;

        case -1:
            inserta(MALO, aux, &MALO);
        break;

        default:
            printf("Algo salio mal...\n");
        break;
    }
    printf("Presione Enter para continuar.");
    bufferEnter();

}

void comandaEliminar(legislador* chicos_buenos, legislador* chicos_malos){
        header();
        printf("Ingrese el nombre del legislador a eliminar: ");
        char aux[50];
        scanf("%[^\n]", aux);
        bufferEnter();
        int encontrado = miembro(aux, &chicos_buenos, &chicos_malos);
        int i;
        if(encontrado != -1){
            printf("Presione 1 para confirmar que lo quiere eliminar.");
            scanf("%i", &i);
            bufferEnter();
            if(i == 1){
                if(encontrado == BUENO){
                suprime(BUENO, aux, &chicos_buenos);
            } else {
                suprime(MALO, aux, &chicos_malos);
                }
            }
        } else {
            printf("No se encontro al legislador\nPresiona enter para continuar");
            bufferEnter();
        }
}



void inserta(int tipo, char * nombre, legislador ** lista){

    legislador* nuevoLegislador;
    nuevoLegislador = (legislador*)malloc(sizeof(legislador));

    nuevoLegislador->nombre = nombre;
    nuevoLegislador->siguiente = *lista;
    *lista = nuevoLegislador;
    printf("Se agregó al legislador '%s' en la lista de chicos ", nuevoLegislador->nombre);
    if(tipo == BUENO){
        verde(); printf("buenos. \n"); colorReset();
    } else {
        rojo(); printf("malos. \n"); colorReset();
    }
}



void busqueda(legislador* chicos_buenos, legislador* chicos_malos){
    char aux[50];
    header();
    printf("Ingrese el nombre del legislador a buscar: ");
    scanf("%[^\n]", aux);
    bufferEnter();
    miembro(aux, &chicos_buenos, &chicos_malos);
    printf("Presione enter para continuar.");
    bufferEnter();
}

int miembro(char * nombreArg, legislador** chicos_buenos, legislador ** chicos_malos){

    printf("El legislador '%s'", nombreArg);
    legislador* temp;
    temp = *chicos_buenos;

    while(temp != NULL) {
        if(strcmp(temp->nombre, nombreArg) == 0){
            printf(" esta registrado como un ");
            verde(); printf("Chico Bueno\n"); colorReset();
            return BUENO;
        }
        temp = temp->siguiente;
    }

    temp = *chicos_malos;
    while(temp != NULL) {
        if(strcmp(temp->nombre, nombreArg) == 0){
            printf(" esta registrado como un ");
            rojo(); printf("Chico Malo\n"); colorReset();
            return MALO;
        }
        temp = temp->siguiente;
    }

    printf(" no esta registrado en la base de datos \n");
    return -1;
}

void suprime(int tipo, char * nombre, legislador ** lista){
    legislador* temp;
    legislador* auxPre;
    temp = *lista;
    auxPre = *lista;
    while(temp != NULL){
        if(strcmp(temp->nombre, nombre) == 0){
            auxPre->siguiente = temp->siguiente;
            free(temp);
            temp = NULL;
            printf("Se elimino el legislador '%s' \n", nombre);
            //return;
        } else {
            auxPre = temp;
            temp = temp->siguiente;
        }
    }
}

void mostrar(legislador* lista){
    legislador * temp;
    temp = lista;
    if(temp == NULL){
        printf("La lista esta vacia\n");
    }
    while(temp != NULL){
        printf("%s\n", temp->nombre);
        temp = temp->siguiente;
    }
}







void separador(){
    negro();
    printf("---------------------------------\n");
    colorReset();
}

void header(){
    verde(); printf("--> Sociedad para la Prevencion de Injusticias con el Atun <--\n");
    separador();
    amarillo(); printf("Base de Datos de Legisladores\n");
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

/*
void comandaIngreso(legislador* chicos_buenos, legislador* chicos_malos){
    //Funcion en desuso. No me anduvo y no supe por que y no quise perder mas tiempo
    // Lo reemplace por dos entradas diferentes en el menu para ingresar buenos o malos que si funciona
    // Pero no encuentro el motivo
    int valido;

    while(1)
    {
        int i, valido = 0;
        limpiarPantalla();
        headerComanda();
        char aux[50] = "", aux2[49] = "";

        printf("Ingrese el comando: ");
        scanf("%[^\n]", aux);
        bufferEnter();

        for(i = 1; aux[i] != '\0'; i++){
            aux2[i-1] = aux[i];
        }
        aux2[i] = '\0';

        printf("\n DEBUG, -%s-, -%s- \n\n", aux, aux2);

        if(aux[0] == 'E' || aux[0] == 'e'){
            printf("Se terminó el proceso de ingreso.\n");
            printf("Presione enter para continuar.");
            bufferEnter();
            return;
        }

        int encontrado = miembro(aux2, &chicos_buenos, &chicos_malos); //0 bueno, 1 malo, -1 no encontrado

        if(aux[0] == 'F' || aux[0] == 'f')
        {
            if(encontrado == MALO)
            {
                suprime(MALO, aux2, &chicos_malos);
                inserta(BUENO, aux2, &chicos_buenos);
                valido = 1;
            }
            if(encontrado == -1)
            {
                inserta(BUENO, aux2, &chicos_buenos);
                valido = 1;
            }
        }

        if(aux[0] == 'D' || aux[0] == 'd')
        {
            if(encontrado == BUENO)
            {
                suprime(BUENO, aux2, &chicos_buenos);
                inserta(MALO, aux2, &chicos_malos);
                valido = 1;
            }
            if(encontrado == -1)
            {
                inserta(MALO, aux2, &chicos_malos);
                valido = 1;
            }
        }

        if(strlen(aux)<2){
            valido = 0;
        }

        if(valido == 0){
            printf("El comando no fue introducido correctamente.\n");
        }

        printf("Presione enter para continuar.");
        bufferEnter();
    }

}

void headerComanda(){
    verde(); printf("--> Base de Datos de Legisladores <--\n");
    separador();
    amarillo(); printf("Sociedad para la Prevención de Injusticias con el Atún\n");
    separador();
    negro(); printf("Recuerde seguir el formato ["); verde(); printf("F"); negro(); printf("/"); rojo(); printf("D"); negro(); printf("][Nombre], o 'E' para terminar\n");
    separador();
}

*/
