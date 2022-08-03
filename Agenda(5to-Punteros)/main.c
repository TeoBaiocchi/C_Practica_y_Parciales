#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void limpiarPantalla(){
  #if defined(linux) || defined(unix) || defined(APPLE)
    system("clear");
  #endif

  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #endif
}

typedef struct{
  char* dni, *nombre, *telefono, *mail, *direccion;
  int edad;
} Contacto;

void bufferEnter(){
  int c;
  while ((c = getchar()) != '\n' && c != EOF){}
}


int ingresoEntero(){
  int x;
  scanf("%i", &x);
  bufferEnter(); //Esto es un codigo de verificación que usaba cuando intenté hacer algo con NULL y me
  if(x == 2425) //dio problemas. Si bien después resolví ese asunto decidí dejarlo
    x = 2426; //como medida de confirmación de eliminación adicional
  return x;
}
//Hay que empezar a leer la cadena completa y, no caracter por caracter.
void ingresoArrayChar(char aux[]){
  int i;
  for(i = 0; i < 65 && (aux[i] = getchar())!= '\n'; i++){}
    aux[i] = '\0';
    if(i == 65)
      bufferEnter();
}

void ingresoContacto(Contacto *auxiliar, int n){
  //Esta función recibe un contacto ya creado. Eso es un tanto confuso.
  //Muy bien el reusar la variable.
  char arrayProvisorio[65];
  int x;
  limpiarPantalla();
  printf("Nombre: ");
  ingresoArrayChar(arrayProvisorio);
  //auxiliar + 0 es lo mismo que poner auxiliar, en todos los casos donde aparece hay que sacarlo.
  (auxiliar + 0) -> nombre = malloc(strlen(arrayProvisorio) + 1);
  strcpy((auxiliar + 0) -> nombre, arrayProvisorio);
  printf("Telefono: ");
  ingresoArrayChar(arrayProvisorio);
  (auxiliar + 0) -> telefono = malloc(strlen(arrayProvisorio) + 1);
  strcpy((auxiliar + 0)->telefono, arrayProvisorio);
  printf("Mail: ");
  ingresoArrayChar(arrayProvisorio);
  (auxiliar + 0) -> mail = malloc(strlen(arrayProvisorio)+1);
  strcpy((auxiliar + 0)->mail, arrayProvisorio);
  printf("Direccion: ");
  ingresoArrayChar(arrayProvisorio);
  (auxiliar + 0) -> direccion = malloc(strlen(arrayProvisorio)+1);
  strcpy((auxiliar + 0)->direccion, arrayProvisorio);
  printf("D.N.I: ");
  ingresoArrayChar(arrayProvisorio);
  (auxiliar + 0) -> dni = malloc(strlen(arrayProvisorio)+1);
  strcpy((auxiliar + 0) -> dni, arrayProvisorio);
  printf("Edad: ");
  x=ingresoEntero();
  (auxiliar + 0) -> edad = x;
}

void nuevoContacto(Contacto *auxiliar, Contacto *agenda, int n){
  limpiarPantalla();
  (agenda + n) -> nombre =  malloc(strlen((auxiliar + 0) -> nombre) + 1);
  strcpy( (agenda + n)-> nombre, (auxiliar + 0) -> nombre);
  (agenda + n) -> telefono =  malloc(strlen((auxiliar + 0) -> telefono) + 1);
  strcpy( (agenda + n)-> telefono, (auxiliar + 0) -> telefono);
  (agenda + n) -> mail =  malloc(strlen((auxiliar + 0) -> mail) + 1);
  strcpy( (agenda + n)-> mail, (auxiliar + 0) -> mail);
  (agenda + n) -> direccion =  malloc(strlen((auxiliar + 0)-> direccion) + 1);
  strcpy( (agenda+ n) -> direccion, (auxiliar + 0) -> direccion);
  (agenda + n) -> dni =  malloc(strlen((auxiliar + 0) -> dni) + 1);
  strcpy( (agenda + n)-> dni, (auxiliar + 0) -> dni);
  (agenda + n) -> edad = (auxiliar + 0)-> edad;
  limpiarPantalla();
  printf("Nombre: %s \n", (agenda + n) -> nombre);
  printf("Telefono: %s \n", (agenda + n) -> telefono);
  printf("Mail: %s \n", (agenda + n) -> mail);
  printf("Direccion: %s \n", (agenda + n) -> direccion);
  printf("D.N.I: %s \n", (agenda + n) -> dni);
  printf("Edad: %i \n", (agenda + n) -> edad);
  printf("Contacto agregado con exito! \n");
}

