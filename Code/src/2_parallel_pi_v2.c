/*

This program will numerically compute the integral of

                  4/(1+x*x)

from 0 to 1.  The value of this integral is pi -- which
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

Use padding to prvent false sharing
*/
#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 12
#define PAD 8
static long num_steps = 1000000000;
double step;
int main()
{
	int i, nthreads;
	double pi, sum[NUM_THREADS][PAD];
	double start_time, run_time;
	step = 1.0 / (double)num_steps;
	omp_set_num_threads(NUM_THREADS);
	start_time = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp single
		printf(" num_threads = %d", omp_get_num_threads());
		int nthrds, i, id;
		double x;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		if (id == 0)
			nthreads = nthrds;
		for (i = id, sum[id][0] = 0.0; i <= num_steps; i += nthrds)
		{
			x = (i + 0.5) * step;
			sum[id][0] += 4.0 / (1.0 + x * x);
		}
	}

	for (int idx = 0; idx < nthreads; ++idx)
	{
		pi = pi + sum[idx][0];
	}
	pi = pi * step;
	run_time = omp_get_wtime() - start_time;
	printf("\n pi with %ld steps is %lf in %lf seconds\n ", num_steps, pi, run_time);
	return 0;
}
