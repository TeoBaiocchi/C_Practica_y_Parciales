#include <stdio.h>
int main()
{
    menu();
    /*int testInteger;
    printf("Enter an integer: ");
    scanf("%d", &testInteger);  
    printf("Number = %d",testInteger); */
    return 0;
}
 
void limpiarPantalla(){
  #if defined(linux) || defined(unix) || defined(APPLE)
    system("clear");
  #endif

  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #endif
  // Este es bastante evidente, pero resulta muy practico.
  // Este modulo detecta basicamente si estás en windows o en linux, 
  // para usar el comando apropiado para limpiar pantalla.
  // Tantos años después no recuerdo los detalles, pero no podía hacerse
  // de cualquier manera, porque la presencia del comando dentro de un if
  // común aunque no se ejecute podía tirar un error de compilación
}

void bufferEnter(){
  int c;
  while ((c = getchar()) != '\n' && c != EOF){}
  // No avanza hasta que presiones enter. Bastante útil. 
}

void menu(){
    printf("Bienvenido al programa de prueba/plantillas de Teo \n");
    printf("Presione enter para continuar: ");
    bufferEnter();
}