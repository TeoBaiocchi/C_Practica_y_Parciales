#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct tiempo{
    int anio, mes, dia, hora, minuto, segundo;
    //struct tiempo variable;
} Tiempo;

int menorMayor(int a, int b){
    if(a < b)
        return 1;
    if(a > b)
        return -1;
    if(a == b)
        return 0;
}

int compara_tiempos(Tiempo *t1, Tiempo *t2);

int main(){

    Tiempo t1, t2;
    t1.anio = 1;
    t1.mes = 2;
    t1.dia = 3;
    t1.hora = 4;
    t1.minuto = 5;
    t1.segundo = 6;

    t2.anio = 1;
    t2.mes = 2;
    t2.dia = 3;
    t2.hora = 4;
    t2.minuto = 5;
    t2.segundo = 6;

    int resultado = compara_tiempos(&t1, &t2);
    printf("\nDio: %i\n", resultado);
    return 0;
}

int compara_tiempos(Tiempo *t1, Tiempo *t2){
    int tiempo1[6], tiempo2[6]; //aux

    tiempo1[0] = t1->anio;
    tiempo1[1] = t1->mes;
    tiempo1[2] = t1->dia;
    tiempo1[3] = t1->hora;
    tiempo1[4] = t1->minuto;
    tiempo1[5] = t1->segundo;

    tiempo2[0] = t2->anio;
    tiempo2[1] = t2->mes;
    tiempo2[2] = t2->dia;
    tiempo2[3] = t2->hora;
    tiempo2[4] = t2->minuto;
    tiempo2[5] = t2->segundo;

    for(int i=0; i<6 ; i++){
        if(menorMayor(tiempo1[i], tiempo2[i]) != 0){
            return menorMayor(tiempo1[i], tiempo2[i]);
        }
    }

    return 0;


    //switch(menorMayor(t1 ->))
    /*if( t1->anio <  (*t2).anio){
        return 1;
        } else if(t1->mes < t2->mes){
            return 1;
            } else if(t1->dia < t2->dia){
                return 1;}
                    else if(t1->hora < t2->hora){
                        return 1;}
                             else if(t1->minuto < t2->minuto){
                                return 1;}
                                    else if(t1->segundo < t2->segundo){
                                        return 1;}*/

}


