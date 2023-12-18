#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5

int main(){

        int **M1, **M2, **sumaM;
        int i, j;

        
        M1 = (int**) malloc (sizeof(int*) * N);
        M2 = (int**) malloc (sizeof(int*) * N);
        sumaM = (int**) malloc(sizeof(int*) * N);

        srand(time(NULL));
        

        for(i=0; i<N; i++){
            *(M1+i) = (int*) malloc (sizeof(int)*N);
            *(M2+i) = (int*) malloc (sizeof(int)*N);
            *(sumaM+i) = (int*) malloc(sizeof(int) * N);
            for(j=0; j<N; j++){
                *(*(M1 + i)+j) = rand() % 100;
                *(*(M2 + i)+j) = rand() % 100;
                *(*(sumaM + i) + j) = (*(*(M1 + i)+j) + *(*(M2 + i)+j)); 
            }
        }


        for(i=0; i<N; i++){
            for(j=0; j<N; j++){
                //printf( "i: %d, j: %d, m1: %d, m2: %d\n", i, j, M1[i][j], *(*(M2+i)+j));
                printf("m1: %d, m2: %d suma: %i\n", M1[i][j], *(*(M2+i)+j), *(*(sumaM+i)+j));
            }
        }



    return 0;
}