void imprimirContactos(Contacto *agenda, int n){
  int i;
  limpiarPantalla();
  printf("Lista de contactos: \n");
  for(i = 0; i < n; i++){
    if((agenda + i) -> edad != 2425){
      printf("\n Nombre: %s \n", (agenda + i) -> nombre);
      printf("Telefono: %s \n", (agenda + i) -> telefono);
      printf("Mail: %s \n", (agenda + i) -> mail);
      printf("Direccion: %s \n", (agenda + i) -> direccion);
      printf("Direccion: %s \n", (agenda + i) -> dni);
      printf("Edad: %i \n", (agenda + i) -> edad);
    }
  }
}

void ingresoClaveBusqueda(char arrayProvisorio[]){
  limpiarPantalla();
  printf("Ingrese la clave de busqueda: ");
  ingresoArrayChar(arrayProvisorio);
}

void ingresoLetraSimple(char l[]){
  limpiarPantalla();
  printf("Ingrese una letra: ");
  scanf("%c", &l[0]);
  bufferEnter();
}

//Habría que retornarlos
void imprimirContactosLetra(char l[], Contacto *agenda, int n){
  limpiarPantalla();
  char name[65], letra[2];
  int i = 0;
  l[0] = toupper(l[0]);
  l[1] = '\0';
  limpiarPantalla();
  printf("Lista de contactos que comienzan con %c: \n", l[0]);
  if( (agenda + i) -> edad != 2425){
    for(i = 0; i < n; i++){
      strcpy(name, (agenda + i) -> nombre);
      letra[0] = toupper(name[0]);
      letra[1] = '\0';
      if(strcmp(letra , l) == 0){
        printf("\nNombre: %s \n", (agenda + i) -> nombre);
        printf("Telefono: %s \n", (agenda + i) -> telefono);
        printf("Mail: %s \n", (agenda + i) -> mail);
        printf("Direccion: %s \n", (agenda + i) -> direccion);
        printf("Edad: %i \n", (agenda + i) -> edad);
      }
    }
  }
}

//Habría que retornarlos
void buscarContactosNombre(char nom[], Contacto *agenda, int n){
  int i, x;
  char comp[66];
  limpiarPantalla();
  printf("Lista de contactos que comienzan con: %s\n", nom);
  for(i = 0 ; nom[i] ; i++)
    nom[i] = toupper(nom[i]);
    for(i = 0; i < n; i++){
      if((agenda + i) -> edad != 2425){
        strcpy(comp, (agenda + i) -> nombre);
        for(x = 0; x < strlen(nom); x++){
          comp[x] = toupper(comp[x]);
        } comp[x] = '\0';
        if(strcmp(comp, nom) == 0){
          printf("\nNombre: %s \n", (agenda + i) -> nombre);
          printf("Telefono: %s \n", (agenda + i) -> telefono);
          printf("Mail: %s \n", (agenda + i) -> mail);
          printf("Direccion: %s \n", (agenda + i) -> direccion);
          printf("Edad: %i \n", (agenda + i) -> edad);
      }
    }
  }
}

//Habría que retornarlos
void buscarContactosTelefono(char telefono[], Contacto * agenda, int n){
  char numero[65], comp[65];
  int i;
  limpiarPantalla();
  for(i = 0; i < n; i++){
    if((agenda + i) -> edad != 2425){
      strcpy(comp, (agenda + i) -> telefono);
      if(strcmp(numero, comp) == 0){
        printf("\nNombre: %s \n", (agenda + i) -> nombre);
        printf("Telefono: %s \n", (agenda + i) -> telefono);
        printf("Mail: %s \n", (agenda + i) -> mail);
        printf("Direccion: %s \n", (agenda + i) -> direccion);
        printf("Edad: %i \n", (agenda + i) -> edad);
      }
    }
  }
}

void eliminarTodosContactos(Contacto* agenda, int n){
  limpiarPantalla();
  int i;
  printf("Seleccionaste eliminar la agenda. Estas seguro?\n");
  printf("(1) Si, estoy seguro. (otro) No, cambie de opinion\n");
  int confirmacion;
  confirmacion = ingresoEntero();
  if(confirmacion == 1){
    limpiarPantalla();
    printf("Esto es absolutamente irreversible.\n");
    printf("(1) Continuar. (otro) No, cambie de opinion\n");
    confirmacion = ingresoEntero();
      if(confirmacion == 1){
        for(i = 0; i < n; i++){
          free((agenda + i) -> nombre);
          free((agenda + i) -> telefono);
          free((agenda + i) -> direccion);
          free((agenda + i) -> mail);
          free((agenda + i) -> dni);
          (agenda + i) -> edad = 2425;
            }
      limpiarPantalla();
      printf("Agenda eliminada\n");
    }
  }
}

