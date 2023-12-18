#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct alumno{
    char nom[25];
    float nota[3];
    float prom;
    char sit[20];
};


void limpieza(int W){
    if(W==1){
        system("cls");
    }
    if(W==2){
        system("clear");
    }
}
void normalizacion(struct alumno todos[], int N){
	int i, j;
	for(i=0; i<N; i++){
		todos[i].nom[0]=toupper(todos[i].nom[0]);
		for(j=1; j<strlen(todos[i].nom); j++){
			todos[i].nom[j]=tolower(todos[i].nom[j]);
		}
	}
}
void situacion(struct alumno todos[], int N){
	int i;
	for(i=0; i<N; i++){
	    todos[i].prom=(todos[i].nota[0]+todos[i].nota[1]+todos[i].nota[2])/3;
        if(todos[i].prom<4){
            strcpy(todos[i].sit, "Marzo");
        }
        else if(todos[i].prom < 6){
            strcpy(todos[i].sit, "Diciembre");
        }
        else{
            strcpy(todos[i].sit, "Aprobado");
        }
		}
}
void aprobacion(struct alumno todos[], struct alumno aprobados[], int N){
	int i, x=0;
	for(i=0; i<N; i++){
		if(strcmp(todos[i].sit, "Aprobado")==0){
		aprobados[x]=todos[i];
		x++;
		}
		}}

void ordenacion(struct alumno todos[],int N, struct alumno aux){
    int i, j;
    for(i=0; i<N-1; i++)
    {
    for(j=(i+1); j<N; j++)
    {
        if(strcmp(todos[i].sit, todos[j].sit)>0)
        {
            aux=todos[i];
            todos[i]=todos[j];
            todos[j]=aux;
        }
        if(strcmp(todos[i].sit, todos[j].sit)==0)
        {   if(strcmp(todos[i].nom, todos[j].nom)>0)
            {
                aux=todos[i];
                todos[i]=todos[j];
                todos[j]=aux;
            }
        }
    }
    }
	}
int main()
{
	struct alumno todos[50], aprobados[50], aux;
    int W, N, i, y;
    while(1==1){
    printf("Ingrese el sistema operativo desde el que esta ejecutando el programa: \n Windows (1) \n Linux (2)\n");
    scanf("%i", &W);
    if(W==1)
        break;
    if(W==2)
        break;
    }
    limpieza(W);
    printf("Ingrese la cantidad de alumnos a registrar. \n ");
    scanf("%i", &N);
    limpieza(W);
    for(i=0; i<N; i++){
        printf("Ingrese los datos del alumno nro %i \n", i+1);
        printf("Apellido: ");
        scanf("%s", todos[i].nom);
        printf("Nota 1: ");
        scanf("%f", &todos[i].nota[0]);
        printf("Nota 2: ");
        scanf("%f", &todos[i].nota[1]);
        printf("Nota 3: ");
        scanf("%f", &todos[i].nota[2]);

        limpieza(W);}
		normalizacion(todos, N);
		situacion(todos, N);
		aprobacion(todos, aprobados, N);
		ordenacion(todos, N, aux);

	printf("Se mostrara la lista de los alumnos por orden de situacion y apellido.\n");
	for(i=0; i<N; i++){
		printf("Alumno: %s\n", todos[i].nom);
		printf("Promedio: %.2f\n", todos[i].prom);
		printf("Situacion: %s\n\n", todos[i].sit);
	}
	return 0;
    }
