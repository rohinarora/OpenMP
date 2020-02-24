/**
 * @author Rohin Arora
 * @email rohinarora07@gmail.com
 * @create date 2020-02-23
 * @modify date 2020-02-23
 * @desc 


This program will numerically compute the integral of

                  4/(1+x*x)

from 0 to 1.  

This program introduces OpenMP for the application
*/
#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 2
static long num_steps = 1000000000;
double step;
int main()
{
	int i, nthreads;
	double pi, sum[NUM_THREADS];
	double start_time, run_time;
	step = 1.0 / (double)num_steps;
	omp_set_num_threads(NUM_THREADS);
	start_time = omp_get_wtime();
#pragma omp parallel
	{
		int nthrds, i, id;
		double x;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		if (id == 0)
			nthreads = nthrds;
		for (i = id, sum[id] = 0.0; i <= num_steps; i += nthrds)
		{
			x = (i + 0.5) * step;
			sum[id] += 4.0 / (1.0 + x * x);
		}
	}

	for (int idx = 0; idx < nthreads; ++idx)
	{
		pi = pi + sum[idx];
	}
	pi = pi * step;
	run_time = omp_get_wtime() - start_time;
	printf("\n pi with %ld steps is %lf in %lf seconds\n ", num_steps, pi, run_time);
	return 0;
}