int eliminarContactoNombre(char nom[], Contacto *agenda, int n){
  int i, x, posibilidades[50], y = 0, e = 0;
  char comp[66];
  limpiarPantalla();
  printf("Lista de contactos que comienzan con: %s\n", nom);
  //Esto quedó mal tabulado y, da la impresión que todo está dentro del 1er for.
  for(i=0 ; nom[i] ; i++)
    nom[i]=toupper(nom[i]);
    //Hay que arreglar esto.
    if((agenda + i) -> edad != 2425){
      for(i = 0; i < n; i++){
        strcpy(comp, (agenda + i) -> nombre);
        for(x = 0; x < strlen(nom); x++){
          comp[x] = toupper(comp[x]);
        } comp[x] = '\0';
        if(strcmp(comp, nom) == 0){
          posibilidades[y] = i;
          y++;
    }
  }
}
//Preguntemos contacto por contacto si se lo quiere eliminar. No recopilemos todas las posiciones primero y, luego preguntemos.
  if(y > 0){
  printf("El contacto que desea eliminar es alguno de los siguientes?\nIngrese el numero correpsondiente u otro para salir\n");
  for(i = 0; i < y; i++){
    printf("(%i) Eliminar a: %s\n", i, (agenda + posibilidades[i]) -> nombre);
    }
  int m;
  m = ingresoEntero();
  n--;
  if(m < y && m >= 0){
    strcpy((agenda + posibilidades[m]) -> nombre, (agenda+n) -> nombre);
    strcpy((agenda + posibilidades[m]) -> telefono, (agenda+n) -> telefono);
    strcpy((agenda + posibilidades[m]) -> direccion, (agenda+n) -> direccion);
    strcpy((agenda + posibilidades[m]) -> mail, (agenda+n) -> mail);
    strcpy((agenda + posibilidades[m]) -> dni, (agenda+n) -> dni);
    (agenda + posibilidades[m]) -> edad = (agenda+n) -> edad;
    free((agenda + n) -> nombre);
    free((agenda + n) -> telefono);
    free((agenda + n) -> direccion);
    free((agenda + n) -> mail);
    free((agenda + n) -> dni);
    (agenda + n) -> edad = 2425;
    e = 1;
    }
  }
  if(y==0)
    printf("No hay resultados\n");
  return e;
}

void menu(){
  Contacto *agenda, *auxiliar;
  auxiliar = malloc(sizeof(Contacto));
  agenda = malloc(sizeof(Contacto) * 50);
  int y = 0, salida = 0, primerMenu = 0, cont = 0, i = 0, e = 0, contTotal = 0;
  char clave[65], l[2];
  //Habría que tabular.
  while(salida != 1){
  if(primerMenu != 0){
    printf("Presione enter para volver al menu.");
    bufferEnter();
         }
  if(primerMenu == 0)
    primerMenu = 1;
    limpiarPantalla();
    printf("--Agenda - Teo Baiocchi Ensinck 5to Info -\n");
    printf("Cantidad de contactos: %i \n \nSeleccione una opcion:\n", (cont));
    printf("(1)-Nuevo contacto\n");
    printf("(2)-Lista de contactos\n");
    printf("(3)-Filtrar por inicial\n");
    printf("(4)-Buscar por nombre\n");
    printf("(5)-Buscar por numero telefonico\n");
    printf("(6)-Eliminar contacto\n");
    printf("(7)-Eliminar lista de contactos\n");
    printf("(8)-Salir del programa\n");
    y = ingresoEntero();
    switch (y){
      //Habría que simplificar la ejecución, directamente se debería llamar a nuevoContacto. nuevoContacto que se encargue
      //en caso de necesitarlo, de llamar a ingresoContacto. 
      //El incremento de las variables de cantidad se debería realizar en las funciones.
      case 1: ingresoContacto(auxiliar, cont); nuevoContacto(auxiliar, agenda, cont); cont++; contTotal++; break;
      case 2: imprimirContactos(agenda, cont); break;
      case 3: ingresoLetraSimple(l); imprimirContactosLetra(l, agenda, cont); break;
      case 4: ingresoClaveBusqueda(clave); buscarContactosNombre(clave, agenda, cont); break;
      case 5: ingresoClaveBusqueda(clave); buscarContactosTelefono(clave, agenda, cont);break;
      case 6: ingresoClaveBusqueda(clave); e=eliminarContactoNombre(clave, agenda, cont); cont=cont-e; break;
      case 7:  eliminarTodosContactos(agenda, contTotal); cont = 0; contTotal = 0; break;
      case 8: salida = 1; break;
      default: limpiarPantalla(); printf("Ingrese un numero valido \n"); break;
        }
    }
  for(i = 0; i < cont; i++){
    free((agenda + i) -> nombre);
    free((agenda + i) -> telefono);
    free((agenda + i) -> direccion);
    free((agenda + i) -> mail);
    free((agenda + i) -> dni);
    }
  free(agenda);

}

int main()
{
  menu();
  limpiarPantalla();
  printf("Programa cerrado.");
  return 0;
}
