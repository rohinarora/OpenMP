/**
 * @author Rohin Arora
 * @email rohinarora07@gmail.com
 * @create date 2020-02-25
 * @modify date 2020-02-25
 *
 * Sparse Matrix multiplication using naive multiplication
 */
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#define M 512 

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

int main(int argc, char **argv)
{
    int i,j,k;
    double start, finish, total, sum;
    float  a[M][M], b[M][M], c[M][M];


/* Initialize a, b and c */
    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
          {
            if ((i+j)%7 == 0)
             a[i][j] = 2.;
            else a[i][j] = 0.;
	  }

    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
             b[i][j] = (i/3)+(j/5); 

    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
           c[i][j] = 0.;

/* Start timing */
    start = CLOCK();

/* This is the only portion of the code you should modify to improve performance. */

    for (i =0; i<M; i++)
     for (j=0; j<M; j++)
       for (k=0; k<M; k++)
        c[i][j] += a[i][k] * b[k][j];

    finish = CLOCK();
/* End timing */
    total = finish - start;
    printf("Time for the loop = %f\n", total);
    printf("The value of c[%d][%d] = %4.2f\n", 0, 0, c[0][0]);
    printf("The value of c[%d][%d] = %4.2f\n", 31, 32, c[31][32]);
    printf("The value of c[%d][%d] = %4.2f\n", 510, 0, c[510][0]);
    printf("The value of c[%d][%d] = %4.2f\n", 511, 511, c[511][511]);

    return 0;
}

