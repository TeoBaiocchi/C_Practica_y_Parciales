#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUENO 0
#define MALO 1

typedef struct Legislador{
   char *nombre;
   struct Legislador *siguiente;
} legislador;

void inserta(char*, legislador**);
void suprime(char*, legislador**);
void mostrar(legislador*);
int miembro(char*, legislador*, legislador*);

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

int main()
{
    int salir = 0;
    legislador* chicos_buenos;
    legislador* chicos_malos;

    chicos_malos = NULL;
    chicos_buenos = NULL;

    //Algunos valores por defecto...
    inserta("Arturo", &chicos_buenos);
    inserta("John", &chicos_buenos);
    inserta("Leonardo", &chicos_buenos);
    inserta("Martin", &chicos_buenos);

    inserta("Justo", &chicos_malos);
    inserta("Archibaldo", &chicos_malos);
    //test de suprimir
    suprime("John", &chicos_buenos);
    

    while(salir == 0){
        //Impresion de cabezera
        limpiarPantalla();
        header();
        verde(); printf("---Chicos Buenos---\n");
        mostrar(chicos_buenos);
        rojo();  printf("---Chicos Malos---\n");
        mostrar(chicos_malos);
        separador();

        //Ingreso de comando
        char aux[25];
        printf("Ingrese el comando: ");
        scanf("%[^\n]", aux);
        bufferEnter();
        
        //Si se ingresa vacio, nada.
        if(!strlen(aux) == 0)
        {
            int i, status;
            //Guardo el primer caracter normalizado para analizarlo
            char primerCaracter = toupper(aux[0]);
            //guardo el resto del comando en nombreCorrecto
            char nombreCorrecto[25];
            for(i = 1; aux[i] != '\0'; i++){
                nombreCorrecto[i-1] = aux[i];
            }
            nombreCorrecto[i-1] = '\0';

            //miembro tambien imprime un mensaje, por eso me interesa que no se haga si el comando es invalido
            //status recibe de miembro: BUENO, MALO, o -1 si no lo encuentra
            if(primerCaracter == 'E' || primerCaracter == 'F' || primerCaracter == 'D'){
                status = miembro(nombreCorrecto, chicos_buenos, chicos_malos);
            } else {
                primerCaracter = 'x';
            }

            //printf("'%c', '%s', %i, %i, %i \n", primerCaracter, nombreCorrecto, status, BUENO, MALO);
            switch(primerCaracter)
            {
                case 'E':
                    salir = 1;
                    printf("Fin del proceso. Presione Enter para cerrar\n");
                    bufferEnter();
                break;

                //Se revisa el caracter ingresado,
                case 'F':
                    switch(status)
                    {
                        //Si es bueno y era bueno, no se hace nada
                        case BUENO:
                            printf("El legislador de voto favorable ya era un chico bueno. No se efectua cambio.\n");
                        break;
                        //Si es bueno y era malo, se borra de malo y se inserta en bueno
                        case MALO:
                            suprime(nombreCorrecto, &chicos_malos);
                            printf("de Chicos Malos\n");
                            inserta(nombreCorrecto, &chicos_buenos);
                            printf("de Chicos Buenos\n");
                        break;

                        //(status = -1), no se encontró
                        default:
                            inserta(nombreCorrecto, &chicos_buenos);
                        break;
                    }
                break;

                case 'D': //Logica idem a la de case F
                    switch(status)
                    {
                        case MALO:
                            printf("El legislador de voto desfavorable ya era un chico malo. No se efectua cambio.\n");
                        break;

                        case BUENO:
                            suprime(nombreCorrecto, &chicos_buenos);
                            printf("de Chicos Buenos.\n");
                            inserta(nombreCorrecto, &chicos_malos);
                            printf("de Chicos Malos\n");
                        break;

                        default:
                            inserta(nombreCorrecto, &chicos_malos);
                            printf("de Chicos Malos\n");
                        break;
                    }
                break;

                default:
                    printf("Ingreso incorreto de comando. Siga el formato especificado (sin espacios)\n");
                break;
                }
        }
        printf("Presione enter para continuar.");
        bufferEnter();

    }

    return 0;
}

void inserta(char * nombre, legislador ** lista){

    legislador* nuevoLegislador;
    nuevoLegislador = (legislador*)malloc(sizeof(legislador));
    nuevoLegislador->nombre = (char *) malloc (25 * sizeof(char));
    strcpy(nuevoLegislador->nombre, nombre);
    if(*lista == NULL){
        *lista = nuevoLegislador;
    } else {
    nuevoLegislador->siguiente = *lista;
    *lista = nuevoLegislador;
    }
    printf("Se agrego al legislador '%s' a la lista ", nuevoLegislador->nombre);
}


int miembro(char * nombreArg, legislador* chicos_buenos, legislador *chicos_malos){

    printf("El legislador ");
    legislador* temp;
    temp = chicos_buenos;

    while(temp != NULL) {
        if(strcmp(temp->nombre, nombreArg) == 0){
            printf("'%s' esta registrado como un ", temp->nombre);
            verde(); printf("Chico Bueno\n"); colorReset();
            return BUENO;
        }
        temp = temp->siguiente;
    }

    temp = chicos_malos;
    while(temp != NULL) {
        if(strcmp(temp->nombre, nombreArg) == 0){
            printf("'%s' esta registrado como un ", temp->nombre);
            rojo(); printf("Chico Malo\n"); colorReset();
            return MALO;
        }
        temp = temp->siguiente;
    }

    printf(" no esta registrado en la base de datos \n");
    return -1;
}

void suprime(char * nombre, legislador ** lista){
    legislador* temp;
    legislador* auxPre;
    temp = *lista;
    auxPre = *lista;
    
    if(strcmp(temp->nombre, nombre) == 0){
        *lista = temp -> siguiente;
        free(temp);
        temp = NULL;
        printf("Se elimino el legislador '%s' \n", nombre);
        return;
    }
    while(temp != NULL){
        if(strcmp(temp->nombre, nombre) == 0){
            auxPre->siguiente = temp->siguiente;    
            free(temp);
            temp = NULL;
            printf("Se elimino el legislador '%s' \n", nombre);
            return;
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
    verde();
    printf("--> Sociedad para la Prevencion de Injusticias con el Atun <--\n");
    amarillo();
    printf("------------Base de Datos de Legisladores-----------------\n");
    separador();
    negro(); printf("Recuerde seguir el formato ["); verde(); printf("F"); negro(); printf("/"); rojo(); printf("D"); negro(); printf("][Nombre] *Todo junto, sin espacios*. o 'E' para terminar\n");colorReset();
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
