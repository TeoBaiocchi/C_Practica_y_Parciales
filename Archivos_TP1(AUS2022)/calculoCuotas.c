#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bufferEnter();
void limpiarPantalla();
void insertaPersona(char*);
void mostrarPersonas();
void insertaPlan(char*);
void mostrarPlanes();
float calcularPrecio(int, int);
void leerPersonas(FILE *);
void leerPlanes(FILE *);
void generarCuotas();

typedef struct Persona{
   char *nombre;
   char *apellido;
   int edad;
   char sexo;
   int antiguedad;
   char plan;
   struct Persona *siguiente;
   struct Persona *anterior;
} persona;
persona* listaPersonas = NULL;

typedef struct Plan{
   char codigo;
   int precio;
   int porcentajeDescuento;
   struct Plan *siguiente;
} plan;
plan * listaPlanes = NULL;




int main()
{
  printf("Bienvenido al programa de calculo de cuota del club\n\n");
  printf("El programa lee de dos archivos que deben estar situados en el mismo directorio\n");
  printf("Uno llamado 'personas.txt' que debe estar formateado de la siguiente forma: \n'[nombre]-[apellido]-[edad]-[sexo]-[antiguedad]-[codigo de plan]'\n\n");
  printf("y otro, 'plan.txt' que debe estar formateado de la siguiente forma: \n'[codigo de una sola letra]-[monto entero]-[porcentaje de descuento]'\n\n");
  printf("Ambos deben tener UNICAMENTE un dato por linea, \ny no deben estar separados por espacios ni alejarse del formato dado.\n\n");
  printf("El programa creara un nuevo archivo (o lo pisara sin aviso, si ya existe) \ndonde todas las entradas del archivo persona tendran su cuota calculada segun su plan\n");
  printf("Presione enter para comenzar el proceso automatico");
  bufferEnter();
  limpiarPantalla();

  FILE *fpPersonas,*fpPlanes, *fpCuotas;

  printf("Cargando desde archivo personas.txt...\n");
  leerPersonas(fpPersonas);
  printf("Cargando desde archivo planes.txt...\n");
  leerPlanes(fpPlanes);
  printf("\nListado de Personas: \n");
  mostrarPersonas();
  printf("\nListado de Planes:\n");
  mostrarPlanes();
  printf("\nGenerando archivo con calculo de cuotas...\n");
  generarCuotas();
  printf("Fin del programa. Presione enter para concluir");
  bufferEnter();
  return 0;
}

void generarCuotas(){
    persona ** personas = &listaPersonas;
    persona * temp = *personas;

    if(temp == NULL){
        printf("No hay personas cargadas. Terminando el programa.");
        return;
    }

    FILE * fpCalculoCuotas = fopen("calculoCuotas.txt" ,"w+");
    if(fpCalculoCuotas != NULL){
        do{
            int descuentoActual = 0, precioActual = 0;
            float total = 0;

            if(temp->edad < 12 || temp->edad > 65)
            {
                descuentoActual = 5;
            }

            plan * tempPlan = listaPlanes;
            while(tempPlan != NULL)
            {
                if(tempPlan->codigo == temp->plan)
                {
                    if(temp->antiguedad > 24)
                    {
                        descuentoActual = descuentoActual + tempPlan->porcentajeDescuento;
                    }
                    precioActual = tempPlan->precio;
                }
                tempPlan = tempPlan->siguiente;
            }

           total = calcularPrecio(precioActual, descuentoActual);
           printf ("Cuota calculada: %s-%s-%i-%c-%i-%c-%.2f\n", temp->nombre, temp->apellido, temp->edad, temp->sexo, temp->antiguedad, temp->plan, total);
           fprintf (fpCalculoCuotas , "%s-%s-%i-%c-%i-%c-%.2f\n", temp->nombre, temp->apellido, temp->edad, temp->sexo, temp->antiguedad, temp->plan, total);
           temp = temp->siguiente;
        }while(temp != *personas);

        if (!fclose(fpCalculoCuotas)){
            printf ("Archivo creado y cerrado.\n");
        } else {
            printf("Error al cerrar el archivo.\n");
        }
    } else {
        printf("Hubo un error creando el archivo");
        return;
    }

}

float calcularPrecio(int precio, int descuento){
        float total;
        total = (precio - (descuento/100.0)*precio);
        //printf("%i, %i, %.2f\n", precio, descuento, total);
        return total;
}

void leerPlanes(FILE* fpPlanes){
    char linea[256];
    int i;
  fpPlanes = fopen("plan.txt", "r");
  if(fpPlanes == NULL){
    printf("No se pudo leer el archivo. Verifique que exista en el directorio del programa.\n");
    return;
  } else {
        for(i = 0; !feof(fpPlanes); i++){
            fscanf(fpPlanes, "%s", linea);
            //printf("(Log) Linea Leida: %s\n", linea);
            insertaPlan(linea);
        }
        printf("(Log) Se leyeron %i lineas con planes\n", i);
  }
  fclose(fpPlanes);
}

void insertaPlan(char * linea)
{
    plan** lista = &listaPlanes;
    int descuento, precio, i, j;
    char codigo, stringAux[4];

    codigo = linea[0];

    j = 0;
    for(i = 2; linea[i] != '-'; i++){
        stringAux[j] = linea[i];
        j++;
    }
    stringAux[j] = '\0';
    precio = atoi(stringAux);

    j = 0;
    for(i = i + 1; linea[i] != '\0' && linea[i] != '%' ; i++){
        stringAux[j] = linea[i];
        j++;
    }
    stringAux[j] = '\0';
    descuento = atoi(stringAux);

    //printf("(Log) Parseo: %c, %i, %i\n", codigo, precio, descuento);

    plan * nuevoPlan = (plan*) malloc(sizeof(plan));
    nuevoPlan->codigo = codigo;
    nuevoPlan->precio = precio;
    nuevoPlan->porcentajeDescuento = descuento;

    if(*lista == NULL){
        *lista = nuevoPlan;
        nuevoPlan->siguiente = NULL;
    } else {
        nuevoPlan->siguiente = *lista;
        *lista = nuevoPlan;
    }
}

void mostrarPlanes(){
    plan * temp = listaPlanes;
    if(temp == NULL){
        printf("Lista vacia.\n");
    } else {
        while(temp != NULL){
            printf("%c-%i-%i\%\n", temp->codigo, temp->precio, temp->porcentajeDescuento);
            temp = temp->siguiente;
        }
    }
}

void mostrarPersonas(){
    persona* lista = listaPersonas;
    persona * temp;
    temp = lista;
    if(temp == NULL){
        printf("La lista esta vacia\n");
    }

    printf("%s-%s-%i-%c-%i-%c\n", temp->nombre, temp->apellido, temp->edad, temp->sexo, temp->antiguedad, temp->plan);
    temp = temp->siguiente;
    while(temp != lista){
        printf("%s-%s-%i-%c-%i-%c\n", temp->nombre, temp->apellido, temp->edad, temp->sexo, temp->antiguedad, temp->plan);
        temp = temp->siguiente;
    }
}

void leerPersonas(FILE * fpPersonas){
    int i;
    char * linea = (char*)malloc(300 * sizeof(char));
    fpPersonas = fopen("personas.txt","r");
    if(fpPersonas == NULL){
        printf("No se pudo leer el archivo. Verifique que exista en el directorio del programa.\n");
        return;
        } else {
            for(i = 0; fscanf(fpPersonas, "%s", linea) != EOF; i++){
    //          fscanf(fpPersonas, "%[^\n]", linea);
                //printf("(Log) Linea Leida: %s\n", linea);
                insertaPersona(linea);
                //fscanf(fpPersonas, "%[^-]-%[^-]-%d-%c-%d-%c", nombre, apellido, &edad, &sexo, &plan);
            }
            printf("(Log) Se leyeron %i lineas con personas\n", i);
    }
    fclose(fpPersonas);
}

void insertaPersona(char * linea){
    persona** lista = &listaPersonas;
    int i = 0, j = 0, k = 0;
    int edad, antiguedad;
    char sexo, plan, nombre[255], apellido[255], stringAux[4];

    //------------------Parseo de linea-------------------
    //printf("(Log) ");
    j = 0;
    for(i = 0; linea[i] != '-'; i++){
        nombre[j] = linea[i];
        j++;
        }
    nombre[j] = '\0';
    //printf("%s, ", nombre);

    j = 0;
    for(i = i+1; linea[i] != '-'; i++){
        apellido[j] = linea[i];
        j++;
        }
    apellido[j] = '\0';
    //printf("%s, ", apellido);

    j = 0;
    for(i = i+1; linea[i] != '-'; i++){
        stringAux[j] = linea[i];
        j++;
        }
    stringAux[j] = '\0';
    edad = atoi(stringAux);
    //printf("%i, ", edad);

    i++;
    sexo = linea[i];
    i++;
    //printf("%c, ", sexo);

    j = 0;
    for(i = i+1; linea[i] != '-'; i++){
        stringAux[j] = linea[i];
        j++;
    }
    stringAux[j] = '\0';
    antiguedad = atoi(stringAux);
    //printf("%i, ", antiguedad);

    i++;
    plan = linea[i];
    //printf("%c\n", plan);

    // ------------ Agregado a la lista ----------
    persona * nuevaPersona = (persona*) malloc(sizeof(persona));
    nuevaPersona->nombre = (char*) malloc(256 * sizeof(char));
    nuevaPersona->apellido = (char*) malloc(256 * sizeof(char));
    strcpy(nuevaPersona->nombre, nombre);
    strcpy(nuevaPersona->apellido, apellido);
    nuevaPersona->edad = edad;
    nuevaPersona->sexo = sexo;
    nuevaPersona->antiguedad = antiguedad;
    nuevaPersona->plan = plan;

    persona * temp = *lista;

    if(*lista == NULL){
        *lista = nuevaPersona;
        nuevaPersona->anterior = nuevaPersona;
        nuevaPersona->siguiente = nuevaPersona;
    } else {
        nuevaPersona->siguiente = (*lista)->siguiente;
        (*lista)->siguiente = nuevaPersona;
        nuevaPersona->anterior = *lista;
    }

    //Idea de parseo original:
    //No quise perder mas tiempo intentando arreglarla
    /*for(i = 0; linea[i] != '\0'; i++)
    {
        if(linea[i] == '-')
        {
            j++;
            i++;
            k = 0;
        }
        switch(j)
        {
            case 0:
            nombre[k] = linea[i];
            k++;
            nombre[k] = '\0';
            break;

            case 1:
            apellido[k] = linea[i];
            k++;
            apellido[k] = '\0';
            break;

            case 2:
            stringAux[k] = linea[i];
            k++;
            stringAux[k] = '\0';
            break;

            case 3:
            edad = atoi(stringAux);
            stringAux[0] = '\0';
            sexo = linea[i];
            break;

            case 4:
            stringAux[k] = linea[i];
            k++;
            stringAux[k] = '\0';
            break;

            case 5:
            antiguedad = atoi(stringAux);
            plan = linea[i];
            break;
        }
    }*/
//    printf("Parseo: %s, %s, %c, %c, %c\n", nombre, apellido, edad, sexo, plan);
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


